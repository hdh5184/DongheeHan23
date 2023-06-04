#pragma once
#include <windows.h>
#include <conio.h>

/* Ŀ�� �̵� �Լ�*/
void gotoxy(int x, int y);

/* �ܼ� �� Ŀ�� ����� �Լ�*/
void SetCursorState(bool visible);

/* ���� �ʱ�ȭ �Լ�*/
int clearBuffer(char* screenBuf, int width, int height);

/* �����ð��� ��� x,y�� ��Ʈ���� ���� �Լ��� ¥�� ��. */
int writeStringToBuffer(const char* string, int x, int y);

/* Ÿ��Ʋ ȭ�� �׸��� ����*/
int setTitleToScreenBuffer(char* screenBuf, int width, int height);

/* ���ӿ��� ȭ�� �׸��� ����*/
int setGameOverToScreenBuffer(char* screenBuf, int width, int height);

/* ���� ȭ�� �׸��� ����*/
int setDescriptionToScreenBuffer(char* screenBuf, int width, int height);

/* ��ŷ ȭ�� �׸��� ����*/
int setRankingToScreenBuffer(char* screenBuf, int width, int height);


