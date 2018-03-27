#ifndef CHANT_HPP
#define CHANT_HPP

#include <QDialog>
#include <cstdint>

namespace Ui {
class chant;
}

class chant : public QDialog
{
    Q_OBJECT

public:
    explicit chant(QWidget *parent = 0);
    ~chant();

private slots:
    void on_c_bn_enc_clicked();

    void on_c_bn_dec_clicked();

private:
    Ui::chant *ui;
    std::vector<uint16_t> chtbl;
    QString b32_4k_ch(QString s);
    QString conv_magnet(QString m);
    QString raw_4k_ch(std::string s);
};

#endif // CHANT_HPP
