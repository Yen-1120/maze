#include <iostream>
using namespace std;

// 定義章節函式
void Chapter1() {
    cout << "第一章：主角的起點。" << endl;
    cout << "這裡描述主角的出身與背景。" << endl;
}

void Chapter2() {
    cout << "第二章：神秘來客。" << endl;
    cout << "主角遇到一位神秘的角色，引出冒險的序幕。" << endl;
}

void Chapter3() {
    cout << "第三章：危險降臨。" << endl;
    cout << "主角必須快速適應變故，迎接挑戰。" << endl;
}

int main() {
    // 定義函式指標陣列
    void (*chapters[])() = {Chapter1, Chapter2, Chapter3};

    int choice;
    cout << "歡迎來到故事冒險！" << endl;

    while (true) {
        // 顯示章節選項
        cout << "\n請選擇章節：" << endl;
        cout << "1. 第一章" << endl;
        cout << "2. 第二章" << endl;
        cout << "3. 第三章" << endl;
        cout << "0. 結束故事" << endl;

        cout << "請輸入選擇 (0-3)：";
        cin >> choice;

        if (choice == 0) {
            cout << "感謝遊玩！故事結束。" << endl;
            break;
        }

        if (choice >= 1 && choice <= 3) {
            chapters[choice - 1]();  // 呼叫對應章節的函式
        } else {
            cout << "無效選擇，請重新輸入！" << endl;
        }
    }

    return 0;
}
