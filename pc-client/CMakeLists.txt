cmake_minimum_required(VERSION 3.12)
project(pc_client_gamepad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pc-client
    src/main.cpp
    src/GamepadState.h
    src/SerialClient.h
    src/SerialClient.cpp
    src/KeyboardMapper.h
    src/KeyboardMapper.cpp
)

if (MSVC)
    target_compile_options(pc-client PRIVATE /W4)
else()
    target_compile_options(pc-client PRIVATE -Wall -Wextra -pedantic)
endif()
