#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <vector>

class Crypto {
public:
    // 加密方法枚举
    enum Algorithm {
        CAESAR_CIPHER,
        XOR_CIPHER
    };

    // 构造函数
    Crypto(Algorithm algo = CAESAR_CIPHER);
    
    // 设置加密算法
    void setAlgorithm(Algorithm algo);
    
    // 文本加密
    std::string encryptText(const std::string& text, const std::string& key);
    
    // 文本解密
    std::string decryptText(const std::string& text, const std::string& key);
    
    // 文件加密
    bool encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    
    // 文件解密
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);

private:
    Algorithm currentAlgorithm;
    
    // Caesar Cipher 加密
    std::string caesarEncrypt(const std::string& text, int shift);
    
    // Caesar Cipher 解密
    std::string caesarDecrypt(const std::string& text, int shift);
    
    // XOR 加密
    std::string xorEncrypt(const std::string& text, const std::string& key);
    
    // XOR 解密（与加密相同）
    std::string xorDecrypt(const std::string& text, const std::string& key);
    
    // 从字符串密钥转换为整数（用于Caesar Cipher）
    int keyToInt(const std::string& key);
};

#endif
