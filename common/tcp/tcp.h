#pragma once

#include <string>
#include <ws2tcpip.h>

class TCPServer {
    public:
        TCPServer(int port);
        ~TCPServer();
    
        std::string startListen();
        void respond(const std::string& data);
        void close();

    private:
        int port;
        SOCKET serverSocket;
        SOCKET clientSocket;
};