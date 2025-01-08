#include <windows.h>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

COORD coord;            // 光標位置

// 迷宮地形
vector<vector<string>> Maze[2] = {
    // 第一關
    {
        {"我", "牆", "牆", "牆", "　"},
        {"牆", "牆", "　", "牆", "牆"},
        {"牆", "牆", "牆", "牆", "牆"},
        {"　", "牆", "牆", "　", "牆"},
        {"牆", "牆", "牆", "牆", "門"}
    },
    // 第二關
    {
        {"我", "牆", "牆", "牆", "牆"},
        {"　", "　", "牆", "　", "　"},
        {"牆", "牆", "牆", "　", "　"},
        {"牆", "牆", "牆", "牆", "牆"},
        {"牆", "牆", "　", "牆", "門"}
    }
};
// 我懶得記每個文字的顏色
map<string, int> color_code = {
    {"black",       0}, // 像gray
    {"blue",        1},
    {"green",       2},
    {"cyan",        3},
    {"red",         4},
    {"purple",      5},
    {"yellow",      6},
    {"white",       7},
    {"gray",        8},
};
// 預設每個文字的顏色
map<string, string> word_color = {
    {"我", "blue"},
    {"牆", "gray"},
    {"廢", "gray"},
    {"墟", "gray"},
    {"門", "purple"}
};

// 迷宮展示
void DrawMaze(int chapter, int mode);
void DrawWord(string word);
// 設置
void HideCursor();
void setConsoleColor(string code);



/////主程式/////

int main()
{
    // 預設操作
    system("cls");
    HideCursor();
    setConsoleColor("white");

    DrawMaze(0, 0);

    return 0;
}

void DrawMaze(int chapter, int mode)
{
    // 章節迷宮
    vector<vector<string>> maze = Maze[chapter];
    // 預設值
    int delay = 0;
    bool disappear = false;
    pair<string, vector<string>> focus("　", {"我", "門"});   // 第一個是填充物，是"　"，第二個是留下的[目標]

    // 調整個模式差異
    switch (mode)
    {
        case 0:         // 展示迷宮(有延遲)
            delay = 50;
            break;
        case 1:         // 更新迷宮(瞬間，無延遲)
            break;
        case 2:         // 清除迷宮(一格一格消失，獨留[目標])
            disappear = true;
            break;
    }

    coord = {0, 3};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);   // 設定光標位置

    // 尋遍目標迷宮
    for (vector<string> row : maze)
    {
        for (string word : row)
        {
            if (disappear) {
                for (string s : focus.second)
                {
                    if (s == word)
                    {
                        DrawWord(word);
                    } else {
                        cout << focus.first;
                    }
                }
            } else {
                DrawWord(word);
            }

            Sleep(delay);
        }
    
        cout << endl;
    }

    return;
}
void DrawWord(string word)
{
    setConsoleColor(word);
    cout << word;
}

// 設置
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE; // 設置光標為不可見
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    return;
}
void setConsoleColor(string word) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code[word_color[word]]);

    return;
}