#include <iostream>
#include <windows.h>

using namespace std;

//取得主控台句柄
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//NPC名單
struct NPC
{
    string name; //對化時顯示的名稱
    COORD where; //說話位置(從顯示名稱處算起)
    //{"玩家", 1}
};
NPC narrator = {"旁白", {0, 0}};
NPC player = {"玩家", {0, 1}};

bool rungame = true;

void Update_game();   // 遊戲邏輯更新
void Check_input();   // 玩家輸入檢查
void ClearScreen();   // 畫面更新(實際上只是把光標移到左上角)
void say(NPC, string);

int main()
{
    system("cls");

    while(rungame)
    {
        say(narrator, "你好");
        say(player, "我不好");
        Sleep(50);
    }

    return 0;
}

void ClearScreen()
{
    COORD coord = {0, 0}; // 設定光標位置
    SetConsoleCursorPosition(hConsole, coord);
}

void say(NPC speaker, string sentance)
{
    // 設定說話者(光標)位置
    COORD coord = speaker.where;
    SetConsoleCursorPosition(hConsole, coord);

    // 顯示說話者名稱
    cout << speaker.name << ": ";

    for (int i = 0; i < sentance.length(); i++)
    {
        cout << sentance[i];
        Sleep(100);
    }

    return;
}
