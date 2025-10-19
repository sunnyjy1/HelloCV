#ifndef MENU_H
#define MENU_H

#include "Crypto.h"
#include "FileHandler.h"
#include <iostream>

class Menu {
public:
    Menu();
    void showMainMenu();
    void run();
    
private:
    Crypto crypto;
    
    void handleTextEncryption();
    void handleTextDecryption();
    void handleFileEncryption();
    void handleFileDecryption();
    void handleAlgorithmSelection();
    
    void clearInputBuffer();
    std::string getInput(const std::string& prompt);
};

#endif
