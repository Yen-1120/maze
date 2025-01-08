#include <windows.h>
#include <iostream>

using namespace std;

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main()
{
    cout << '1' << '2' << '3' << endl;

    setConsoleColor(4); // 紅色
    cout << "紅色文字" << endl;

    setConsoleColor(2); // 綠色
    cout << "綠色文字" << endl;

    setConsoleColor(1); // 藍色
    cout << "藍色文字" << endl;

    setConsoleColor(7); // 重置為白色
    return 0;
}