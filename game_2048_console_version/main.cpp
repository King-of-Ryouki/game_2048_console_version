// ******************************
// *
// * Date     : 2018/07/07
// *
// * Author   : 施冠年
// * mail     : Co6901251@gmail.com
// *
// * function :
// *
// * 2048 console ver
// *
// * 2048 命令提示字元版
// *
// ******************************

#include "game_view_old.hpp"
// #include "game_view.hpp"

using std::cout;
using std::endl;

int main() {

    GameView gameView;
    KeyboardInput KeyboardInput;

    // Game init
    gameView.CreateNumber();
    gameView.CreateNumber();
    gameView.GameBoard();

    // Runing game
    while (true) {

        if (gameView.GameState() == kGameContinue) {

            gameView.ProcessInput(KeyboardInput.getInput());
            gameView.CreateNumber();
            gameView.GameBoard();
            Sleep(80);

        } else if (gameView.GameState() == kGameWin) {

            gameView.GameBoard();
            cout << "\nWin !" << endl;
            gameView.Restart();

        } else if (gameView.GameState() == kGameOver) {

            gameView.GameBoard();
            cout << "\nGameOver !" << endl;
            gameView.Restart();
        }
    }

    return 0;
}