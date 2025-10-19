#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
public:
    // 读取文件内容
    static std::string readFile(const std::string& filePath);
    
    // 写入文件内容
    static bool writeFile(const std::string& filePath, const std::string& content);
    
    // 检查文件是否存在
    static bool fileExists(const std::string& filePath);
};

#endif
