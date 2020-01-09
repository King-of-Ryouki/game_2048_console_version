#include "game_view.hpp"

const int kGameView_H = 4;
const int kGameView_W = 4;

int game_board[ kGameView_H ][ kGameView_W ];

bool GameView::CreateNumber() {

    int create_x_num; // 生成 x 軸的數字
    int create_y_num; // 生成 y 軸的數字

    int rand_times     = 0;                         // 隨機次數
    int max_rand_times = kGameView_H * kGameView_W; // 隨機次數上限

    // 生成數字
    do {
        create_y_num = rand() % kGameView_H;
        create_x_num = rand() % kGameView_W;
        ++rand_times;
    } while (game_board[ create_y_num ][ create_x_num ] != 0 &&
             rand_times <= max_rand_times);
    // !
    if (rand_times <= max_rand_times) {
        (rand() % 3 != 0) ? game_board[ create_y_num ][ create_x_num ] = 2  // (2/3) Create 2
                          : game_board[ create_y_num ][ create_x_num ] = 4; // (1/3) Create 4
    } else {
        return false;
    }

    return true;
}

// 棋盤
void GameView::GameBoard() {

    system("cls"); // 清空螢幕

    cout << "---------------------------------" << endl;

    for (int y = 0; y < kGameView_H; ++y) {
        for (int x = 0; x < kGameView_W; ++x) {
            (game_board[ y ][ x ] == 0)
                ? cout << "|" << setw(8)
                : cout << "|" << setw(5) << game_board[ y ][ x ] << "  ";
        }

        cout << "|" << endl;
        cout << "---------------------------------" << endl;
    }
}

//? 優化中
// 遊戲狀態
int GameView::GameState() {

    // 獲勝或繼續
    for (int y = 0; y < kGameView_H; ++y) {
        for (int x = 0; x < kGameView_W; ++x) {

            if (game_board[ y ][ x ] == 2048) {
                return kGameWin;
                break;
            } else if (game_board[ y ][ x ] == 0) {
                return kGameContinue;
                break;
            }
        }
    }

    // 判斷左右是否還可移動
    for (int y = 0; y < kGameView_H; ++y) {
        for (int x = 0; x < kGameView_W - 1; ++x) {

            if ((game_board[ y ][ x ] == game_board[ y ][ x + 1 ])) {
                return kGameContinue;
                break;
            }
        }
    }

    // 判斷上下是否還可移動
    for (int x = 0; x < kGameView_W; ++x) {
        for (int y = 0; y < kGameView_H - 1; ++y) {

            if ((game_board[ y ][ x ] == game_board[ y + 1 ][ x ])) {
                return kGameContinue;
                break;
            }
        }
    }

    return kGameOver;
}

// 新局
void GameView::Restart() {

    while (true) {

        cout << "\nRestart? Y/N : ";

        char new_game;
        cin >> new_game;

        if (new_game == 'Y' || new_game == 'y') {

            memset(game_board, 0, sizeof(int) * kGameView_H * kGameView_W); // 清除盤面

            GameView::CreateNumber();
            GameView::CreateNumber();
            GameView::GameBoard();

            break;

        } else if (new_game == 'N' || new_game == 'n') {

            exit(0);

        } else {

            GameView::GameBoard();
            cout << "\nInput error !" << endl;
        }
    }
}

