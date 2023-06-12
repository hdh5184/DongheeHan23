#include "screen.hpp"
#include <stdio.h>
#include <cstring>
#include <iomanip>

#define Key_Enter 13
#define Key_Left 75
#define Key_Right 77

using namespace std;

int Select = 1;
int KeyEnent = 1;
int keyInput = 1;

//"유한대학교 VR게임·앱학과 202027041 한동희";

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

int clearBuffer(char* screenBuf, int width, int height)
{
	int i = 0;	/* 가로 index */
	int j = 0;  /* 세로 index */
	while (j < height)
	{
		while (i < width + 1) /* 개행문자때문에 + 1*/
		{
			if (i == width)
				screenBuf[i + (j * (width + 1))] = '\n';
			else
			{
				if (i == 0 || i == (width - 1) || j == 0 || j == (height - 1))
					screenBuf[i + (j * (width + 1))] = '#';
				else
					screenBuf[i + (j * (width + 1))] = ' ';
			}
			i = i + 1;
		}
		i = 0;
		j = j + 1;
	}
	screenBuf[height * (width + 1) - 1] = '\0';
	return 0;
}

int writeStringToScreen(const char* string, int x, int y)
{
	gotoxy(x, y);
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == '\n') {
			gotoxy(x, y + 1);
			y++;
		}
		else printf("%c", string[i]);
	}

	gotoxy(6, y);


	return 0;
}

int setTitleToScreen()
{
	Select = 1;
	KeyEnent = 1;
	keyInput = 1;

	while (1) {
		SetTextColor(Gray, dBlue);
		gotoxy(12, 3); cout << "내가 뱀 띠라서 만든 뱀 게임";
		gotoxy(20, 4); cout << "Snake Bite";

		SetTextColor(Gray, Black);
		gotoxy(5, 8); cout << "[좌, 우 방향키를 눌러 메뉴를 선택하세요.]";
		gotoxy(4, 9); cout << "===========================================";
		gotoxy(7, 10); cout << " 게임 시작    게임 설명    게임 종료 ";

		SetTextColor(Gray, dRed);
		switch (Select) {
		case 1:
			gotoxy(7, 10); cout << "<게임 시작>";
			gotoxy(6, 12); cout << "\"난이도를 설정하고 게임을 시작합니다.\"   ";
			break;
		case 2:
			gotoxy(20, 10); cout << "<게임 설명>";
			gotoxy(6, 12); cout << "    \"게임에 대한 설명을 확인합니다.\"      ";
			break;
		case 0:
			gotoxy(33, 10); cout << "<게임 종료>";
			gotoxy(6, 12); cout << " \"게임을 종료하여 프로그램을 닫습니다.\"";
			break;
		}

		SetTextColor(Gray, Black);
		gotoxy(4, 13); cout << "===========================================";
		gotoxy(6, 14); cout << "[Enter를 눌러 선택한 메뉴를 실행합니다.]";

		while (KeyEnent) {
			if (_kbhit()) {
				keyInput = _getch();
				if (keyInput == 224) keyInput = _getch();
				if (Select == 0) Select = 3;

				switch (keyInput) {
				case Key_Left: Select--; break;
				case Key_Right: Select++; break;
				case Key_Enter: return Select % 3;
				}
				KeyEnent = 0;
			}
		}
		KeyEnent = 1;
		Select %= 3;
	}
}


int setDescriptionToScreen() {
	SetTextColor(Gray, dBlue);
	gotoxy(12, 3); cout << "내가 뱀 띠라서 만든 뱀 게임";
	gotoxy(20, 4); cout << "Snake Bite";

	SetTextColor(Gray, Black);
	gotoxy(20, 6); cout << "<게임설명>";
	gotoxy(2, 8); cout << "1. 좌,우 방향키로 뱀을 이동시킨다.";
	gotoxy(2, 9); cout << "2. 사과를 먹으면 뱀의 길이가 한 칸 늘어난다.";
	gotoxy(2, 10); cout << "3. 먹은 사과 개수에 따라 뱀의 속도가 증가한다.";
	gotoxy(2, 11); cout << "4. 뱀 머리가 벽이나 몸에 부딪히면 게임이 끝난다.";

	SetTextColor(Gray, dPurple);
	gotoxy(2, 12); cout << "*  게임 시작 전 난이도를 선택할 수 있다.";

	SetTextColor(Gray, Black);
	gotoxy(8, 14); cout << "[Enter를 눌러 타이틀로 돌아갑니다.]";

	while (1) {
		if (_kbhit()) {
			if(_getch() == Key_Enter) return 10;
		}
	}
}

int selectGameDifficulty() {
	Select = 0;
	KeyEnent = 1;
	keyInput = 1;

	while (1)
	{
		SetTextColor(Gray, dBlue);
		gotoxy(12, 3); cout << "내가 뱀 띠라서 만든 뱀 게임";
		gotoxy(20, 4); cout << "Snake Bite";

		SetTextColor(Gray, dPurple);
		gotoxy(16, 6); cout << "<게임 난이도 설정>";

		SetTextColor(Gray, Black);
		gotoxy(4, 8); cout << "[좌, 우 방향키를 눌러 난이도를 선택하세요.]";
		gotoxy(4, 9); cout << "===========================================";
		gotoxy(14, 10); cout << " 쉬움    중간    어려움 ";

		SetTextColor(Gray, dRed);
		switch (Select) {
		case 0:
			gotoxy(14, 10); cout << "<쉬움>";
			gotoxy(6, 12); cout << "\"난이도를 설정하고 게임을 시작합니다.\"   ";
			break;
		case 1:
			gotoxy(22, 10); cout << "<중간>";
			gotoxy(6, 12); cout << "    \"게임에 대한 설명을 확인합니다.\"      ";
			break;
		case 2:
			gotoxy(30, 10); cout << "<어려움>";
			gotoxy(6, 12); cout << " \"게임을 종료하여 프로그램을 닫습니다.\"";
			break;
		}

		SetTextColor(Gray, Black);
		gotoxy(4, 13); cout << "===========================================";
		gotoxy(9, 14); cout << "[Enter를 눌러 게임을 시작합니다.]";

		while (KeyEnent) {
			if (_kbhit()) {
				keyInput = _getch();
				if (keyInput == 224) keyInput = _getch();
				if (Select == 0) Select = 3;

				switch (keyInput) {
				case Key_Left: Select--; break;
				case Key_Right: Select++; break;
				case Key_Enter: 
					switch (Select % 3)
					{
					case 0: return 5;
					case 1: return 10;
					case 2: return 20;
					}
				}
				KeyEnent = 0;
			}
		}
		KeyEnent = 1;
		Select %= 3;
	}
}


int setGameOverToScreen(int finalScore)
{
	SetTextColor(dRed, White);
	gotoxy(11, 6); cout << "0000000000000000000000000000";
	gotoxy(11, 7); cout << "0                          0";
	gotoxy(11, 8); cout << "0   게 임 이 끝 났 어 요   0";
	gotoxy(11, 9); cout << "0                          0";
	gotoxy(11, 10);
	cout << "0 너의 점수는 " << setw(4) << right << finalScore << "점 이다. 0";
	gotoxy(11, 11); cout << "0                          0";
	gotoxy(11, 12); cout << "0                          0";
	gotoxy(11, 13); cout << "0000000000000000000000000000";

	while (1) {
		if (_kbhit()) {
			if (_getch() == Key_Enter) return 10;
		}
	}
}