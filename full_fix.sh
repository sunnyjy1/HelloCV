#!/bin/bash
echo "=== 完全修复项目 ==="

# 备份旧文件（可选）
mkdir -p backup
cp src/*.cpp backup/ 2>/dev/null || true
cp include/*.h backup/ 2>/dev/null || true

# 重新创建所有核心文件

# 1. 创建 CMakeLists.txt
cat > CMakeLists.txt << 'END'
cmake_minimum_required(VERSION 3.10)
project(CryptoTool)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(CryptoTool
    src/main.cpp
    src/Crypto.cpp
)

set_target_properties(CryptoTool PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/bin
)
END

# 2. 创建 Crypto.h
cat > include/Crypto.h << 'END'
#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

class Crypto {
public:
    enum Algorithm {
        CAESAR_CIPHER,
        XOR_CIPHER
    };

    Crypto(Algorithm algo = CAESAR_CIPHER);
    std::string encryptText(const std::string& text, const std::string& key);
    std::string decryptText(const std::string& text, const std::string& key);

private:
    Algorithm currentAlgorithm;
    std::string caesarEncrypt(const std::string& text, int shift);
    int keyToInt(const std::string& key);
};

#endif
END

# 3. 创建简化的 Crypto.cpp
cat > src/Crypto.cpp << 'END'
#include "Crypto.h"
#include <cctype>

Crypto::Crypto(Algorithm algo) : currentAlgorithm(algo) {}

std::string Crypto::encryptText(const std::string& text, const std::string& key) {
    return caesarEncrypt(text, keyToInt(key));
}

std::string Crypto::decryptText(const std::string& text, const std::string& key) {
    int shift = keyToInt(key);
    return caesarEncrypt(text, 26 - (shift % 26));
}

std::string Crypto::caesarEncrypt(const std::string& text, int shift) {
    std::string result;
    shift = shift % 26;
    
    for(char c : text) {
        if(std::isalpha(c)) {
            char base = std::islower(c) ? 'a' : 'A';
            c = static_cast<char>((c - base + shift) % 26 + base);
        }
        result += c;
    }
    return result;
}

int Crypto::keyToInt(const std::string& key) {
    if(key.empty()) return 0;
    int result = 0;
    for(char c : key) {
        result += static_cast<int>(c);
    }
    return result % 26;
}
END

# 4. 创建简化的 main.cpp
cat > src/main.cpp << 'END'
#include <iostream>
#include "Crypto.h"

int main() {
    Crypto crypto;
    std::string encrypted = crypto.encryptText("Hello", "3");
    std::string decrypted = crypto.decryptText(encrypted, "3");
    
    std::cout << "加密: " << encrypted << std::endl;
    std::cout << "解密: " << decrypted << std::endl;
    return 0;
}
END

echo "修复完成！"
END
