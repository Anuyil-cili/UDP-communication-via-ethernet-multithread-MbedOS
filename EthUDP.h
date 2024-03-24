#pragma once

#include "mbed.h"
#include "EthernetInterface.h"

class EthUDP {
public:
    EthUDP();
    ~EthUDP();

    nsapi_error_t initialize(const char* ip, const char* netmask, const char* gateway, int port);
    nsapi_size_or_error_t send(const char* data, SocketAddress sendAddr);
    nsapi_size_or_error_t send(const char* data, nsapi_size_t size, const char* addr, uint16_t port)
    nsapi_size_or_error_t receive(char* buffer, nsapi_size_t size, uint32_t timeout); //ricevo da chiunque collegato sulla porta
    nsapi_size_or_error_t receiveFrom(char* buffer, nsapi_size_t size, const char* sender_ip, int port, uint32_t timeout); //ricevo da un indirizzo ip specifico
    nsapi_size_or_error_t receiveFrom(char* buffer, nsapi_size_t size, SocketAddress sender_addr, uint32_t timeout);
private:
    EthernetInterface _eth;
    UDPSocket _socket;
    SocketAddress _addr;
};

