#include <iostream>     // 
#include <conio.h>      // 
#include <windows.h>    // 
#include <string>       // 
#include <vector>       // 
#include <utility>      // 

using namespace std;
using Maze = vector<vector<string>>;

bool rungame = true;

struct text
{
    string speaker;
    string sentence;
};
vector <text>  opening = {
    {"旁白：", "你好，"}, {"旁白：你好，", "歡迎來到這個世界。"},
    {"旁白：", "讓我帶你一步步熟悉它吧！"}
};
vector <text>  chapter1 = {
    {"旁白：", "使用方向鍵來移動"},
    
};
vector <text>  chapter2 = {
    
};

vector <text> story[3] = {
    opening,
    chapter1,
    chapter2
};
int chapter;

Maze maze[2] = {
    // 第一關迷宮
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
        {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
    },
    // 第二關迷宮
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
        {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
    }
};

struct item
{
    int x;
    int y;
};
item player;

void HideCursor();                          // 隱藏光標，增加流暢度(只用這一次而已，之後沒用了)
void read(vector <text> content);           // 讀文本，展示劇情(使用say)
void say(string speaker, string sentence);  // 幫助劇情展示，或是單純用來顯示文字
void DrawMaze(int chapte, int show);        // 顯示、更新操作後的地圖
void CheckInput();                          // 遊戲核心(使用者互動) ———— 偵測玩家按了什麼
void MovePlayer(short dx, short dy);        // 若玩家按下方向鍵，處理玩家的移動，以及和各種物件的互動

// 光標位置
COORD coord;

/////程式開始/////

int main()
{
    system("cls");
    HideCursor();

    chapter = 0;
    read(story[chapter]);
    player = {1, 1}; // 好習慣，先給玩家位置再DrawMaze。
    DrawMaze(chapter, 1);

    while (rungame)
    {
        CheckInput();

        Sleep(100);  // 控制迴圈速度
    }

    return 0;
}


/////函式定義/////

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE; // 設置光標為不可見
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    return;
}

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
    if (maze[chapter][newY][newX] != "　" && maze[chapter][newY][newX] != "門") {
        return;
    }

    // 檢查是否到達終點
    if (maze[chapter][newY][newX] == "門") {
        // NextLevel();
        return;
    }

    // 更新玩家位置
    player.x = newX;
    player.y = newY;
    DrawMaze(chapter, 0);

    return;
}

void read(vector <text> content)
{
    for (int i = 0; i < content.size(); i++)
    {
        say(content[i].speaker, content[i].sentence); // 說出內容
        Sleep(1000);
        cout << "\r" << string(content[i].speaker.length() + content[i].sentence.length(), ' ') << "\r"; // 清除該行內容
    }

    return;
}

void say(string speaker, string sentence) // 顯示對話
{
    cout << speaker;

    for (int i = 0; i < sentence.length(); i++)
    {
        cout << sentence[i];

        Sleep(50); // 讓每個字顯示有延遲
    }

    return;
}

void DrawMaze(int chapter, int show)
{
    // 設定光標位置
    coord = {0, 3};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int i = 0; i < maze[chapter].size(); i++)
    {
        for (int j = 0; j < maze[chapter][i].size(); j++)
        {
            if (i == player.y && j == player.x)
            {
                cout << "我";
            } else {
                cout << maze[chapter][i][j];
            }

            switch (show)
            {
                case 0:
                    break; // 甚麼都不做
                case 1:
                    Sleep(10); // 讓每個字顯示有延遲
                    break;
            }
            
        }

        cout << endl;
    }

    return;
}
