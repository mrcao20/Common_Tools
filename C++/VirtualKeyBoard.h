#ifndef VIRTUAL_KEY_BOARD
#define VIRTUAL_KEY_BOARD

#include<Windows.h>
#include <iostream>

using namespace std;

extern void DD_init();
extern void mouseMove(int, int);
extern void mousePress();
extern void KeyDown(int);
extern void KeyUp(int);
extern void KeyPress(int);
extern void KeyPress(int, long);
extern void interval(long = 50);
extern short getAsyncKeyState(int);
extern bool isQuit();
extern bool isPause();
extern bool isRestart();
extern void mouseMoveAndPress(int, int);

#endif // VIRTUAL_KEY_BOARD