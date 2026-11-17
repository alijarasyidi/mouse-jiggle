#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <ApplicationServices/ApplicationServices.h>
#endif
#include <thread>
#include <chrono>
#include <cstdlib>
#include <iostream>

#if defined(_WIN32)

bool hasInputPermission() {
    return true;
}

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

#elif defined(__APPLE__)

bool hasInputPermission() {
    return AXIsProcessTrusted();
}

CGPoint currentCursorPosition() {
    CGEventRef probe = CGEventCreate(NULL);
    CGPoint pos = CGEventGetLocation(probe);
    CFRelease(probe);
    return pos;
}

void simulateMouseActivity(int move) {
    CGPoint pos = currentCursorPosition();
    pos.x += move;
    pos.y += move;

    CGEventRef ev = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, pos, kCGMouseButtonLeft);
    CGEventPost(kCGHIDEventTap, ev);
    CFRelease(ev);
}

void simulateMouseClick() {
    CGPoint pos = currentCursorPosition();

    CGEventRef down = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, pos, kCGMouseButtonLeft);
    CGEventRef up = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, pos, kCGMouseButtonLeft);
    CGEventPost(kCGHIDEventTap, down);
    CGEventPost(kCGHIDEventTap, up);
    CFRelease(down);
    CFRelease(up);
}

#endif

int main() {
    if (!hasInputPermission()) {
        std::cout << "accessibility permission required. enable your terminal in System Settings > Privacy & Security > Accessibility, then run again.\n";
        return 1;
    }

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
