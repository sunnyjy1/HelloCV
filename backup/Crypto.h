#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <vector>

class Crypto {
public:
    enum Algorithm {
        CAESAR_CIPHER,
        XOR_CIPHER
    };

    Crypto(Algorithm algo = CAESAR_CIPHER);
    void setAlgorithm(Algorithm algo);
    std::string encryptText(const std::string& text, const std::string& key);
    std::string decryptText(const std::string& text, const std::string& key);
    bool encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);

private:
    Algorithm currentAlgorithm;
    std::string caesarEncrypt(const std::string& text, int shift);
    std::string caesarDecrypt(const std::string& text, int shift);
    std::string xorEncrypt(const std::string& text, const std::string& key);
    std::string xorDecrypt(const std::string& text, const std::string& key) {
        return xorEncrypt(text, key);
    }
    int keyToInt(const std::string& key);
};

#endif
