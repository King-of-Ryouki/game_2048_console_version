#ifndef _GAME_VIEW_HPP_
#define _GAME_VIEW_HPP_

#include "keyboard_input.hpp"

#include <iomanip> // setw()
#include <iostream>
#include <string.h> // memset()

using std::cin;
using std::cout;
using std::endl;
using std::setw;

enum EnumGameStatus {

    kGameContinue = 0,
    kGameWin,
    kGameOver

};

class GameView {
public:
    bool CreateNumber();
    void GameBoard(); // 棋盤
    int GameState();  // 遊戲狀態
    void Restart();   // 新局

    void ProcessInput(int keyboard_input);
};

#endif // _GAME_VIEW_HPP_