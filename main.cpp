#include "common/server/server.h"
#include "common/logger/logger.h"

int main() {

    Server app;

    app.get("/hello", [](){
        log("Handling hello");
    });

    app.startServer(5400);

    return 0;
};