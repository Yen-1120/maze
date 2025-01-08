#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

// 設置控制台顏色
void setConsoleColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorCode = textColor + (bgColor << 4);  // 顏色代碼範圍 0-15
    SetConsoleTextAttribute(hConsole, colorCode);
}

// 設置其他控制台屬性（例如粗體、下劃線等）
void setConsoleAttributes(const string& attribute) {
    if (attribute == "bold") {
        cout << "\033[1m";  // 設置粗體
    } else if (attribute == "underline") {
        cout << "\033[4m";  // 設置下劃線
    } else if (attribute == "reset") {
        cout << "\033[0m";  // 重置樣式
    }
}

int main() {
    system("cls");

    // 啟用 ANSI 控制碼支持
    DWORD dwMode = 0;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hStdOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hStdOut, dwMode);

    // 使用 setConsoleColor 設置顏色
    setConsoleColor(4, 7);  // 紅色文字，黑色背景
    cout << "11111" << endl;

    // 設置粗體並改變顏色
    //setConsoleAttributes("bold");
    setConsoleColor(2, 0);  // 綠色文字，黑色背景
    cout << "22222" << endl;

    // 設置下劃線並改變顏色
    //setConsoleAttributes("underline");
    setConsoleColor(1, 0);  // 藍色文字，黑色背景
    cout << "33333" << endl;

    // 重置屬性並使用默認顏色
    //setConsoleAttributes("reset");
    setConsoleColor(7, 0);  // 默認顏色（白色文字，黑色背景）
    cout << "\033[1m44444" << endl;

    return 0;
}
