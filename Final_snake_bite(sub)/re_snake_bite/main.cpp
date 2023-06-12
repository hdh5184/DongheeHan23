#define _CRT_SECURE_NO_WARNINGS

#define GameStartState 1		//���� ����
#define DescriptionState 2		//���� ����
#define TitleState 10			//Ÿ��Ʋ
#define GameOverState 99		//���� ��ŷ
#define GameQuit 0

#include <algorithm>            //sort �迭 ���� ���
#include <iomanip>              //setw �Լ� ���
#include <stdio.h>
#include <vector>
#include "screen.hpp"
#include "Musoeun.hpp"

/*���� ���¿� ���� ȭ�� ���*/
void GameStateCheck();

char screenBuf[1000];           //ȭ�� ��¿� ����
int width = 52;                 //������ �ʺ�
int height = 18;                //������ ����
int isGamePlaying = 10;         //���� ���� ���� ����� (��� : 3~8��° ��)
int KeyEvent = 1;               //Ű �Է� �̺�Ʈ ����
int KeyInput = 0;               //�Է��� Ű �� ����
int recordScore;                //���� ���� �� ���� �������� ����
int setSpeed;
int finalScore;

MuSoeun::MGameLoop GamePlay;                        //���� ���� ����� ��ü ����

int main()
{
    SetCursorState(false);                              //�ܼ� �� Ŀ�� ����
    clearBuffer(screenBuf, width, height);              //ȭ�� ���� �ʱ�ȭ

    //���� ������ �� ���� (isGamePlaying == 0) ȭ�� ���
    while (isGamePlaying)
    {
        //��ũ�� ���� ��� �� ��ũ�� ���� ���
        SetTextColor(Gray, Black);
        cout << screenBuf;
        GameStateCheck();

        SetTextColor(Black, White);
        system("cls");  //ȭ�� �����
    }
    //���� ���� ��
    cout << "������ �����Ͽ����ϴ�." << endl;
    return 0;
}

void GameStateCheck() {
    switch (isGamePlaying)
    {
    case TitleState:        //Ÿ��Ʋ
        isGamePlaying = setTitleToScreen();
        break;
    case GameStartState:    //���� ���� ~ ���� ����
        setSpeed = selectGameDifficulty();
        SetTextColor(Black, White);
        system("cls");

        finalScore = GamePlay.Run(setSpeed);   //���� ����, ���� ���� �� ���� ��������
        setGameOverToScreen(finalScore);
        isGamePlaying = TitleState;
        break;
    case DescriptionState:  //���� ����
        setDescriptionToScreen();
        isGamePlaying = 10;
        break;
    case GameQuit:
        isGamePlaying = GameQuit;
        break;
    default:
        break;
    }
}