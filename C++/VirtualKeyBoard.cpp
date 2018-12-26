#include "stdafx.h"
#include "VirtualKeyBoard.h"

typedef void(*key)(int, int);

key DD_key;

void DD_init(){
	HINSTANCE hdll = LoadLibrary(L"gameSource\\dll\\dd74000x64.64.dll");
	if(hdll == NULL){
		cout << "dll¼ÓÔØÊ§°Ü" << endl;
		FreeLibrary(hdll);
		return;
	}
	DD_key = (key)GetProcAddress(hdll, "DD_key");
	if(DD_key == NULL){
		cout << "º¯Êý¼ÓÔØÊ§°Ü" << endl;
		FreeLibrary(hdll);
		return;
	}
}

void mousePress(){
	mouse_event(0x02, 0, 0, 0, GetMessageExtraInfo());
	interval();
	mouse_event(0x04, 0, 0, 0, GetMessageExtraInfo());
	interval();
}

void mouseMoveAndPress(int x, int y){
	mouseMove(x, y);
	mousePress();
}

void mouseMove(int x, int y){
	SetCursorPos(x, y);
	interval();
}

void KeyDown(int key) {
	DD_key(key, 1);
	interval();
}

void KeyUp(int key) {
	DD_key(key, 2);
	interval();
}

void KeyPress(int key) {
	KeyDown(key);
	KeyUp(key);
}
	
void KeyPress(int key, long time) {
	KeyDown(key);
	interval(time - 50);
	KeyUp(key);
}

void interval(long time){
	if(time <= 0) return;
	Sleep(time);
}

short getAsyncKeyState(int vKey){
	return GetAsyncKeyState(vKey);
}

bool isPress(int key){
	int val = getAsyncKeyState(key);
	if((val & 0x8000) == 32768){
		return true;
	}
	return false;
}

bool isRestart(){
	if(isPress('0')){
		return true;
	}
	return false;
}

bool isPause(){
	if(isPress(VK_HOME)){
		return true;
	}
	return false;
}

bool isQuit(){
	if(isPress(VK_END)){
		return true;
	}
	return false;
}