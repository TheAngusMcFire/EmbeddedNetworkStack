#include <net_utils.h>
#include <utils.h>
#include <string.h>


static uint16_t ntohs (uint16_t value)
{
    uint16_t val = 0;

    val = value >> 8;
    val |= (value & 0xFF) << 8;

    return val; 
}

static uint16_t htons (uint16_t value)
{
    return ntohs(value); 
}

//the code for crc_calc was taken from:
//http://www.microhowto.info/howto/calculate_an_internet_protocol_checksum_in_c.html

uint16_t netUtilsCalcChecksum(uint8_t *buffer, uint8_t size)
{
    uint32_t acc=0xffff;

    // Handle complete 16-bit blocks.
    for (size_t i=0; i+1 < size; i+=2) 
    {
        uint16_t word;
        memcpy(&word,buffer+i,2);
        acc+=ntohs(word);
        if (acc>0xffff) 
        {
            acc-=0xffff;
        }
    }

    // Handle any partial block at the end of the data.
    if (size&1) 
    {
        uint16_t word=0;
        memcpy(&word,buffer+size-1,1);
        acc+=ntohs(word);
        if (acc>0xffff)
        {
            acc-=0xffff;
        }
    }

    // Return the checksum in network byte order.
    return htons(~acc);
} 