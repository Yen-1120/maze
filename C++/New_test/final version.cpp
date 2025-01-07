#include <iostream>     // cin, cout
#include <conio.h>      // 使用者輸入
#include <windows.h>    // 操作視窗: Sleep(), GetCurrentProcessId(),
#include <string>       // string(不是容器)特殊化類別
#include <vector>       // vector容器

using namespace std;

bool rungame = true;    // 遊戲執行條件

COORD coord;            // 光標位置

// 迷宮
vector<vector<string>> maze[3] = {

};

// 劇情
    // 替一章
void opening() {
    cout << "大家好這裡是開場白" << endl;
}
void Chapter1() {
    cout << "第一章：主角的起點。" << endl;
}
void Chapter2() {
    cout << "第二章：神秘來客。" << endl;
}
void Chapter3() {
    cout << "第三章：危險降臨。" << endl;
}
    // 章節表，使用指標指向所需展示的章節，可以更方便的使用劇情函式。
int chapter;
void (*chapters[])() = {opening, Chapter1, Chapter2, Chapter3};

// 關卡切換：包含劇情展示、迷宮切換等等
void ToLevel(int chapter);  // 醫官對應依劇情

/////程式開始/////

int main()
{
    system("cls");
    HideCursor();
    setConsoleColor(7);

    for (int i = 0; i < 3; i++)
    {
        ToLevel(i);
    }
    /*
    while (rungame)
    {
        CheckInput();   // 遊戲核心

        Sleep(100);     // 控制迴圈速度
    }
    */

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
void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);

    return;
    /*
    黑色	0
    藍色	1
    綠色	2
    青色	3
    紅色	4
    紫色	5
    黃色	6
    白色	7
    */
}


