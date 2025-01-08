#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    // 播放指定的音效文件，並等待播放完成
    if (PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_SYNC)) {
        cout << "音效播放完成！" << endl;
    } else {
        cout << "播放音效失敗！" << endl;
    }
    return 0;
}