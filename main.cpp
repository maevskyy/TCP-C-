#include "common/server/server.h"
#include "common/logger/logger.h"

int main() {

    Server app;

    app.get("/hello", [](HttpRequest& req, HttpResponse& res){
        res.send("Hello");
    });

    app.get("/", [](HttpRequest& req, HttpResponse& res){
        res.send("Main");
    });

    app.startServer(5400);

    return 0;
};