#pragma once

#include <string>
#include <map>

struct HttpResponse
{
    int statusCode = 200;
    std::string statusText = "OK";
    std::map<std::string, std::string> headers;
    std::string body;

    HttpResponse& status(int code);
    HttpResponse& setHeader(const std::string& key, const std::string& value);
    HttpResponse& send(const std::string& responseBody);
    std::string toString();
};
