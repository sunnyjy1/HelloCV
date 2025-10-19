#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::string FileHandler::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if(!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filePath);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool FileHandler::writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if(!file.is_open()) {
        return false;
    }
    
    file << content;
    file.close();
    return true;
}

bool FileHandler::fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}
