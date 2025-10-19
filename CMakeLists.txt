cmake_minimum_required(VERSION 3.10)
project(CryptoTool)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(CryptoTool
    src/main.cpp
    src/Crypto.cpp
    src/FileHandler.cpp
    src/Menu.cpp
)

set_target_properties(CryptoTool PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
