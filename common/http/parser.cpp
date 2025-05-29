#include "parser.h"
#include <string>
#include <sstream>
#include <algorithm>

HttpRequest parseHttpRequest(const std::string& raw) {
    std::istringstream stream(raw);
    HttpRequest request;

    stream >> request.method >> request.path >> request.version;
    stream.ignore();

    std::string line;
    while(std::getline(stream, line) && line != "\r") {
        size_t colon = line.find(":");
        if(colon != std::string::npos) {
            std::string key = line.substr(0, colon);
            std::string value = line.substr(colon + 1);
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
            value.erase(0, value.find_first_not_of(" \t\r"));
            value.erase(value.find_last_not_of(" \t\r") + 1);
            request.headers[key] = value;
        }
    }

    std::getline(stream, request.body, '\0');

    return request;
}