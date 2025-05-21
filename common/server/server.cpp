#include "server.h"
#include "../logger/logger.h"

#include <iostream>

Server::Server() {
    log("Server Initialized");
};
Server::~Server() {
    log("Server destroyed");
};

void Server::get(const std::string& path, std::function<void()> callback){
    log("Get route registered" + std::string(path));
    std::string key = "GET" + path;
    this->routes[key] = callback;
};

void Server::startServer(int port){
    log("Starting server on port" + std::to_string(port));
};