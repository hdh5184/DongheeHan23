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

//"���Ѵ��б� VR���ӡ����а� 202027041 �ѵ���";

void gotoxy(int x, int y) {
	COORD pos = { x, y }; // ��ǥ ����

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}// pos���� ����� ��ǥ�� Ŀ�� �̵�

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
	int i = 0;	/* ���� index */
	int j = 0;  /* ���� index */
	while (j < height)
	{
		while (i < width + 1) /* ���๮�ڶ����� + 1*/
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
		gotoxy(12, 3); cout << "���� �� ��� ���� �� ����";
		gotoxy(20, 4); cout << "Snake Bite";

		SetTextColor(Gray, Black);
		gotoxy(5, 8); cout << "[��, �� ����Ű�� ���� �޴��� �����ϼ���.]";
		gotoxy(4, 9); cout << "===========================================";
		gotoxy(7, 10); cout << " ���� ����    ���� ����    ���� ���� ";

		SetTextColor(Gray, dRed);
		switch (Select) {
		case 1:
			gotoxy(7, 10); cout << "<���� ����>";
			gotoxy(6, 12); cout << "\"���̵��� �����ϰ� ������ �����մϴ�.\"   ";
			break;
		case 2:
			gotoxy(20, 10); cout << "<���� ����>";
			gotoxy(6, 12); cout << "    \"���ӿ� ���� ������ Ȯ���մϴ�.\"      ";
			break;
		case 0:
			gotoxy(33, 10); cout << "<���� ����>";
			gotoxy(6, 12); cout << " \"������ �����Ͽ� ���α׷��� �ݽ��ϴ�.\"";
			break;
		}

		SetTextColor(Gray, Black);
		gotoxy(4, 13); cout << "===========================================";
		gotoxy(6, 14); cout << "[Enter�� ���� ������ �޴��� �����մϴ�.]";

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
	gotoxy(12, 3); cout << "���� �� ��� ���� �� ����";
	gotoxy(20, 4); cout << "Snake Bite";

	SetTextColor(Gray, Black);
	gotoxy(20, 6); cout << "<���Ӽ���>";
	gotoxy(2, 8); cout << "1. ��,�� ����Ű�� ���� �̵���Ų��.";
	gotoxy(2, 9); cout << "2. ����� ������ ���� ���̰� �� ĭ �þ��.";
	gotoxy(2, 10); cout << "3. ���� ��� ������ ���� ���� �ӵ��� �����Ѵ�.";
	gotoxy(2, 11); cout << "4. �� �Ӹ��� ���̳� ���� �ε����� ������ ������.";

	SetTextColor(Gray, dPurple);
	gotoxy(2, 12); cout << "*  ���� ���� �� ���̵��� ������ �� �ִ�.";

	SetTextColor(Gray, Black);
	gotoxy(8, 14); cout << "[Enter�� ���� Ÿ��Ʋ�� ���ư��ϴ�.]";

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
		gotoxy(12, 3); cout << "���� �� ��� ���� �� ����";
		gotoxy(20, 4); cout << "Snake Bite";

		SetTextColor(Gray, dPurple);
		gotoxy(16, 6); cout << "<���� ���̵� ����>";

		SetTextColor(Gray, Black);
		gotoxy(4, 8); cout << "[��, �� ����Ű�� ���� ���̵��� �����ϼ���.]";
		gotoxy(4, 9); cout << "===========================================";
		gotoxy(14, 10); cout << " ����    �߰�    ����� ";

		SetTextColor(Gray, dRed);
		switch (Select) {
		case 0:
			gotoxy(14, 10); cout << "<����>";
			gotoxy(6, 12); cout << "\"���̵��� �����ϰ� ������ �����մϴ�.\"   ";
			break;
		case 1:
			gotoxy(22, 10); cout << "<�߰�>";
			gotoxy(6, 12); cout << "    \"���ӿ� ���� ������ Ȯ���մϴ�.\"      ";
			break;
		case 2:
			gotoxy(30, 10); cout << "<�����>";
			gotoxy(6, 12); cout << " \"������ �����Ͽ� ���α׷��� �ݽ��ϴ�.\"";
			break;
		}

		SetTextColor(Gray, Black);
		gotoxy(4, 13); cout << "===========================================";
		gotoxy(9, 14); cout << "[Enter�� ���� ������ �����մϴ�.]";

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
	gotoxy(11, 8); cout << "0   �� �� �� �� �� �� ��   0";
	gotoxy(11, 9); cout << "0                          0";
	gotoxy(11, 10);
	cout << "0 ���� ������ " << setw(4) << right << finalScore << "�� �̴�. 0";
	gotoxy(11, 11); cout << "0                          0";
	gotoxy(11, 12); cout << "0                          0";
	gotoxy(11, 13); cout << "0000000000000000000000000000";

	while (1) {
		if (_kbhit()) {
			if (_getch() == Key_Enter) return 10;
		}
	}
}