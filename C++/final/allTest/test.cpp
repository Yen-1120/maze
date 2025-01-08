#include <windows.h> // 用於 Beep 函數
#include <iostream>
#include <thread>    // 用於 this_thread::sleep_for
#include <chrono>    // 用於 chrono::milliseconds

void typewriterEffect(const std::string& text) {
    for (char c : text) {
        std::cout << c << std::flush;
        if (c == ' ') {
            Beep(400, 50); // 空格聲
        } else if (c == '\n') {
            Beep(1200, 100); // 換行聲
        } else {
            Beep(800, 50); // 普通字元
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::string text = "Hello, this is a typewriter effect!\n";
    typewriterEffect(text);

    return 0;
}
