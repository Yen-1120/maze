#include <iostream>
#include <windows.h>
using namespace std;

//取得主控台句柄
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void ClearScreen();       // 清屏函式
void GetConsoleSize();    // 獲取主控台大小函式
void HideCursor();        // 隱藏光標函式
void LockConsoleSize();   // 鎖定主控台大小

int main()
{
    LockConsoleSize();    // 初始化並鎖定主控台大小
    HideCursor();         // 隱藏光標，避免閃爍
    system("cls");

    while (true)
    {
        ClearScreen();      // 清屏
        GetConsoleSize();   // 獲取並顯示主控台大小
        Sleep(500);         // 延遲 500 毫秒
    }

    return 0;
}

void ClearScreen() {
    COORD coord = {0, 0}; // 將光標移動到 (0, 0)
    SetConsoleCursorPosition(hConsole, coord);
}

void GetConsoleSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi; // 儲存主控台緩衝區資訊

    // 重試機制以確保獲取穩定數據
    int retryCount = 3; // 最多重試 3 次
    while (retryCount--) {
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            // 計算寬度與高度
            int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

            // 顯示結果
            cout << "Console Width: " << width << endl;
            cout << "Console Height: " << height << endl;
            return;
        }
        Sleep(100); // 若失敗，延遲 100 毫秒後重試
    }

    cerr << "Error: Unable to get console size after retries." << endl;
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // 設置光標為不可見
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void LockConsoleSize()
{
    // 設定固定大小，例如 80x25
    int width = 180;
    int height = 25;

    COORD bufferSize = {static_cast<SHORT>(width), static_cast<SHORT>(height)};
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = {0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1)};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}
