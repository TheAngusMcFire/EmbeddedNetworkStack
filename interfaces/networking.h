
#include <device.h>
#include <ethernet.h>
#include <ip.h>
#include <tcp.h>
#include <udp.h>
#include <arp.h>

#ifndef INTERFACES_NETWORKING_H
#define INTERFACES_NETWORKING_H

enum NETWORKING_TYPE
{
    TCP = 0xAA, UDP = 0x55
}

void networkingHandleData(uint8_t *buffer);

void networkingRegisterHandler(void (*handler)(), uint16_t port, uint8_t tcp);

#endif