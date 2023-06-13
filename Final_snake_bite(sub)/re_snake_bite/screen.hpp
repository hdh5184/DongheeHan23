#pragma once

#include <windows.h>
#include <conio.h>
#include <iostream>



/* 버퍼 초기화 함수*/
int clearBuffer(char* screenBuf, int width, int height);

/* 수업시간에 배운 x,y에 스트링을 쓰는 함수를 짜면 됨. */
int writeStringToScreen(const char* string, int x, int y);

/* 타이틀 화면 출력*/
int setTitleToScreen(int finalScore);

/* 게임 설명 화면 출력*/
int setDescriptionToScreen();

/* 게임 시작 전 난이도 선택 화면 출력*/
int selectGameDifficulty();

/* 게임오버 화면 출력*/
int setGameOverToScreen(int recordScore, int finalScore);





