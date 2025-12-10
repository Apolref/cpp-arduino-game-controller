#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "SerialClient.h"
#include "GamepadState.h"
#include "KeyboardMapper.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: pc-client <COM_PORT>\n";
        std::cerr << "Example: pc-client COM3\n";
        return 1;
    }

    std::string portName = argv[1];

    std::cout << "Opening serial port: " << portName << "...\n";
    SerialClient serial(portName);

    if (!serial.isConnected()) {
        std::cerr << "Failed to open serial port.\n";
        return 1;
    }

    std::cout << "Connected. Reading gamepad data...\n";

    KeyboardMapper mapper;
    GamepadState state;

    while (true) {
        uint8_t byte = 0;
        if (serial.readByte(byte)) {
            state.fromMask(byte);
            std::cout << "\r" << state.toString() << "   " << std::flush;

            // Optional: map to keyboard
            mapper.update(state);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
