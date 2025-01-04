#ifndef player_move_H
#define player_move_H

#include <iostream>
#include <windows.h>
#include "maze.h" // 包含迷宮資訊

using namespace std;

// 函數宣告
// 讀取玩家輸入
void Check_input()
{
    if (_kbhit()) {
        int key = _getch();
        switch (key) {
            case 72:  // 上
                MovePlayer(0, -1);
                break;
            case 80:  // 下
                MovePlayer(0, 1);
                break;
            case 75:  // 左
                MovePlayer(-1, 0);
                break;
            case 77:  // 右
                MovePlayer(1, 0);
                break;
        }
    }

    return;
}

// 處理玩家移動
void MovePlayer(int dx, int dy) 
{
    int newX = playerX + dx;
    int newY = playerY + dy;

    // 檢查是否撞到牆
    if ((level == 1 && maze1[newY][newX] != "　" && maze1[newY][newX] != "門") ||
        (level == 2 && maze2[newY][newX] != "　" && maze2[newY][newX] != "門")) {
        return;
    }

    // 檢查是否到達終點
    if ((level == 1 && maze1[newY][newX] == "門") ||
        (level == 2 && maze2[newY][newX] == "門")) {
        NextLevel();
        return;
    }

    // 更新玩家位置
    if (level == 1) {
        maze1[playerY][playerX] = "　";  // 原位置清空
        maze1[newY][newX] = "我";  // 新位置標記玩家
    } else if (level == 2) {
        maze2[playerY][playerX] = "　";  // 原位置清空
        maze2[newY][newX] = "我";  // 新位置標記玩家
    }

    playerX = newX;
    playerY = newY;

    return;
}

// 切換到下一關
void NextLevel()
{
    // 顯示通關訊息並進入下一關
    system("cls");
    say(narrator, "恭喜你完成了這一關！\n");
    Sleep(2000);  // 顯示通關訊息

    if (level == 1) {
        level = 2;  // 進入第二關
        playerX = 1;
        playerY = 1;
    } else {
        system("cls");
        say(narrator, "恭喜你完成了所有關卡！\n");
        Sleep(3000);  // 顯示結束訊息
        exit(0);  // 遊戲結束
    }

    return;
}

#endif // player_move_H
