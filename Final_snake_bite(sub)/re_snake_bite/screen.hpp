#pragma once

#include <windows.h>
#include <conio.h>
#include <iostream>

enum TextColorCollection {
	//0b00xx	00			01			10			11
				Black,		dBlue,		dGreen,		dSkyBlue,
	//0b01xx
				dRed,		dPurple,	dYellow,	Gray,
	//0b10xx
				dGray,		Blue,		Green,		SkyBlue,
	//0b11xx
				Red,		Purple,		Yellow,		White
};

/* Ŀ�� �̵� �Լ�*/
void gotoxy(int x, int y);

/* �ܼ� �� Ŀ�� ����� �Լ�*/
void SetCursorState(bool visible);

/* �ؽ�Ʈ ���� �����ϴ� �Լ�*/
void SetTextColor(int backColor, int textColor);

/* ���� �ʱ�ȭ �Լ�*/
int clearBuffer(char* screenBuf, int width, int height);

/* �����ð��� ��� x,y�� ��Ʈ���� ���� �Լ��� ¥�� ��. */
int writeStringToScreen(const char* string, int x, int y);

/* Ÿ��Ʋ ȭ�� ���*/
int setTitleToScreen();

/* ���� ���� ȭ�� ���*/
int setDescriptionToScreen();

/* ���� ���� �� ���̵� ���� ȭ�� ���*/
int selectGameDifficulty();

/* ���ӿ��� ȭ�� ���*/
int setGameOverToScreen(int finalScore);





