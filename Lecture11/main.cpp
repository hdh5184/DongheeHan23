#define _CRT_SECURE_NO_WARNINGS

#define TitleState 10			//Ÿ��Ʋ
#define GameStartState 1		//���� ����
#define DescriptionState 2		//���� ����
#define RankingState 3			//���� ��ŷ
#define GameOverState 99		//���� ��ŷ

#define TitleString "������ ����\nSnake Bike\n\n\n1. ���� ����\n2. ���� ����\n3. ���� ��ŷ ����\n4. ���� ����(q)\n\n\n"
#define DescriptionString "<���� ����>\n\n��ŵ� �ƴ� �����̶� ���\n�ϴ� �� ���� ���״� ������ ���� ������.\n����Ű�� �����Դϴ�.\n[���ư��� : 'Z']\n\n\n"
#define RankingString "<������ ���� ��ŷ>\n\n1st\n2nd\n3rd\n4th\n5th\n\n[���ư��� : 'Z']\n\n\n"
#define GameOverString "�׾���ϴ�\n������������\n������������\n������������\n������������\n������������\n������������\n[���ư��� : 'Z']\n\n\n"

#include <stdio.h>
#include <conio.h>
#include "screen.hpp"
#include "Musoeun.hpp"


int main()
{
	char screenBuf[800];
	int width = 34;
	int height = 12;
	int isGamePlaying = 10;
	int KeyEvent = 1;

	char string[200];

    
	while (isGamePlaying)
	{
        MuSoeun::MGameLoop GamePlay;
		clearBuffer(screenBuf, width, height);

		setTitleToScreenBuffer(screenBuf, width, height); /* �̷������� ¥�ּ��� */

        while (isGamePlaying)
        {
            KeyEvent = 1;

            switch (isGamePlaying)
            {
            case TitleState:
                setTitleToScreenBuffer(screenBuf, width, height);
                strcpy(string, TitleString); break;
            case GameStartState:
                GamePlay.Run();
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

            printf("%s\ninput>", screenBuf);

            writeStringToBuffer(string, 5, 2);

            while (KeyEvent)
            {
                if (_kbhit())
                {
                    switch (isGamePlaying)
                    {
                    case TitleState:
                        switch (_getch())
                        {
                        case '1': isGamePlaying = GameStartState; break;
                        case '2': isGamePlaying = DescriptionState; break;
                        case '3': isGamePlaying = RankingState; break;
                        case '4': case 'q': isGamePlaying = 0; system("cls"); break;
                        default:
                            break;
                        } break;
                    case GameStartState:
                    case DescriptionState:
                    case RankingState:
                    case GameOverState:
                        if (_getch() == 'z') isGamePlaying = TitleState; break;
                    default:
                        break;
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

