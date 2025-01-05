#include <iostream>     // cin, cout
#include <conio.h>      // 使用者輸入
#include <windows.h>    // 操作視窗: Sleep(), GetCurrentProcessId(), 用戶輸入: GetKeyState(), SetCursorPos()
#include <string>       // string(不是容器)特殊化類別
#include <vector>       // vector容器
#include <utility>      // 用於pair(我有用到嗎???)
#include "DoCollision.h"// 碰撞處理

using namespace std;

bool rungame = true;

// 光標位置
COORD coord;

// 劇情文本
struct text
{
    string speaker;
    string sentence;
    string tip;
};
vector <text>  opening = {
    {"旁白：", "你好，", ""}, {"旁白：你好，", "歡迎來到這個世界。", ""},
    {"旁白：", "讓我帶你一步步熟悉它吧！", ""}
};

vector <text>  chapter1 = {
    {"旁白：", "第一步，", ""}, {"旁白：第一步，", "使用方向鍵來移動。", ""},
    {"旁白：", "簡單的開始，", ""}, {"旁白：簡單的開始，", "剩下的就交給你囉！", "提示：使用方向鍵移動，走出這個迷宮。"}
};
vector <text>  chapter2 = {
    {"旁白：", "恭喜你通過第一關，", ""}, {"旁白：恭喜你通過第一關，", "讓我們增加難度吧！", "提示：走出困難的迷宮，祝你好運！"}
};

vector <text> story[2] = {
    chapter1,
    chapter2
};
int chapter;

// 會動的物件(玩家, 怪物)
struct item
{
    int x;
    int y;
};
item player;

// 迷宮(不會動的物件: 地形)
struct Maze {
    item PlayerStart;               // 每一關的玩家出生點
    vector<vector<string>> terrain; // 每一關的地形
};
Maze maze[2] = {
    // 第一關迷宮
    {
        {1, 1},
        {
            {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
            {"牆", "　", "　", "牆", "牆", "牆", "　", "　", "　", "　", "　", "牆"},
            {"牆", "牆", "　", "　", "　", "　", "　", "牆", "牆", "牆", "門", "牆"},
            {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
        }
    },
    // 第二關迷宮
    {
        {1, 1},
        {
            {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
            {"牆", "　", "　", "　", "牆", "　", "　", "　", "　", "　", "　", "牆"},
            {"牆", "牆", "牆", "　", "牆", "　", "牆", "牆", "牆", "牆", "　", "牆"},
            {"牆", "　", "　", "　", "　", "　", "牆", "　", "　", "牆", "　", "牆"},
            {"牆", "　", "牆", "牆", "牆", "　", "牆", "牆", "　", "牆", "　", "牆"},
            {"牆", "　", "　", "　", "牆", "　", "　", "　", "　", "牆", "　", "牆"},
            {"牆", "牆", "牆", "　", "牆", "牆", "牆", "牆", "　", "牆", "　", "牆"},
            {"牆", "　", "　", "　", "　", "　", "　", "牆", "　", "牆", "　", "牆"},
            {"牆", "　", "牆", "牆", "牆", "牆", "　", "牆", "　", "牆", "　", "牆"},
            {"牆", "　", "　", "　", "　", "牆", "　", "　", "　", "牆", "門", "牆"},
            {"牆", "牆", "牆", "牆", "　", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
            {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"}
        }
    }
};

// 設置
void HideCursor();                                      // 隱藏光標，增加流暢度(只用一次而已，之後沒用了)

// 展示資訊
void ToLevel();                                         // 展示當前章節
void read(vector <text> content);                       // 讀文本，展示劇情(使用say，其實就只是一句句說出來而已......)
void say(string speaker, string sentence, string tip);  // 幫助劇情展示，或是單純用來顯示文字
void DrawMaze(int chapter, int show);                   // 顯示、更新操作後的地圖

// 處理玩家移動
void CheckInput();                                      // 遊戲核心(使用者互動) ———— 偵測玩家按了什麼
void MovePlayer(short dx, short dy);                    // 若玩家按下方向鍵，處理玩家的移動，以及和各種物件的互動



/////程式開始/////

int main()
{
    system("cls");
    HideCursor();

    read(opening);

    chapter = 1;
    ToLevel();

    while (rungame)
    {
        CheckInput();   // 遊戲核心

        Sleep(100);     // 控制迴圈速度
    }

    return 0;
}


/////函式定義/////

// 設置
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE; // 設置光標為不可見
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    return;
}

// 展示資訊
void ToLevel()
{
    system("cls");

    // 好習慣，先給玩家位置再DrawMaze。
    player = maze[chapter].PlayerStart;
    DrawMaze(chapter-1, 1);

    Sleep(2000);
    // 展示地圖
    read(story[chapter-1]);

    // 固定顯示當前提示, 資訊(因為read完就會消失，需要一個穩定的資訊欄)


    return;
}

void DrawMaze(int chapter, int way)
{
    // 設定光標位置
    coord = {0, 3};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int i = 0; i < maze[chapter].terrain.size(); i++)
    {
        for (int j = 0; j < maze[chapter].terrain[i].size(); j++)
        {
            if (i == player.y && j == player.x)
            {
                cout << "我";
            } else {
                switch (way)
                {
                    case 0:
                        cout << maze[chapter].terrain[i][j];    // 無延遲顯示(用來更新互動結果)
                        break;
                    case 1:
                        Sleep(10);
                        cout << maze[chapter].terrain[i][j];    // 有延遲顯示(用來展示地圖)
                        break;
                    case 2:
                        Sleep(10);
                        cout << "　";                   // 地圖一塊塊消失(只留下"我")
                        break;
                }
            }
        }

        cout << endl;
    }

    return;
}

void read(vector <text> content)
{
    for (int i = 0; i < content.size(); i++)
    {
        say(content[i].speaker, content[i].sentence, content[i].tip); // 顯示對話, 提示
    }

    return;
}

void say(string speaker, string sentence, string tip)
{
    // 角色說出台詞
    coord = {0, 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    cout << speaker;                            // 角色：
    for (int i = 0; i < sentence.length(); i++) // 　　　台詞
    {
        cout << sentence[i];

        Sleep(50); // 讓每個字顯示有延遲
    }
    Sleep(1000);
    cout << "\r" << string(speaker.length() + sentence.length(), ' ') << "\r"; // 清除該行內容

    // 顯示顯示提示
    coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    cout << tip;

    return;
}

// 處理玩家移動
void CheckInput()
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

    //座標平面
    //0x+
    //y
    //+
}

void MovePlayer(short dx, short dy)
{
    short newX = player.x + dx;
    short newY = player.y + dy;

    // 檢查是否撞到牆
    if (maze[chapter].terrain[newY][newX] == "牆") {
        return;
    }

    // 檢查是否到達"門"
    if (maze[chapter].terrain[newY][newX] == "門") {
        player.x = newX;
        player.y = newY;
        DrawMaze(chapter, 0);   // "我"取代門
        Sleep(1000);

        DrawMaze(chapter-1, 2); // 清空舊地圖
        chapter += 1;
        ToLevel();              // 前往下一關, 畫地圖, 展示劇情
        return;
    }

    // 更新玩家位置
    player.x = newX;
    player.y = newY;
    DrawMaze(chapter, 0);

    return;
}
