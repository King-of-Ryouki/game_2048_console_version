#include "keyboard_input.hpp"

int KeyboardInput::getInput() {

    int keyboard_input;

    while (true) {

        if (GetAsyncKeyState(VK_UP)) {
            keyboard_input = kKeyboardInputUp;
            break;
        } else if (GetAsyncKeyState(VK_DOWN)) {
            keyboard_input = kKeyboardInputDown;
            break;
        } else if (GetAsyncKeyState(VK_LEFT)) {
            keyboard_input = kKeyboardInputLeft;
            break;
        } else if (GetAsyncKeyState(VK_RIGHT)) {
            keyboard_input = kKeyboardInputRight;
            break;
        }
    }

    return keyboard_input;
}