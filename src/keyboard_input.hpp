#ifndef _KEYBOARD_INPUT_HPP_
#define _KEYBOARD_INPUT_HPP_

#include <windows.h> // GetAsyncKeyState(VK_)

enum EnumKeyboardInput {

    kKeyboardInputUp = 0,
    kKeyboardInputDown,
    kKeyboardInputLeft,
    kKeyboardInputRight,

};

class KeyboardInput {
public:
    int getInput();
};

#endif // _KEYBOARD_INPUT_HPP_