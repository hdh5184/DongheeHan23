#pragma once
#include <windows.h>
#include <conio.h>

/* 커서 이동 함수*/
void gotoxy(int x, int y);

/* 콘솔 내 커서 숨기는 함수*/
void SetCursorState(bool visible);

/* 버퍼 초기화 함수*/
int clearBuffer(char* screenBuf, int width, int height);

/* 수업시간에 배운 x,y에 스트링을 쓰는 함수를 짜면 됨. */
int writeStringToBuffer(const char* string, int x, int y);

/* 타이틀 화면 그리는 버퍼*/
int setTitleToScreenBuffer(char* screenBuf, int width, int height);

/* 게임오버 화면 그리는 버퍼*/
int setGameOverToScreenBuffer(char* screenBuf, int width, int height);

/* 설명 화면 그리는 버퍼*/
int setDescriptionToScreenBuffer(char* screenBuf, int width, int height);

/* 랭킹 화면 그리는 버퍼*/
int setRankingToScreenBuffer(char* screenBuf, int width, int height);


