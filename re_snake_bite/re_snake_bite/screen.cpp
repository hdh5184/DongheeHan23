#include "screen.hpp"
#include <stdio.h>
#include <cstring>

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
				if (i == 0 || i == 1 || i == (width - 1) || i == (width - 2) || j == 0 || j == (height - 1))
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

int writeStringToBuffer(const char* string, int x, int y)
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

int setTitleToScreenBuffer(char* screenBuf, int width, int height)
{
	width = 34; height = 12;
	clearBuffer(screenBuf, width, height); return 0;
}

int setGameOverToScreenBuffer(char* screenBuf, int width, int height)
{
	width = 34; height = 12;
	clearBuffer(screenBuf, width, height); return 0;
}

int setDescriptionToScreenBuffer(char* screenBuf, int width, int height) {
	width = 80; height = 11;
	clearBuffer(screenBuf, width, height); return 0;
}

int setRankingToScreenBuffer(char* screenBuf, int width, int height) {
	width = 34; height = 13;
	clearBuffer(screenBuf, width, height); return 0;
}