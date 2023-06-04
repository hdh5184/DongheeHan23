#define _CRT_SECURE_NO_WARNINGS

#define TitleState 10			//타이틀
#define GameStartState 1		//게임 시작
#define DescriptionState 2		//게임 설명
#define RankingState 3			//게임 랭킹
#define GameOverState 99		//게임 랭킹

#define TitleString "지렁이 게임\nSnake Bike\n\n\n1. 게임 시작\n2. 게임 설명\n3. 게임 랭킹 보기\n4. 게임 종료(q)\n\n\n"
#define DescriptionString "<게임 설명>\n\n1. 방향키로 뱀을 이동시킨다.\n2. 사과를 먹으면 뱀의 길이가 한 칸 늘어나고 점수가 1점 증가한다.\n3. 점수가 증가함에 따라 뱀의 이동 속도도 증가한다.\n4. 뱀의 머리가 벽 또는 뱀의 몸통에 부딪히면 게임이 끝난다.\n[돌아가기 : 'Z']\n\n\n"
#define RankingString "<지렁이 게임 랭킹>\n\n1st\n2nd\n3rd\n4th\n5th\n\n[돌아가기 : 'Z']\n\n\n"
#define GameOverString "죽었답니다\n이번 게임의 점수는\n\n\n\n[돌아가기 : 'Z']\n"

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
                cout << recordScore << " 점입니다.";
                if (recordScore >= Record[0]) {
                    gotoxy(5, 6);
                    cout << "<최고 기록 달성>";
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

    cout << "게임을 종료하였습니다." << endl;

    return 0;
}

void RecordOutput(vector<int> record) {
    for (int i = 0; i < 5; i++)
    {
        gotoxy(10, 4 + i);
        cout << setw(3) << right << record[i];
    }

}