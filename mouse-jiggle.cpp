#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    std::cout << "Press Ctrl+C to stop.\n";

    while (true) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);

        // Move the cursor 1px right and back
        SetCursorPos(cursorPos.x + 1, cursorPos.y);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        SetCursorPos(cursorPos.x, cursorPos.y);

        // Wait 5 seconds before next wiggle
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
