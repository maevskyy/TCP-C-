#include <iostream>
#include <stdlib.h>
#include <ws2tcpip.h>

#include "tcp.h"


TCPServer::TCPServer(int port) {

    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsInit = WSAStartup(ver, &wsData);
    if (wsInit != 0) {
        std::cerr << "WSAStartup failed!" << std::endl;
        exit(1);
    }

    SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listeningSocket == INVALID_SOCKET) {
        std::cerr << "Cannot create socket!" << std::endl;
        WSACleanup();
        exit(1);
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(listeningSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(listeningSocket, SOMAXCONN);

    sockaddr_in client;
    int clientSize = sizeof(client);
    clientSocket = accept(listeningSocket, (sockaddr*)&client, &clientSize);
    closesocket(listeningSocket); 
};

std::string TCPServer::startListen() {
    char buf[4096];
    ZeroMemory(buf, 4096);

    int bytesReceived = recv(clientSocket, buf, 4096, 0);
    if (bytesReceived <= 0) {
        return "";
    }

    return std::string(buf, bytesReceived);
};
void TCPServer::respond(const std::string& data) {
    send(clientSocket, data.c_str(), data.size(), 0);
};

void TCPServer::close(){
    closesocket(this->clientSocket);
    WSACleanup();
};

TCPServer::~TCPServer() {
    this->close();
};

