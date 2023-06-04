#define _CRT_SECURE_NO_WARNINGS

#define TitleState 10			//Ÿ��Ʋ
#define GameStartState 1		//���� ����
#define DescriptionState 2		//���� ����
#define RankingState 3			//���� ��ŷ
#define GameOverState 99		//���� ��ŷ

#define TitleString "������ ����\nSnake Bike\n\n\n1. ���� ����\n2. ���� ����\n3. ���� ��ŷ ����\n4. ���� ����(q)\n\n\n"
#define DescriptionString "<���� ����>\n\n1. ����Ű�� ���� �̵���Ų��.\n2. ����� ������ ���� ���̰� �� ĭ �þ�� ������ 1�� �����Ѵ�.\n3. ������ �����Կ� ���� ���� �̵� �ӵ��� �����Ѵ�.\n4. ���� �Ӹ��� �� �Ǵ� ���� ���뿡 �ε����� ������ ������.\n[���ư��� : 'Z']\n\n\n"
#define RankingString "<������ ���� ��ŷ>\n\n1st\n2nd\n3rd\n4th\n5th\n\n[���ư��� : 'Z']\n\n\n"
#define GameOverString "�׾���ϴ�\n�̹� ������ ������\n\n\n\n[���ư��� : 'Z']\n"

#include <algorithm>            //sort �迭 ���� ���
#include <iomanip>              //setw �Լ� ���
#include <stdio.h>
#include <vector>
#include "screen.hpp"
#include "Musoeun.hpp"

/* ��ŷ ����ϴ� �Լ�*/
void RecordOutput(vector<int> record);

int main()
{
    char screenBuf[1000];           //ȭ�� ��¿� ����
    char string[300];               //��ũ�� �� ����� ���� ����
    int width = 34;                 //������ �ʺ�
    int height = 12;                //������ ����
    int isGamePlaying = 10;         //���� ���� ���� ����� (��� : 3~8��° ��)
    int KeyEvent = 1;               //Ű �Է� �̺�Ʈ ����
    int KeyInput = 0;               //�Է��� Ű �� ����
    int recordScore;                //���� ���� �� ���� �������� ����
    vector<int> Record(5, 0);       //���� ��Ͽ� vector �迭
    

    MuSoeun::MGameLoop GamePlay;                        //���� ���� ����� ��ü ����
    SetCursorState(false);                              //�ܼ� �� Ŀ�� ����
    clearBuffer(screenBuf, width, height);              //ȭ�� ���� �ʱ�ȭ
    setTitleToScreenBuffer(screenBuf, width, height);   //Ÿ��Ʋ ȭ�� ���

    //���� ������ �� ���� (isGamePlaying == 0) ȭ�� ���
    while (isGamePlaying)
    {
        KeyEvent = 1;               //Ű �̺�Ʈ �ʱ�ȭ

        //���� ���¿� ���� ȭ�� ���
        switch (isGamePlaying)
        {
        case TitleState:        //Ÿ��Ʋ
            setTitleToScreenBuffer(screenBuf, width, height);
            strcpy(string, TitleString); break;
        case GameStartState:    //���� ���� ~ ���� ����
            recordScore = GamePlay.Run();   //���� ����, ���� ���� �� ���� ��������
            system("cls");
            setGameOverToScreenBuffer(screenBuf, width, height);
            strcpy(string, GameOverString);
            isGamePlaying = GameOverState; break;
        case DescriptionState:  //���� ����
            setDescriptionToScreenBuffer(screenBuf, width, height);
            strcpy(string, DescriptionString); break;
        case RankingState:      //���� ��ŷ
            setRankingToScreenBuffer(screenBuf, width, height);
            strcpy(string, RankingString); break;
        default:
            break;
        }

        //��ũ�� ���� ��� �� ��ũ�� ���� ���
        cout << screenBuf << "\ninput>";
        writeStringToBuffer(string, 5, 2);

        //���� ���� �� ���� ��� ����
        if (isGamePlaying == GameOverState) {
            gotoxy(5, 4);
            cout << recordScore << " ���Դϴ�.";

            //���� �ְ��� �޼� �� ���� ���
            if (recordScore >= Record[0]) {
                gotoxy(5, 6);
                cout << "<�ְ� ��� �޼�>";
            }

            //���� ��� �� ������ ���� ������ ���� (5�� ������ ����)
            Record.push_back(recordScore);
            sort(Record.rbegin(), Record.rend()); Record.erase(Record.end() - 1);
        }

        //���� ��ŷ ��� �� ���� ��� ���
        if (isGamePlaying == RankingState) RecordOutput(Record);

        //���� ���� �� �´� Ű �Է��� �� ���� �ݺ�
        while (KeyEvent)
        {
            if (_kbhit())   //Ű �Է� ���� ��
            {
                KeyInput = _getch();    //�Է��� Ű �� ����

                //���� ���� �� Ű �Է�
                switch (isGamePlaying)
                {
                //�޴� ����
                case TitleState:
                    switch (KeyInput)
                    {
                    case '1': isGamePlaying = GameStartState; break;
                    case '2': isGamePlaying = DescriptionState; break;
                    case '3': isGamePlaying = RankingState; break;
                    case '4': case 'q': isGamePlaying = 0; system("cls"); break;
                    default: continue;
                    } break;

                //�ڷ� ����
                case GameStartState:
                case DescriptionState:
                case RankingState:
                case GameOverState:
                    if (KeyInput == 'z' || KeyInput == 'Z') { isGamePlaying = TitleState; break; }
                default:
                    continue;
                }
                KeyEvent = 0;   //�´� Ű �Է� �� �ݺ� ����
                system("cls");  //ȭ�� �����
            }
        }
    }

    //���� ���� ��
    cout << "������ �����Ͽ����ϴ�." << endl;
    return 0;
}

void RecordOutput(vector<int> record) {
    for (int i = 0; i < 5; i++)
    {
        gotoxy(10, 4 + i);
        cout << setw(3) << right << record[i];
    }

}