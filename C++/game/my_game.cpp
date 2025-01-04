#include "say.h"
//#include "maze.h" // 其實 player_move.h 裡已經 #include "maze.h" 了
//#include "player_move.h"
#include <thread>

bool rungame = true;

// from say.h
Role narrator = {"旁白", {0, 0}};
Role player = {"玩家", {0, 1}};

void ClearScreen();

void t_say();

int main()
{
    system("cls");
    // thread T_say(t_say);

    while (rungame)
    { 
        say(narrator, "你好");
        say(player, "我不好");

        Sleep(50);
    }

    // 等待線程結束
    // T_say.join();

    return 0;
}

void ClearScreen()
{
    COORD coord = {0, 0}; // 設定光標位置
    SetConsoleCursorPosition(hConsole, coord);
}

void t_say() {
    say(player, "我不好");

    return;
}
