#pragma once

#include <string>
#include <map>
#include <functional>

#include "../http/request.h"
#include "../http/response.h"

using Handler = std::function<void(HttpRequest&, HttpResponse&)>;

class Server {
    public:
        Server();
        ~Server();

        void startServer(int port);
        void get(const std::string& path, Handler callback) ;

    private:
        std::map<std::string, Handler> routes;
};