void GameView::ProcessInput(int keyboard_input) {

    // ******************************
    // *
    // * Step :
    // * 1. first line freeze
    // * 2. push numbers to head of the line
    // * 3. == 0 push to topmost, == add, !0 nothing
    // *
    // * 步驟 :
    // * 1. 0 不動, 1 開始 ++i
    // * 2. 從 0 開始合併, ++j
    // * 3. 歷遍
    // *
    // * 本身為 0
    // * 下一格為 0
    // * 大於，不動
    // * 等於
    // *
    // ******************************

    switch (keyboard_input) {

        case kKeyboardInputUp:

            for (int x = 0; x < kGameView_W; ++x) {

                int y = 1;                 // [ 0 + 1 ]
                while (y <= kGameView_H) { // [ max ]

                    if (game_board[ y ][ x ] == 0) { // 本身為 0
                        // 直接跳到 ++y, 可加速
                    } else if (game_board[ y - 1 ][ x ] == 0) { // 下一格為 0

                        game_board[ y - 1 ][ x ] = game_board[ y ][ x ];
                        game_board[ y ][ x ]     = 0;

                        if (1 < y) { // [ 1 ] < x < [ -1 ]
                            --y;
                            continue;
                        }

                    } else if (game_board[ y - 1 ][ x ] == game_board[ y ][ x ]) { // 等於

                        game_board[ y - 1 ][ x ] <<= 1;
                        game_board[ y ][ x ] = 0;
                        if (y < kGameView_W - 1) { ++y; }
                    }

                    ++y;
                }
            }

            break;

        case kKeyboardInputDown:

            for (int x = 0; x < kGameView_W; ++x) {

                int y = kGameView_H - 2; // [ 0 + 1 ]
                while (y >= 0) {         // [ max ]

                    if (game_board[ y ][ x ] == 0) { // 本身為 0
                        // 直接跳到 ++y, 可加速
                    } else if (game_board[ y + 1 ][ x ] == 0) { // 下一格為 0

                        game_board[ y + 1 ][ x ] = game_board[ y ][ x ];
                        game_board[ y ][ x ]     = 0;

                        if (y < kGameView_H - 2) { // [ 1 ] < x < [ -1 ]
                            ++y;
                            continue;
                        }

                    } else if (game_board[ y + 1 ][ x ] == game_board[ y ][ x ]) { // 等於

                        game_board[ y + 1 ][ x ] <<= 1;
                        game_board[ y ][ x ] = 0;
                        if (1 < y) { --y; }
                    }

                    --y;
                }
            }

            break;

        case kKeyboardInputLeft:

            for (int y = 0; y < kGameView_H; ++y) {

                int x = 1;                 // [ 0 + 1 ]
                while (x <= kGameView_W) { // [ max ]

                    if (game_board[ y ][ x ] == 0) { // 本身為 0
                        // 直接跳到 ++x, 可加速
                    } else if (game_board[ y ][ x - 1 ] == 0) { // 下一格為 0

                        game_board[ y ][ x - 1 ] = game_board[ y ][ x ];
                        game_board[ y ][ x ]     = 0;

                        if (1 < x) { // [ 1 ] < x < [ -1 ]
                            --x;
                            continue;
                        }

                    } else if (game_board[ y ][ x - 1 ] == game_board[ y ][ x ]) { // 等於

                        game_board[ y ][ x - 1 ] <<= 1;
                        game_board[ y ][ x ] = 0;
                        if (x < kGameView_W - 1) { ++x; }
                    }

                    ++x;
                }
            }

            break;

        case kKeyboardInputRight:

            for (int y = 0; y < kGameView_H; ++y) {

                int x = kGameView_W - 2; // [ 0 + 1 ]
                while (x >= 0) {         // [ max ]

                    if (game_board[ y ][ x ] == 0) { // 本身為 0
                        // 直接跳到 ++x, 可加速
                    } else if (game_board[ y ][ x + 1 ] == 0) { // 下一格為 0

                        game_board[ y ][ x + 1 ] = game_board[ y ][ x ];
                        game_board[ y ][ x ]     = 0;

                        if (x < kGameView_W - 2) { // [ 1 ] < x < [ -1 ]
                            ++x;
                            continue;
                        }

                    } else if (game_board[ y ][ x + 1 ] == game_board[ y ][ x ]) { // 等於

                        game_board[ y ][ x + 1 ] <<= 1;
                        game_board[ y ][ x ] = 0;
                        if (1 < x) { --x; }
                    }

                    --x;
                }
            }

            break;
    }
}