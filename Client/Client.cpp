#include <iostream> // cout
#include <sys/socket.h> // sockaddr, socklen_t
#include <stdlib.h> // atoi
#include <netinet/in.h> // sockaddr_in
#include <string.h> // strlen
#include <unistd.h> // read, close
#include <arpa/inet.h> // inet_ntoa
#include "Message.cpp"

class Client {
    int sock;
    struct sockaddr_in serverAddress;
public:
    bool initClient() {
        //Crear el socket:
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;

        string ip = "172.17.3.175";
        //Dirección del servidor:

        memset(&serverAddress, '0', sizeof(serverAddress)); // Limpia estructura serverAddress
        serverAddress.sin_family = AF_INET; // Address Family IPv4
        serverAddress.sin_port = htons(port); // Puerto de Endian de Host a Endian de Network

        if(inet_aton(ip.c_str(), &serverAddress.sin_addr) <= 0) {
            return false;
        }

        return true;
    }

    bool connection() {
        if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) return false;
        return true;
    }

    Message* receive() {
        const int bufferSize = 1024;
        while(true) {
            char buffer[bufferSize] = {0};

            while(recv(sock, buffer, sizeof(buffer), 0) <= 0);
            std::cout << " >> " << buffer << '\n';
        }
        /*if (n > 0) {
            Message* m = new Message;
            m->text = buffer;
            return m;
        } else {
            return NULL;
        }*/
    }

    void sendClient(Message* message) {
        const char* m = message->text.c_str();

        send(sock, m, strlen(m), 0);
    }

    void end() {
        close(sock);
    }
};
