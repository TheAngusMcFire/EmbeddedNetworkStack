#include <device.h>

#ifndef INTERFACES_NET_UTILS_H
#define INTERFACES_NET_UTILS_H

#ifdef LITTLE_ENDIAN

NET_UTILS_FIX_ENDIANESS_UINT16(var) var = ((var << 8) | (var >> 8))
NET_UTILS_FIX_ENDIANESS_UINT32(var) var = (   \
    ((var >> 24) & 0xFF)      |               \
    ((var >> 8)  & 0xFF00)    |               \
    ((var << 8)  & 0xFF0000)  |               \
    ((var << 24) & 0xFF000000))               \

#else

NET_UTILS_FIX_ENDIANESS_UINT16(var)
NET_UTILS_FIX_ENDIANESS_UINT32(var)

#endif

uint16_t netUtilsCalcChecksum(uint8_t *buffer, uint8_t size);

#endif