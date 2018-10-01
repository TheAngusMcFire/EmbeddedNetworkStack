#include <ethernet.h>
#include <uart.h>
#include <utils.h>
#include <string.h>

uint8_t ethernetParseHeader(EthernetHeader *eth_header, uint8_t *buffer, uint16_t rcv_size)
{
    if(rcv_size < ETH_MIN_SIZE)
        return ETH_HEADER_FAIL;

    for(uint8_t index = 0; index < 6; index++)
        eth_header->dst_mac[index] = buffer[index];

    buffer += 6;

    for(uint8_t index = 0; index < 6; index++)
        eth_header->src_mac[index] = buffer[index];

    buffer += 6;

    eth_header->eth_type  = 0;
    eth_header->eth_type |= buffer[0] << 8;
    eth_header->eth_type |= buffer[1] << 0;

    buffer += 2;

    eth_header->payload_ptr = buffer;
    eth_header->payload_size = rcv_size - (6 + 6 + 2);

    return ETH_HEADER_OK;
}

void ethernetPrintHeader(EthernetHeader *eth_header)
{
    utilsWriteLine(0);
    uartWriteString("Eth Header: ");
    utilsPrintIndentedString("Dest MAC : ");
    utilsPrintMacAddress(eth_header->dst_mac);

    utilsPrintIndentedString("Src MAC  : ");
    utilsPrintMacAddress(eth_header->src_mac);

    utilsPrintIndentedString("Eth Type : ");
    utilsPrintUint16(eth_header->eth_type);

    utilsPrintIndentedString("Pay Size : ");
    utilsPrintInt(eth_header->payload_size);

    if(eth_header->payload_size < 50)
    {
        utilsPrintIndentedString("Payload  : ");
        utilsPrintHex(eth_header->payload_ptr, eth_header->payload_size);
    }
    
    utilsWriteLine(0);
    utilsWriteLine(0);
}

void ethernetBuildHeader(EthernetHeader *eth_header, uint8_t *dst_mac, uint8_t *src_mac, uint16_t eth_type)
{
    memcpy(eth_header->dst_mac, dst_mac, 6);
    memcpy(eth_header->src_mac, src_mac, 6);
    eth_header->eth_type = eth_type;
    eth_header->payload_ptr = 0;
    eth_header->payload_size = 0;
}

uint16_t ethernetHeaderToBuffer(EthernetHeader *eth_header, uint8_t * buffer)
{
    memcpy(buffer, eth_header->dst_mac, 6);
    buffer += 6;
    memcpy(buffer, eth_header->src_mac, 6);
    buffer += 6;
    buffer[0] = eth_header->eth_type >> 8;
    buffer[1] = eth_header->eth_type & 0xff;

    return ETH_HEADER_SIZE;
}