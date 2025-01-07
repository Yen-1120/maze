#include <windows.h>
#include <iostream>

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    setConsoleColor(4); // 紅色
    std::cout << "紅色文字" << std::endl;

    setConsoleColor(2); // 綠色
    std::cout << "綠色文字" << std::endl;

    setConsoleColor(1); // 藍色
    std::cout << "藍色文字" << std::endl;

    setConsoleColor(7); // 重置為白色
    return 0;
}
