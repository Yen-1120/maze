// 處理玩家移動，物件互動交由 maze.h 處理

#ifndef player_move_H
#define player_move_H

#include <iostream>
#include <windows.h>
#include "maze.h"

using namespace std;

// 取得主控台句柄
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// NPC結構體
struct Role
{
    string name; // 顯示名稱
    COORD where; // 顯示位置
};

// 函數宣告
void say(Role speaker, string sentence) // 顯示對話
{
    // 設定說話者(光標)位置
    COORD coord = speaker.where;
    SetConsoleCursorPosition(hConsole, coord);

    // 顯示說話者名稱
    cout << speaker.name << ": ";

    for (int i = 0; i < sentence.length(); i++)
    {
        cout << sentence[i];
        Sleep(100); // 讓每個字顯示有延遲
    }

    return;
}

#endif // player_move_H