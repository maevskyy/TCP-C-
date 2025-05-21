#include <iostream>
#include <stdlib.h>
#include <ws2tcpip.h>

// g++ server.cpp -lws2_32

int main () {

    // intialize winsock
    WSADATA wsData;
    WORD version = MAKEWORD(2, 2);

    int wsok = WSAStartup(version, &wsData);
    if(wsok != 0)
    {
        std::cerr << "Cant intitialice winsock! Quitting" << std::endl;
        return 1;
    }


    // create a socket 
    SOCKET listeting_socket = socket(
        AF_INET, // Address family (ip4)
        SOCK_STREAM, // Protocol ( TCP )
        0 // Protocol ( 0 stand for, choose automatically ( TCP ) )
    );

    if(listeting_socket == INVALID_SOCKET)
    {
        std::cerr << "Cant create a socket! Quitting" << std::endl;
        return 1;
    }


    // bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;  // counld als use inet_pton ...

    bind(listeting_socket, (sockaddr*)&hint, sizeof(hint));


    // tell winsock the socket is for listening 
    listen(listeting_socket, SOMAXCONN);


    // wait for a connection
    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listeting_socket, (sockaddr*)&client, &clientSize);
    if(clientSocket == INVALID_SOCKET) 
    {
        std::cerr << "Invalid client socket! Quitting" << std::endl;
        return 1;
    }

    char host[NI_MAXHOST]; // client remote name
    char service[NI_MAXSERV]; // server (i.e port) the client is connect on

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXSERV);

    int nameInfo = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0);

    if(nameInfo != 0) {
        std::cout << inet_ntoa(client.sin_addr)
                << " connected on port "
                << ntohs(client.sin_port)
                << std::endl;
    } else {
        std::cout << host << " connected on port " << service << std::endl;
    }


    // close listeting socket
    closesocket(listeting_socket);


    // while loop: accept message and send hello world
    char buf[4096];
    while (true)
    {
        ZeroMemory(buf, 4096);

        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            std::cerr << "Error in recv()! Quitting" << std::endl;
            break;
        }

        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected " << std::endl;
            break;
        }

        std::string httpResponse =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 12\r\n"
            "Connection: close\r\n"
            "\r\n"
            "Hello world";

        send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);
        break;
    }


    // close socket
    closesocket(clientSocket);


    // cleanup winsock
    WSACleanup();
}