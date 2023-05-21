#define _CRT_SECURE_NO_WARNINGS

#define TitleState 10			//타이틀
#define GameStartState 1		//게임 시작
#define DescriptionState 2		//게임 설명
#define RankingState 3			//게임 랭킹
#define GameOverState 99		//게임 랭킹

#define TitleString "지렁이 게임\nSnake Bike\n\n\n1. 게임 시작\n2. 게임 설명\n3. 게임 랭킹 보기\n4. 게임 종료(q)\n\n\n"
#define DescriptionString "<게임 설명>\n\n당신도 아는 게임이라 어떻게\n하는 건 지는 알테니 설명은 대충 끝내죠.\n방향키로 움직입니다.\n[돌아가기 : 'Z']\n\n\n"
#define RankingString "<지렁이 게임 랭킹>\n\n1st\n2nd\n3rd\n4th\n5th\n\n[돌아가기 : 'Z']\n\n\n"
#define GameOverString "죽었답니다\n축하축하축하\n축하축하축하\n축하축하축하\n축하축하축하\n축하축하축하\n축하축하축하\n[돌아가기 : 'Z']\n\n\n"

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

		setTitleToScreenBuffer(screenBuf, width, height); /* 이런식으로 짜주세용 */

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

    cout << "게임을 종료하였습니다." << endl;

	return 0;
}

