
#include <string.h>
#include <malloc.h>

#include "base4096.h"

static const uint16_t PAD1 = 0xF001;
static const uint16_t PAD2 = 0xF002;
static const uint16_t PAD_FLAG = 0xF000;
static const uint16_t PAD_MASK = 0x000F;

int base4096_decode(const uint16_t *data, const int i_count,
	void *result, const int o_count)
{
	int i = 0;
	int j = 0;
	int ret = 0;

	uint8_t *out = 0;
	
	int size = (i_count + 1) / 2 * 3;

	if (o_count <= 0 || i_count <= 0 || !data || !result)
	{
		goto done;
	}

	out = calloc(size, 1);
	memset(out, 0, size);

	if (!out)
	{
		goto done;
	}

	for (i = 0; i < i_count; ++i)
	{
		if ((data[i] & PAD_FLAG) != 0)
		{
			j -= 1;
			break;
		}
		if ((i & 1) == 0)
		{
			out[j++] |= data[i] >> 4;
			out[j+0] |= (data[i] & 0xF) << 4;
		}
		else
		{
			out[j++] |= data[i] >> 8;
			out[j++] |= data[i];
		}
	}

	j = j < 0 ? 0 : j;
	ret = o_count > j ? j : o_count;
	memcpy(result, out, ret);

done:
	free(out);
	return ret;
}

int base4096_encode(const void *data, const int i_count,
	uint16_t *result, const int o_count)
{
	int i = 0;
	int j = 0;
	int ret = 0;

	uint8_t *tmp = 0;
	uint16_t *out = 0;

	int tail = i_count % 3;
	int size = (i_count + 2) / 3 * 2 + 1;

	if (o_count <= 0 || i_count <= 0 || !data || !result)
	{
		goto done;
	}

	tmp = calloc(i_count + 2, 1);
	out = calloc(size, 2);

	if (!tmp || !out)
	{
		goto done;
	}

	memcpy(tmp, data, i_count);

	for (i = 0; i < i_count; i += 3)
	{
		out[j++] = tmp[i] << 4 | tmp[i + 1] >> 4;
		out[j++] = (tmp[i + 1] & 0x0F) << 8 | tmp[i + 2];
	}

	if (tail == 1)
	{
		j -= 1; // no deed to pad when tail size 1
	}
	if (tail == 2)
	{
		out[j++] = PAD1; // pad 1 when tail size 2
	}

	ret = o_count > j ? j : o_count;
	memcpy(result, out, ret * sizeof(uint16_t));

done:
	free(tmp);
	free(out);
	return ret;
}