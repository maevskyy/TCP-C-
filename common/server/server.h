#pragma once

#include <string>
#include <map>
#include <functional>

class Server {
    public:
        Server();
        ~Server();

        void startServer(int port);
        void get(const std::string& path, std::function<void()> callback) ;

    private:
        std::map<std::string, std::function<void()>> routes;
};