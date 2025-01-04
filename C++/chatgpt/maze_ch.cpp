#include <iostream>
#include <conio.h>
#include <windows.h>
#include "say.h"         // 包含旁白功能
#include "maze.h"        // 包含迷宮資訊
#include "player_move.h" // 包含移動功能

using namespace std;

// 玩家位置
int playerX = 1, playerY = 1;
int level = 1;  // 記錄當前關卡

// 遊戲迴圈設置
bool rungame = true;

// 旁白角色
Role narrator = {"旁白", {0, 0}};

// 清空螢幕並重新定位光標
void ClearScreen();

// 繪製迷宮
void DrawMaze();

// 隱藏光標函式
void HideCursor();

// 主遊戲迴圈
int main()
{
    system("cls");
    HideCursor();

    // 讓旁白介紹遊戲
    say(narrator, "歡迎來到迷宮遊戲！\n");
    say(narrator, "你需要找到門才能進入下一關。\n");
    system("cls");

    while (rungame) {
        ClearScreen();
        DrawMaze();

        Check_input();

        Sleep(100);  // 控制迴圈速度
    }

    return 0;
}

void ClearScreen()
{
    COORD coord = {0, 0}; // 設定光標位置
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawMaze()
{
    const char* (*currentMaze)[WIDTH];
    if (level == 1) {
        currentMaze = maze1;
    } else {
        currentMaze = maze2;
    }

    // 繪製迷宮
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            cout << currentMaze[y][x];
        }
        cout << endl;
    }

    // 顯示關卡資訊（在迷宮下方第二排）
    cout << endl; // 空出一行
    cout << "當前關卡: " << level << endl;
    cout << "Use Arrow Keys to move." << endl;
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE; // 設置光標為不可見
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

