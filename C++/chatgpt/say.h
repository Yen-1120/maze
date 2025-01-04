// 模擬打字機的方式，處理角色說話

#ifndef say_H
#define say_H

#include <iostream>
#include <windows.h>
using namespace std;

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
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // 顯示說話者名稱
    cout << speaker.name << ": ";

    for (int i = 0; i < sentence.length(); i++)
    {
        cout << sentence[i];
        Sleep(100); // 讓每個字顯示有延遲
    }

    return;
}

#endif // say_H