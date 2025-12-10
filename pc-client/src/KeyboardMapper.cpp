#include "KeyboardMapper.h"
#include <windows.h>

KeyboardMapper::KeyboardMapper() : lastState{} {}

// Helper to send a single keyboard event
static void sendKeyEvent(WORD vkCode, bool keyDown) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vkCode;
    input.ki.dwFlags = keyDown ? 0 : KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void KeyboardMapper::pressKey(WORD vkCode) {
    sendKeyEvent(vkCode, true);
}

void KeyboardMapper::releaseKey(WORD vkCode) {
    sendKeyEvent(vkCode, false);
}

void KeyboardMapper::update(const GamepadState& state) {
    // Example mapping:
    // UP    -> VK_UP
    // DOWN  -> VK_DOWN
    // LEFT  -> VK_LEFT
    // RIGHT -> VK_RIGHT
    // A     -> VK_SPACE
    // B     -> 'Z'

    auto handleTransition = [&](bool prev, bool curr, WORD vk) {
        if (!prev && curr) {
            pressKey(vk);
        } else if (prev && !curr) {
            releaseKey(vk);
        }
    };

    handleTransition(lastState.up,    state.up,    VK_UP);
    handleTransition(lastState.down,  state.down,  VK_DOWN);
    handleTransition(lastState.left,  state.left,  VK_LEFT);
    handleTransition(lastState.right, state.right, VK_RIGHT);
    handleTransition(lastState.a,     state.a,     VK_SPACE);
    handleTransition(lastState.b,     state.b,     0x5A); // 'Z'

    lastState = state;
}
