#include "chant.hpp"
#include "ui_chant.h"
#include <QFileDialog>
#include <QString>
#include <QRegularExpression>

#include "base32.h"
#include "base4096.h"

chant::chant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chant)
{
    ui->setupUi(this);

    QFile f(":/data/table.bin");
    f.open(QIODevice::ReadOnly);

    QDataStream fs(&f);

    uint16_t pool[4096];
    fs.readRawData((char *)pool, 4096 * 2);

    chtbl.clear();
    chtbl.insert(chtbl.end(), pool, pool + 4096);

    ui->c_ltext_status->setText("Ready");

    ui->c_bn_dec->setEnabled(true);
    ui->c_bn_enc->setEnabled(true);

    ui->c_cb_mode->addItem("magnet");
    ui->c_cb_mode->addItem("binary");
    ui->c_cb_mode->addItem("raw");
}

chant::~chant()
{
    delete ui;
}

static const QString inv_str("<Input string not supported>");

QString chant::raw_4k_ch(std::string s)
{
    const uint8_t *tmp32 = (uint8_t *)(s.c_str());
    int lraw = s.size();

    uint16_t *tmp4k = new uint16_t[lraw * 2];
    int l4k = base4096_encode(tmp32, lraw, tmp4k, lraw * 2);

    for(int i = 0; i < l4k; ++i)
    {
        if(tmp4k[i] == 0xF001)
        {
            tmp4k[i] = 0x4e5f;
        }
        else
        {
            tmp4k[i] = chtbl[tmp4k[i]];
        }
    }

    std::u16string b4k;
    b4k.insert(b4k.end(), tmp4k, tmp4k + l4k);

    delete[] tmp4k;

    return QString::fromStdU16String(b4k);
}

QString chant::b32_4k_ch(QString s)
{
    std::string b32 = s.toStdString();
    b32.push_back(0);

    uint8_t *tmp32 = new uint8_t[b32.size() * 2];
    int lraw = base32_decode((uint8_t*)b32.c_str(), tmp32, b32.size() * 2);
    if(lraw <= 0)
    {
        return inv_str;
    }

    uint16_t *tmp4k = new uint16_t[lraw * 2];
    int l4k = base4096_encode(tmp32, lraw, tmp4k, lraw * 2);

    for(int i = 0; i < l4k; ++i)
    {
        if(tmp4k[i] == 0xF001)
        {
            tmp4k[i] = 0x4e5f;
        }
        else
        {
            tmp4k[i] = chtbl[tmp4k[i]];
        }
    }

    std::u16string b4k;
    b4k.insert(b4k.end(), tmp4k, tmp4k + l4k);

    delete[] tmp4k;
    delete[] tmp32;

    return QString::fromStdU16String(b4k);
}

std::string hex2raw(QString qs)
{
    std::string s = qs.toStdString();
    std::string ret;
    char tmp;

    for(int i = 0; i < s.size(); ++i)
    {
        char k = 0;

        if(s[i] >= '0' && s[i] <= '9')
        {
            k = s[i] - '0';
        }
        else if(s[i] >= 'A' && s[i] <= 'F')
        {
            k = s[i] - 'A' + 0xA;
        }
        else if(s[i] >= 'a' && s[i] <= 'f')
        {
            k = s[i] - 'a' + 0xa;
        }
        else
        {
            return inv_str.toStdString();
        }

        if((i & 1) == 0)
        {
            tmp = 0;
            tmp |= k << 4;
        }
        else
        {
            tmp |= k;
            ret.push_back(tmp);
        }
    }

    return ret;
}

QString chant::conv_magnet(QString m)
{
    QRegularExpression re32("magnet:\\?.*xt=urn:btih:(?<hash>[ABCDEFGHIJKLMNOPQRSTUVWXYZ234567]{32})");
    QRegularExpression repl("magnet:\\?.*xt=urn:btih:(?<hash>[0123456789abcdef]{40})");
    QRegularExpressionMatch match = re32.match(m);
    if(match.hasMatch())
    {
        QString hash = match.captured("hash");
        return QString("Car ") + b32_4k_ch(hash);
    }

    match = repl.match(m);
    if(match.hasMatch())
    {
        QString hash = match.captured("hash");
        return QString("Car ") + raw_4k_ch(hex2raw(hash));
    }

    return inv_str;
}

void chant::on_c_bn_enc_clicked()
{
    QString src = ui->c_ptext_i->toPlainText();
    QString dst;
    if(src.startsWith("magnet:"))
    {
        dst = conv_magnet(src);
    }
    else if(src.startsWith("bin:"))
    {
        dst = raw_4k_ch(hex2raw(src.mid(4)));
    }
    else if(src.startsWith("raw:"))
    {
        dst = raw_4k_ch(src.mid(4).toStdString());
    }
    else
    {
        dst = inv_str;
    }

    ui->c_ptext_o->setPlainText(dst);
}

void chant::on_c_bn_dec_clicked()
{
    int id = ui->c_cb_mode->currentIndex();
    ui->c_ptext_o->setPlainText(QString::number(id));
}
