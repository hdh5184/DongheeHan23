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

/* 커서 이동 함수*/
void gotoxy(int x, int y);

/* 콘솔 내 커서 숨기는 함수*/
void SetCursorState(bool visible);

/* 텍스트 색을 변경하는 함수*/
void SetTextColor(int backColor, int textColor);

/* 버퍼 초기화 함수*/
int clearBuffer(char* screenBuf, int width, int height);

/* 수업시간에 배운 x,y에 스트링을 쓰는 함수를 짜면 됨. */
int writeStringToScreen(const char* string, int x, int y);

/* 타이틀 화면 출력*/
int setTitleToScreen();

/* 게임 설명 화면 출력*/
int setDescriptionToScreen();

/* 게임 시작 전 난이도 선택 화면 출력*/
int selectGameDifficulty();

/* 게임오버 화면 출력*/
int setGameOverToScreen(int finalScore);





