#include "mbed.h"
#include "USERLIB/EthUDP.h"
#include "EthernetInterface.h"

Thread thread;
EthernetInterface eth;
EthUDP udp;

void receive_data() {
    udp.initialize("192.168.1.11", "255.255.255.0", "192.168.1.1", 65000);
    char buffer[128];
    while (true) {
        printf("inizio ad ascoltare\n");
        nsapi_size_or_error_t size = udp.receive(buffer, sizeof(buffer), 5000); // Timeout di 5 secondi
        if (size > 0) {
            printf("Received: %s\n", buffer);
        }
    }
    ThisThread::sleep_for(1000ms);
}

void send_data() {
    udp.initialize("192.168.1.11", "255.255.255.0", "192.168.1.1", 65000);

    const char* data = "Hello from sender!";
    SocketAddress sendAddr("192.168.1.11", 65000); // Indirizzo IP del receiver e porta

    while (true) {
        udp.send(data, sendAddr);
        ThisThread::sleep_for(5000ms); // Invia ogni 5 secondi
    }
}

// main() runs in its own thread in the OS
int main() {
    
    
    
    thread.start(receive_data);
    thread.start(send_data);

    while (true) {
        ThisThread::sleep_for(1000ms);
    }
}
