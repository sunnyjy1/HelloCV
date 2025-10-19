#include "Crypto.h"
#include <cctype>
#include <stdexcept>

Crypto::Crypto(Algorithm algo) : currentAlgorithm(algo) {}

void Crypto::setAlgorithm(Algorithm algo) {
    currentAlgorithm = algo;
}

std::string Crypto::encryptText(const std::string& text, const std::string& key) {
    switch(currentAlgorithm) {
        case CAESAR_CIPHER:
            return caesarEncrypt(text, keyToInt(key));
        case XOR_CIPHER:
            return xorEncrypt(text, key);
        default:
            return caesarEncrypt(text, keyToInt(key));
    }
}

std::string Crypto::decryptText(const std::string& text, const std::string& key) {
    switch(currentAlgorithm) {
        case CAESAR_CIPHER:
            return caesarDecrypt(text, keyToInt(key));
        case XOR_CIPHER:
            return xorDecrypt(text, key);
        default:
            return caesarDecrypt(text, keyToInt(key));
    }
}

bool Crypto::encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    return false;
}

bool Crypto::decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    return false;
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

std::string Crypto::caesarDecrypt(const std::string& text, int shift) {
    return caesarEncrypt(text, 26 - (shift % 26));
}

std::string Crypto::xorEncrypt(const std::string& text, const std::string& key) {
    if(key.empty()) return text;
    
    std::string result;
    size_t keyLength = key.length();
    
    for(size_t i = 0; i < text.length(); ++i) {
        result += text[i] ^ key[i % keyLength];
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
