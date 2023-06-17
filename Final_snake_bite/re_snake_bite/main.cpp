#define _CRT_SECURE_NO_WARNINGS

#define GameStartState 1		//���� ����
#define DescriptionState 2		//���� ����
#define TitleState 10			//Ÿ��Ʋ
#define GameOverState 99		//���� ��ŷ
#define GameQuit 0

#include "Musoeun.hpp"
#include "screen.hpp"
#include "setConsole.hpp"

/*���� ���� ���� �� ��ũ�� ���*/
void GameStateCheck();

char screenBuf[1000];           //ȭ�� ��¿� ����
int width = 52;                 //������ �ʺ�
int height = 18;                //������ ����
int isGamePlaying = 10;         //���� ���� ���� ����� (��� : 3~8��° ��)
int setSpeed = 0;
int summonApple = 0;
int recordScore = 0;                //���� ���� �� ���� �������� ����
int finalScore = 0;

MuSoeun::MGameLoop GamePlay;                        //���� ���� ����� ��ü ����

int main()
{
    SetCursorState(false);                              //�ܼ� �� Ŀ�� ����
    clearBuffer(screenBuf, width, height);              //ȭ�� ���� �ʱ�ȭ

    //���� ������ �� ���� (isGamePlaying == 0) ȭ�� ���
    while (isGamePlaying)
    {
        //��ũ�� ���� ��� �� ��ũ�� ���� ���
        SetTextColor(0b0111, 0b0000);
        cout << screenBuf;
        GameStateCheck();

        SetTextColor(0b0000, 0b1111);
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
        isGamePlaying = setTitleToScreen(recordScore);
        break;
    case GameStartState:    //���� ���� ~ ���� ����
        setSpeed = selectGameDifficulty();
        summonApple = selectGameSummonApple();
        SetTextColor(0b0000, 0b1111);
        system("cls");

        finalScore = GamePlay.Run(setSpeed, summonApple);   //���� ����, ���� ���� �� ���� ��������
        recordScore = setGameOverToScreen(recordScore, finalScore);
        isGamePlaying = TitleState;
        break;
    case DescriptionState:  //���� ����
        setDescriptionToScreen();
        isGamePlaying = TitleState;
        break;
    case GameQuit:
        isGamePlaying = GameQuit;
        break;
    default:
        break;
    }
}