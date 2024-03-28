#include "mbed.h"
#include "EthUDP.h"
#include "string.h"
#include "cstring"

EthUDP::EthUDP() {
    // Costruttore
}

EthUDP::~EthUDP() {
    // Distruttore
    _socket.close();
    _eth.disconnect();
}

nsapi_error_t EthUDP::initialize(const char* ip, const char* netmask, const char* gateway, int port) {
    
    _eth.set_network(ip, netmask, gateway);

    nsapi_error_t status = _eth.connect();
    if (status != 0) {
        printf("Errore nella connessione Ethernet: %d\n", status);
        return status;
    } else {
        printf("Ethernet connesso con successo.\n");
    }

    status = _socket.open(&_eth);
    if (status != 0) {
        printf("Errore nell'apertura del socket: %d\n", status);
        return status;
    } else {
        printf("Socket aperto con successo.\n");
    }

    status = _socket.bind(port);
    if (status != 0) {
        printf("Errore nel binding del socket: %d\n", status);
        return status;
    } else {
        printf("Socket legato alla porta %d con successo.\n", port);
    }

    return status; // Restituisce 0 se tutto va bene
}

nsapi_size_or_error_t EthUDP::send(const void* buffer, nsapi_size_t size, SocketAddress sendAddr) {
    nsapi_size_or_error_t result = _socket.sendto(sendAddr, buffer, size);

    if (result < 0) {
        // Stampa un errore se l'invio non è riuscito
        printf("Errore nell'invio dei dati: %d\n", result);
    }
    
    return result;
}

nsapi_size_or_error_t EthUDP::send(const void* buffer, nsapi_size_t size, const char* addr, uint16_t port) {
    SocketAddress sendAddr(addr, port);
    nsapi_size_or_error_t result = _socket.sendto(sendAddr, buffer, size);

    if (result < 0) {
        // Stampa un errore se l'invio non è riuscito
        printf("Errore nell'invio dei dati: %d\n", result);
    }
    
    return result;
}


/*
set_timeout(0) -> non bloccante
set_timeout(-1) -> bloccante
set_timeout(>0) -> tempo in ms
*/
nsapi_size_or_error_t EthUDP::receive(char* buffer, nsapi_size_t size, uint32_t timeout) { //prendo il primo dato in coda senza discriminazioni ip
    _socket.set_timeout(timeout); // Imposta il timeout per le operazioni di socket
    SocketAddress sender;
    nsapi_size_or_error_t ret = _socket.recvfrom(&sender, buffer, size); // Tenta di ricevere dati
    
    if (ret >= 0) {
        // Se abbiamo ricevuto dei dati, stampiamo l'indirizzo del mittente
        printf("Dati ricevuti da: %s\n", sender.get_ip_address());
        return ret; // Restituisce il numero di byte ricevuti
    } else {
        // Gestione degli errori in base al codice di ritorno
        switch (ret) {
            case NSAPI_ERROR_WOULD_BLOCK:
                printf("Nessun dato disponibile entro il timeout specificato.\n");
                break;
            case NSAPI_ERROR_NO_SOCKET:
                printf("Nessun socket disponibile per la ricezione.\n");
                break;
            case NSAPI_ERROR_NO_CONNECTION:
                printf("La connessione è stata persa.\n");
                break;
            default:
                printf("Errore nella ricezione: %d\n", ret);
                break;
        }
        return ret; // Restituisce il codice di errore
    }
}

nsapi_size_or_error_t EthUDP::receiveFrom(char* buffer, nsapi_size_t size, const char* sender_ip, int port, uint32_t timeout) { //ricevo da un indirizzo ip specifico
    _socket.set_timeout(timeout); // Imposta il timeout per le operazioni di socket
    SocketAddress sender(sender_ip, port);
    nsapi_size_or_error_t ret = _socket.recvfrom(&sender, buffer, size); // Tenta di ricevere dati
    
    if (ret >= 0) {
        // Se abbiamo ricevuto dei dati, stampiamo l'indirizzo del mittente
        printf("Dati ricevuti da: %s\n", sender.get_ip_address());
        return ret; // Restituisce il numero di byte ricevuti
    } else {
        // Gestione degli errori in base al codice di ritorno
        switch (ret) {
            case NSAPI_ERROR_WOULD_BLOCK:
                printf("Nessun dato disponibile entro il timeout specificato.\n");
                break;
            case NSAPI_ERROR_NO_SOCKET:
                printf("Nessun socket disponibile per la ricezione.\n");
                break;
            case NSAPI_ERROR_NO_CONNECTION:
                printf("La connessione è stata persa.\n");
                break;
            default:
                printf("Errore nella ricezione: %d\n", ret);
                break;
        }
        return ret; // Restituisce il codice di errore
    }
}

nsapi_size_or_error_t EthUDP::receiveFrom(char* buffer, nsapi_size_t size, SocketAddress sender_addr, uint32_t timeout) { //ricevo da un indirizzo ip specifico
    _socket.set_timeout(timeout); // Imposta il timeout per le operazioni di socket
    nsapi_size_or_error_t ret = _socket.recvfrom(&sender_addr, buffer, size); // Tenta di ricevere dati
    
    if (ret >= 0) {
        // Se abbiamo ricevuto dei dati, stampiamo l'indirizzo del mittente
        printf("Dati ricevuti da: %s\n", sender_addr.get_ip_address());
        return ret; // Restituisce il numero di byte ricevuti
    } else {
        // Gestione degli errori in base al codice di ritorno
        switch (ret) {
            case NSAPI_ERROR_WOULD_BLOCK:
                printf("Nessun dato disponibile entro il timeout specificato.\n");
                break;
            case NSAPI_ERROR_NO_SOCKET:
                printf("Nessun socket disponibile per la ricezione.\n");
                break;
            case NSAPI_ERROR_NO_CONNECTION:
                printf("La connessione è stata persa.\n");
                break;
            default:
                printf("Errore nella ricezione: %d\n", ret);
                break;
        }
        return ret; // Restituisce il codice di errore
    }
}

