#include "Menu.h"
#include <iostream>
#include <limits>

Menu::Menu() : crypto(Crypto::CAESAR_CIPHER) {}

void Menu::showMainMenu() {
    std::cout << "\n=== 文本加密解密工具 ===\n";
    std::cout << "1. 文本加密\n";
    std::cout << "2. 文本解密\n";
    std::cout << "3. 文件加密\n";
    std::cout << "4. 文件解密\n";
    std::cout << "5. 选择加密算法\n";
    std::cout << "6. 退出\n";
    std::cout << "请选择操作 (1-6): ";
}

void Menu::run() {
    int choice = 0;
    
    while(true) {
        showMainMenu();
        std::cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                handleTextEncryption();
                break;
            case 2:
                handleTextDecryption();
                break;
            case 3:
                handleFileEncryption();
                break;
            case 4:
                handleFileDecryption();
                break;
            case 5:
                handleAlgorithmSelection();
                break;
            case 6:
                std::cout << "感谢使用，再见！\n";
                return;
            default:
                std::cout << "无效选择，请重新输入！\n";
        }
    }
}

void Menu::handleTextEncryption() {
    std::string text = getInput("请输入要加密的文本: ");
    std::string key = getInput("请输入密钥: ");
    
    try {
        std::string encrypted = crypto.encryptText(text, key);
        std::cout << "加密结果: " << encrypted << std::endl;
    } catch(const std::exception& e) {
        std::cout << "加密过程中发生错误: " << e.what() << std::endl;
    }
}

void Menu::handleTextDecryption() {
    std::string text = getInput("请输入要解密的文本: ");
    std::string key = getInput("请输入密钥: ");
    
    try {
        std::string decrypted = crypto.decryptText(text, key);
        std::cout << "解密结果: " << decrypted << std::endl;
    } catch(const std::exception& e) {
        std::cout << "解密过程中发生错误: " << e.what() << std::endl;
    }
}

void Menu::handleFileEncryption() {
    std::string inputFile = getInput("请输入要加密的文件路径: ");
    std::string outputFile = getInput("请输入输出文件路径: ");
    std::string key = getInput("请输入密钥: ");
    
    try {
        if(!FileHandler::fileExists(inputFile)) {
            std::cout << "输入文件不存在！\n";
            return;
        }
        
        std::string content = FileHandler::readFile(inputFile);
        std::string encrypted = crypto.encryptText(content, key);
        
        if(FileHandler::writeFile(outputFile, encrypted)) {
            std::cout << "文件加密成功！结果已保存到: " << outputFile << std::endl;
        } else {
            std::cout << "文件写入失败！\n";
        }
    } catch(const std::exception& e) {
        std::cout << "文件加密过程中发生错误: " << e.what() << std::endl;
    }
}

void Menu::handleFileDecryption() {
    std::string inputFile = getInput("请输入要解密的文件路径: ");
    std::string outputFile = getInput("请输入输出文件路径: ");
    std::string key = getInput("请输入密钥: ");
    
    try {
        if(!FileHandler::fileExists(inputFile)) {
            std::cout << "输入文件不存在！\n";
            return;
        }
        
        std::string content = FileHandler::readFile(inputFile);
        std::string decrypted = crypto.decryptText(content, key);
        
        if(FileHandler::writeFile(outputFile, decrypted)) {
            std::cout << "文件解密成功！结果已保存到: " << outputFile << std::endl;
        } else {
            std::cout << "文件写入失败！\n";
        }
    } catch(const std::exception& e) {
        std::cout << "文件解密过程中发生错误: " << e.what() << std::endl;
    }
}

void Menu::handleAlgorithmSelection() {
    std::cout << "\n选择加密算法:\n";
    std::cout << "1. Caesar Cipher (凯撒密码)\n";
    std::cout << "2. XOR Cipher (异或加密)\n";
    std::cout << "请选择算法 (1-2): ";
    
    int choice;
    std::cin >> choice;
    clearInputBuffer();
    
    switch(choice) {
        case 1:
            crypto.setAlgorithm(Crypto::CAESAR_CIPHER);
            std::cout << "已选择 Caesar Cipher 算法\n";
            break;
        case 2:
            crypto.setAlgorithm(Crypto::XOR_CIPHER);
            std::cout << "已选择 XOR Cipher 算法\n";
            break;
        default:
            std::cout << "无效选择，保持当前算法\n";
    }
}

void Menu::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string Menu::getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}
