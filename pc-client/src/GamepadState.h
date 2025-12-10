#pragma once

#include <cstdint>
#include <string>

struct GamepadState {
    bool up    = false;
    bool down  = false;
    bool left  = false;
    bool right = false;
    bool a     = false;
    bool b     = false;

    void fromMask(uint8_t mask) {
        up    = mask & (1 << 0);
        down  = mask & (1 << 1);
        left  = mask & (1 << 2);
        right = mask & (1 << 3);
        a     = mask & (1 << 4);
        b     = mask & (1 << 5);
    }

    std::string toString() const {
        return "UP:"    + std::string(up    ? "1" : "0") +
             " DOWN:"   + std::string(down  ? "1" : "0") +
             " LEFT:"   + std::string(left  ? "1" : "0") +
             " RIGHT:"  + std::string(right ? "1" : "0") +
             " A:"      + std::string(a     ? "1" : "0") +
             " B:"      + std::string(b     ? "1" : "0");
    }
};
