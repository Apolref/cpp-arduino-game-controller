#pragma once

#include "GamepadState.h"

/*
  KeyboardMapper

  Responsible for translating GamepadState into
  keyboard events using the Windows API (SendInput).

  This is optional: you can just log the button states.
*/

class KeyboardMapper {
public:
    KeyboardMapper();

    // Call this regularly with the latest state.
    // It compares with the previous state and sends
    // key press/release events only on transitions.
    void update(const GamepadState& state);

private:
    GamepadState lastState;

    void pressKey(WORD vkCode);
    void releaseKey(WORD vkCode);
};
