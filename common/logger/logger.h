#pragma once

#include <iostream>
#include <string>

inline void log(const std::string& message, const std::string& level = "LOG"){
    std::cout << "[" << level << "]" << message << std::endl;
};