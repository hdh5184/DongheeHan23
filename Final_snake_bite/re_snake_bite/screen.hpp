#pragma once

/* 버퍼 초기화 함수*/
int clearBuffer(char* screenBuf, int width, int height);

/* 타이틀 화면 출력*/
int setTitleToScreen(int recordScore);

/* 게임 설명 화면 출력*/
int setDescriptionToScreen();

/* 게임 시작 전 난이도 선택 화면 출력*/
int selectGameDifficulty();

/* 게임 시작 전 사과 출력 개수 선택 출력*/
int selectGameSummonApple();

/* 게임오버 화면 출력*/
int setGameOverToScreen(int recordScore, int finalScore);





