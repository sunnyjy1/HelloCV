#include <iostream>
#include "Crypto.h"

int main() {
    Crypto crypto;
    std::string result = crypto.encryptText("Hello", "3");
    std::cout << "加密测试: " << result << std::endl;
    return 0;
}
