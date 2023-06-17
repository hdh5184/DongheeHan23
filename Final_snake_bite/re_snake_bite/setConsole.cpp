#include <windows.h>
#include "setConsole.hpp"

void gotoxy(int x, int y) {
	COORD pos = { x, y }; // 좌표 저장

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}// pos에서 저장된 좌표로 커서 이동

void SetCursorState(bool visible) {
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	consoleCursorInfo.bVisible = visible;
	consoleCursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
}

void SetTextColor(int backColor, int textColor) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
}