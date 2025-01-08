#include <iostream>     // cin, cout
#include <conio.h>      // 使用者輸入: _kbhit(), _getch()
#include <windows.h>    // 操作視窗: Sleep(), GetCurrentProcessId()......
#include <string>
#include <vector>
#include <map>

using namespace std;

// 遊戲執行條件
bool rungame = true;
// 我懶得記每個文字的顏色
map<string, int> color_code = {
    {"black",       0},
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
    {"我", "red"},
    {"牆", "white"},
    {"廢", "gray"},
    {"墟", "gray"},
    {"瓦", "gray"},
    {"磚", "gray"},
    {"門", "red"}
};
// 物品(之後方便擴充)
struct item
{
    short x;
    short y;
}player;

// 設置
void HideCursor();
void SetWordColor(string code);
void CursorPosition(short x, short y);
// 劇情展示
void Tolevel();                                         // 切換章節
void type(string sentence, string color, int delay);    // 打字機
void CleanLine();                                       // 清除該行(前40"　")
// 顯示迷宮
void DrawMaze(int mode);
void DrawWord(string word);
// 處理玩家輸入
void CheckInput();
void walk(short dx, short dy);

/////迷宮地形/////
struct Maze
{
    pair<short, short> PlayerStart;
    vector<vector<string>> terrain;
};
Maze maze[3] = {
    // 開場(沒東西)
    {{0, 0}, {}},
    // 第一關
    {
        {1, 1},
        {
            {"牆", "牆", "牆", "牆", "牆", "牆", "牆"},
            {"牆", "　", "　", "牆", "　", "門", "牆"},
            {"牆", "牆", "　", "牆", "　", "牆", "牆"},
            {"牆", "牆", "　", "　", "　", "牆", "牆"},
            {"牆", "牆", "牆", "牆", "牆", "牆", "牆"}
        }
    },
    // 第二關
    {
        {1, 1},
        {
            {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
            {"牆", "　", "　", "　", "　", "　", "　", "　", "牆"},
            {"牆", "　", "牆", "　", "牆", "牆", "　", "牆", "牆"},
            {"牆", "　", "牆", "牆", "　", "牆", "　", "牆", "牆"},
            {"牆", "　", "　", "　", "　", "牆", "　", "牆", "牆"},
            {"牆", "　", "牆", "牆", "牆", "牆", "　", "門", "牆"},
            {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"}
        }
    }
};
/////劇情內容/////
void opening() {
    CursorPosition(0, 0);
    type("旁白：", "white", 0); Sleep(500);
    type("歡迎來到這個遊戲。", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("雖然這個遊戲", "white", 50); type(" 還 沒 做 好 ", "yellow", 75); type("。", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("即便如此，", "white", 50); Sleep(500);
    type("希望螢幕前的你依然能夠體驗遊戲的樂趣......", "white", 50);
    Sleep(2500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("話不多說，", "white", 50); Sleep(500);
    type("讓我們", "yellow", 50);
    type("開始遊戲吧！", "yellow", 100);
    Sleep(1500);CleanLine();

    return;
}
void Chapter1() {
    CursorPosition(0, 0);
    type("旁白：", "white", 0); Sleep(500);
    type("例行公事，", "white", 50); Sleep(500);
    type("我必須告訴你", "white", 50); type("遊戲規則", "yellow", 50); type("。", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("我本來想做更多內容的，", "white", 50); Sleep(500);
    type("例如", "white", 50); type("翻牆、傳送門、NPC互動、戰鬥、道具、叉路......", "gray", 5);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("但是由於時間關係，", "white", 50); Sleep(500);
    type("我只能做到這麼多......", "white", 50);
    Sleep(2500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("扯遠了，", "white", 50); Sleep(500);
    type("讓我們回到遊戲吧。", "white", 50);
    Sleep(1500);CleanLine();
    type("提示：", "white", 10); Sleep(500);
    type("使用方向件來控制\"", "white", 10); type("我", "red", 10); type("\"移動。\n", "white", 10); Sleep(500);
    type("　　　抵達\"", "white", 10); type("門", "red", 10); type("\"的位置。", "white", 10);

    return;
}
void Chapter2() {
    CursorPosition(0, 0);
    type("旁白：", "white", 0); Sleep(500);
    type("恭喜來到第二關，", "white", 50); Sleep(500);
    type("同時也是遊戲的最後一關。", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("我又忍不住想扯遠了......", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("你想知道為什麼我", "white", 50); type("想做遊戲", "yellow", 100); type("嗎？", "white", 50);
    Sleep(2500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("你沒得選，", "white", 50); Sleep(500);
    type("因為我沒做這個功能。", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("\"透過遊戲，", "yellow", 50); Sleep(500);
    type("看見另一個世界。\"", "yellow", 50);
    Sleep(2500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("遊戲不只是", "white", 50);
    type("打怪、", "white", 50); Sleep(100);
    type("抽獎、", "white", 50); Sleep(100);
    type("刷經驗。", "white", 50); Sleep(100);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("更不是欺負", "white", 10); type("哥布林", "green", 10); type("。", "white", 10);
    Sleep(500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("遊戲也可以是一個", "white", 50); type("故事", "yellow", 50); type("的載體。", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("每一個", "white", 50); type("故事", "yellow", 50); type("，", "white", 50); Sleep(500);
    type("都蘊含了創作者精心準備的內容......", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("願意創作的熱情", "red", 50); type("、", "white", 50); Sleep(250);
    type("奇思妙想的創意", "green", 50); type("、", "white", 50); Sleep(250);
    type("敢於嘗試的勇氣", "yellow", 50); type("，", "white", 50); Sleep(250);
    type("以及", "white", 50); type("堅持下去的毅力", "blue", 50); type("......", "white", 50);
    Sleep(2500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("當然也包含喜歡遊戲的玩家，", "white", 50); Sleep(500);
    type("還有至同道合的夥伴。", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("這一切都是讓創作者得以繼續創作，", "white", 50); Sleep(500);
    type("讓更多精彩的故事誕生，", "white", 50); Sleep(500);
    type("展現在所有玩家的眼前。", "white", 50); Sleep(500);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("......", "white", 100);
    Sleep(2500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("我說完了。", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("我真的需要改一改，", "white", 50); Sleep(500);
    type("讓玩家能在我說話的時候順利操控角色。", "white", 50); Sleep(500);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("不至於被硬控那麼久。", "white", 50);
    Sleep(2500);CleanLine();
    type("提示：", "white", 10); Sleep(500);
    type("通過最後的迷宮，", "white", 10); Sleep(500);
    type("完成這個遊戲", "white", 10);

    return;
}
void TheEnd() {
    CursorPosition(0, 0);
    type("旁白：", "white", 0); Sleep(500);
    type("遊戲到這裡就結束了。", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("在這個遊戲中，", "white", 50); Sleep(500);
    type("我只做到", "white", 50); type("移動角色", "red", 50); type("、", "white", 50); Sleep(500);
    type("碰撞判斷", "red", 50); type("、", "white", 50); Sleep(500);
    type("關卡切換", "red", 50); type("，", "white", 50); Sleep(500);
    type("還有現在這個", "white", 50); type("對話打字機", "red", 100); type("。", "white", 50);
    Sleep(2500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("如果有更多時間，", "white", 50); Sleep(500);
    type("我相信我能做得更好", "white", 50);
    Sleep(1500);CleanLine();
    type("旁白：", "white", 0); Sleep(500);
    type("把我", "white", 50); type("理想中的遊戲", "yellow", 50); type("做出來。", "white", 50);
    Sleep(1500);CleanLine();
    Sleep(2500);
    type("旁白：", "white", 0); Sleep(500);
    type("最後，", "white", 50);  Sleep(500);
    type("感謝每一個玩過這個遊戲的玩家。", "white", 50);
    Sleep(500);CleanLine();
    type("(雖然目前還沒做完)", "white", 50);  Sleep(500);
    Sleep(500);CleanLine();
    type("感謝遊玩", "yellow", 50);

    return;
}
int chapter;
void (*ShowChapters[])() = {opening, Chapter1, Chapter2, TheEnd}; // 章節表，使用指標指向所需展示的章節，可以更方便的使用劇情函式。



/////程式開始/////

int main()
{
    system("cls");
    HideCursor();

    chapter = 0;
    Tolevel();

    chapter = 1;
    Tolevel();

    while (rungame)
    {
        CheckInput();
        Sleep(100);
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
void SetWordColor(string color) {
    if (color == "") // 無輸入，直接回傳
    {
        return;
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code[color]);

    return;
}
void CursorPosition(short x, short y) {
    COORD coord;
    coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    return;
}

// 劇情展示
void Tolevel()
{
    if (chapter == 3)
    {
        ShowChapters[3]();
        rungame = false;
    } else {
        DrawMaze(0);                // 先畫迷宮
        ShowChapters[chapter]();    // 在展示劇情
    }

    return;
}
void type(string sentence, string color, int delay)
{
    SetWordColor(color);
    for (int i = 0; i < sentence.length(); i++) // 逐字顯示(就說是打字機)
    {
        Sleep(delay);
        cout << sentence[i];
    }

    return;
}
void CleanLine()
{
    // 輸出40個"　"
    cout << "\r" << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　" << "\r";
}

// 顯示迷宮
void DrawMaze(int mode)
{
    CursorPosition(0, 3);

    // 預設值
    int delay = 0;
    bool disappear = false;

    // 調整個模式差異
    switch (mode)
    {
        case 0:         // 展示迷宮(有延遲)
            player.x = maze[chapter].PlayerStart.first;
            player.y = maze[chapter].PlayerStart.second;
            delay = 75;
            break;
        case 1:         // 更新迷宮(瞬間，無延遲)
            break;
        case 2:         // 清除迷宮(一格一格消失，獨留[目標])
            delay = 75;
            disappear = true;
            break;
    }

    // 尋遍目標迷宮
    pair<short, short> mazeXY = {0, 0}; // X, Y
    for (vector<string> row : maze[chapter].terrain)
    {
        mazeXY.first = 0;
        for (string word : row)
        {
            Sleep(delay);
            if (mazeXY.first == player.x && mazeXY.second == player.y)   // 畫出玩家位置
            {
                DrawWord("我");
            } else {
                if (disappear)
                {
                    cout << "　";
                } else {
                    DrawWord(word);
                }
            }
            
            mazeXY.first += 1;
        }
        mazeXY.second += 1;
        cout << endl;
    }

    return;
}
void DrawWord(string word)
{
    SetWordColor(word_color[word]);
    cout << word;
}

// 處理玩家輸入
void CheckInput()
{
    if (_kbhit())
    {
        int key = _getch();
        switch (key) {
            case 72:    // 上
                walk(0, -1);
                break;
            case 77:    // 右
                walk(1, 0);
                break;
            case 80:    // 下
                walk(0, 1);
                break;
            case 75:    // 左
                walk(-1, 0);
                break;
        }
    }

    return;
}
void walk(short dx, short dy)
{
    short newX = player.x + dx;
    short newY = player.y + dy;

    // 檢查是否撞到牆
    if (maze[chapter].terrain[newY][newX] == "牆")
    {
        return; // 不改變玩家位置，不更新螢幕畫面
    }
    // 檢查是否到達"門"
    if (maze[chapter].terrain[newY][newX] == "門")
    {
        // 更新玩家位置
        player.x = newX;
        player.y = newY;
        DrawMaze(1);
        Sleep(1000);
        // 清空舊地圖，前往下一章
        DrawMaze(2);
        chapter += 1;
        Sleep(500);
        system("cls");
        Sleep(1000);
        Tolevel();

        return;
    }

    // 更新玩家位置
    player.x = newX;
    player.y = newY;
    DrawMaze(1);

    return;
}
