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

#include <stdio.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <iomanip>
#include "screen.hpp"
#include "Musoeun.hpp"

void RecordOutput(vector<int> record);

int main()
{
    char screenBuf[1000];
    int width = 34;
    int height = 12;
    int isGamePlaying = 10;
    int KeyEvent = 1;
    int KeyInput = 0;
    int recordScore;

    char string[300];

    vector<int> Record(5, 0);

    SetCursorState(false);

    while (isGamePlaying)
    {
        MuSoeun::MGameLoop GamePlay;
        clearBuffer(screenBuf, width, height);

        setTitleToScreenBuffer(screenBuf, width, height);

        while (isGamePlaying)
        {
            KeyEvent = 1;

            switch (isGamePlaying)
            {
            case TitleState:
                setTitleToScreenBuffer(screenBuf, width, height);
                strcpy(string, TitleString); break;
            case GameStartState:
                recordScore = GamePlay.Run();
                system("cls");
                setGameOverToScreenBuffer(screenBuf, width, height);
                strcpy(string, GameOverString);
                isGamePlaying = GameOverState; break;
            case DescriptionState:
                setDescriptionToScreenBuffer(screenBuf, width, height);
                strcpy(string, DescriptionString); break;
            case RankingState:
                setRankingToScreenBuffer(screenBuf, width, height);
                strcpy(string, RankingString); break;
            default:
                break;
            }

            cout << screenBuf << "\ninput>";
            //printf("%s\ninput>", screenBuf);

            writeStringToBuffer(string, 5, 2);
            if (isGamePlaying == GameOverState) {
                gotoxy(5, 4);
                cout << recordScore << " ���Դϴ�.";
                if (recordScore >= Record[0]) {
                    gotoxy(5, 6);
                    cout << "<�ְ� ��� �޼�>";
                }
                Record.push_back(recordScore);
                sort(Record.rbegin(), Record.rend()); Record.erase(Record.end() - 1);

            }
            if (isGamePlaying == RankingState) RecordOutput(Record);

            while (KeyEvent)
            {
                if (_kbhit())
                {
                    KeyInput = _getch();
                    switch (isGamePlaying)
                    {
                    case TitleState:
                        switch (KeyInput)
                        {
                        case '1': isGamePlaying = GameStartState; break;
                        case '2': isGamePlaying = DescriptionState; break;
                        case '3': isGamePlaying = RankingState; break;
                        case '4': case 'q': isGamePlaying = 0; system("cls"); break;
                        default: continue;
                        } break;
                    case GameStartState:
                    case DescriptionState:
                    case RankingState:
                    case GameOverState:
                        if (KeyInput == 'z' || KeyInput == 'Z') { isGamePlaying = TitleState; break; }
                    default:
                        continue;
                    }
                    KeyEvent = 0;
                    system("cls");
                }
            }
        }
    }

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