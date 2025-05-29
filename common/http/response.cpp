#include "response.h"
#include <sstream>

HttpResponse& HttpResponse::status(int code) {
    statusCode = code;

    switch (code)
    {
    case 200: statusText = "OK"; break;
    case 201: statusText = "Created"; break;
    case 204: statusText = "No Content"; break;
    case 400: statusText = "Bad Request"; break;
    case 404: statusText = "Not Found"; break;
    case 500: statusText = "Internal Server Error"; break;
    
    default: statusText = ""; break;
    }

    return *this;
};

HttpResponse& HttpResponse::setHeader(const std::string& key, const std::string& value) {
    headers[key] = value;
    return *this;
}

HttpResponse& HttpResponse::send(const std::string& responseBody) {
    body = responseBody;
    return *this;
}

std::string HttpResponse::toString() {
    std::ostringstream ss;

    ss << "HTTP/1.1 " << statusCode << " " << statusText << "\r\n";

    for(const auto& [key, value] : headers) {
        ss << key << ": " << value << "\r\n";
    }

    ss << "Content-Length: " << body.size() << "\r\n";
    ss << "Connection: close\r\n";

    ss << "\r\n";
    ss << body;

    return ss.str();
}