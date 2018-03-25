
#ifndef __BASE4096_H__
#define __BASE4096_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
	int base4096_decode(const uint16_t *data, const int i_count, void *result, const int o_count);
	int base4096_encode(const void *data, const int i_count, uint16_t *result, const int o_count);

#ifdef __cplusplus
}
#endif

#endif // !__BASE4096_H__
