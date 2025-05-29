#include "server.h"
#include "../tcp/tcp.cpp"
#include "../logger/logger.h"
#include "../http/parser.h"

#include <iostream>

Server::Server() {
    log("Server Initialized");
};
Server::~Server() {
    log("Server destroyed");
};

void Server::get(const std::string& path, Handler callback){
    log("Get route registered" + std::string(path));
    std::string key = "GET" + path;
    this->routes[key] = callback;
};

void Server::startServer(int port){
    TCPServer tcp(port);

    std::string rawBytes = tcp.startListen();

    HttpRequest req = parseHttpRequest(rawBytes);
    HttpResponse res;

    std::string key = req.method + req.path;

    if(routes.count(key)) {
        routes[key](req, res);
    }

    tcp.respond(res.toString());
    tcp.close();

    log("Starting server on port" + std::to_string(port));
};