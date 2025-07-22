#include <windows.h>
#include <thread>
#include <chrono>
#include <iostream>

void simulateMouseActivity(int move) {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dx = move;
    input.mi.dy = move;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
}

void simulateMouseClick() {
    INPUT inputs[2] = {};

    // Mouse left button down
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // Mouse left button up
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(2, inputs, sizeof(INPUT));
}

int main() {
    int move = 1;
    int interval = 1;

    std::cout << "pixel move: ";
    std::cin >> move;
    std::cout << "interval (s): ";
    std::cin >> interval;
    std::cout << "press [ctrl+c] to stop.\n";

    while (true) {
        if (move > 0)
        {
            move *= -1;
        }
        else
        {
            move = std::abs(move);
        }

        simulateMouseActivity(move);
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
    return 0;
}
