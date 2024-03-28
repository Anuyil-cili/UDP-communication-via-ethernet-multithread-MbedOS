#include "mbed.h"
#include "EthUDP.h"
#include "EthernetInterface.h"
#include "UserStruct.h"
#include "cstring"

Thread thread;
Thread thread2;
EthernetInterface eth;
EthUDP udp;


void send_data() {
    Data1 buff;
    buff.id = 1;
    strcpy(buff.name, "Hello from sender!");
    
    SocketAddress remoteAddr("192.168.1.11", 65000); // Indirizzo IP del receiver e porta

    while (true) {
        udp.send(&buff, sizeof(buff), remoteAddr);
        printf("dati mandati\n");
        ThisThread::sleep_for(5000ms); // Invia ogni 5 secondi
    }
}

void receive_data() {

    Data1* buff;
    char buffer[1024];
    SocketAddress remoteAddr("192.168.1.11", 6500);
    while (true) {
        printf("inizio ad ascoltare\n");
        nsapi_size_or_error_t size = udp.receiveFrom(buffer, sizeof(buffer), remoteAddr, 5000); // Timeout di 5 secondi (-1 per receive bloccante)
        if (size > 0) {
            buff =  reinterpret_cast<Data1*>(buffer);
            printf("Received: %i %s\n", buff->id, buff->name);
        }
        ThisThread::sleep_for(1000ms);
    }
    
}

int main() {
    udp.initialize("192.168.1.12", "255.255.255.0", "192.168.1.1", 65000);
    thread.start(send_data);
    thread2.start(receive_data);
    while (true) {
        ThisThread::sleep_for(1000ms);
    }
}
