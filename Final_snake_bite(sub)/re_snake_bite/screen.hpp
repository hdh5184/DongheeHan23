#pragma once

#include <windows.h>
#include <conio.h>
#include <iostream>



/* ���� �ʱ�ȭ �Լ�*/
int clearBuffer(char* screenBuf, int width, int height);

/* �����ð��� ��� x,y�� ��Ʈ���� ���� �Լ��� ¥�� ��. */
int writeStringToScreen(const char* string, int x, int y);

/* Ÿ��Ʋ ȭ�� ���*/
int setTitleToScreen(int finalScore);

/* ���� ���� ȭ�� ���*/
int setDescriptionToScreen();

/* ���� ���� �� ���̵� ���� ȭ�� ���*/
int selectGameDifficulty();

/* ���ӿ��� ȭ�� ���*/
int setGameOverToScreen(int recordScore, int finalScore);





