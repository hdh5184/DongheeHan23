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

#include <algorithm>            //sort 배열 정렬 사용
#include <iomanip>              //setw 함수 사용
#include <stdio.h>
#include <vector>
#include "screen.hpp"
#include "Musoeun.hpp"

/* 랭킹 출력하는 함수*/
void RecordOutput(vector<int> record);

int main()
{
    char screenBuf[1000];           //화면 출력용 버퍼
    char string[300];               //스크린 별 출력할 내용 저장
    int width = 34;                 //버퍼의 너비
    int height = 12;                //버퍼의 높이
    int isGamePlaying = 10;         //현재 게임 상태 저장용 (목록 : 3~8번째 줄)
    int KeyEvent = 1;               //키 입력 이벤트 저장
    int KeyInput = 0;               //입력한 키 값 저장
    int recordScore;                //게임 종료 시 점수 가져오는 변수
    vector<int> Record(5, 0);       //점수 기록용 vector 배열
    

    MuSoeun::MGameLoop GamePlay;                        //게임 루프 실행용 객체 생성
    SetCursorState(false);                              //콘솔 내 커서 끄기
    clearBuffer(screenBuf, width, height);              //화면 버퍼 초기화
    setTitleToScreenBuffer(screenBuf, width, height);   //타이틀 화면 출력

    //게임 종료할 때 까지 (isGamePlaying == 0) 화면 출력
    while (isGamePlaying)
    {
        KeyEvent = 1;               //키 이벤트 초기화

        //게임 상태에 따른 화면 출력
        switch (isGamePlaying)
        {
        case TitleState:        //타이틀
            setTitleToScreenBuffer(screenBuf, width, height);
            strcpy(string, TitleString); break;
        case GameStartState:    //게임 시작 ~ 게임 오버
            recordScore = GamePlay.Run();   //게임 시작, 게임 오버 시 점수 가져오기
            system("cls");
            setGameOverToScreenBuffer(screenBuf, width, height);
            strcpy(string, GameOverString);
            isGamePlaying = GameOverState; break;
        case DescriptionState:  //게임 설명
            setDescriptionToScreenBuffer(screenBuf, width, height);
            strcpy(string, DescriptionString); break;
        case RankingState:      //게임 랭킹
            setRankingToScreenBuffer(screenBuf, width, height);
            strcpy(string, RankingString); break;
        default:
            break;
        }

        //스크린 버퍼 출력 후 스크린 내용 출력
        cout << screenBuf << "\ninput>";
        writeStringToBuffer(string, 5, 2);

        //게임 오버 시 점수 기록 저장
        if (isGamePlaying == GameOverState) {
            gotoxy(5, 4);
            cout << recordScore << " 점입니다.";

            //게임 최고기록 달성 시 내용 출력
            if (recordScore >= Record[0]) {
                gotoxy(5, 6);
                cout << "<최고 기록 달성>";
            }

            //점수 기록 후 점수가 높은 순으로 정렬 (5위 까지만 저장)
            Record.push_back(recordScore);
            sort(Record.rbegin(), Record.rend()); Record.erase(Record.end() - 1);
        }

        //게임 랭킹 출력 시 게임 기록 출력
        if (isGamePlaying == RankingState) RecordOutput(Record);

        //게임 상태 별 맞는 키 입력할 때 까지 반복
        while (KeyEvent)
        {
            if (_kbhit())   //키 입력 감지 시
            {
                KeyInput = _getch();    //입력한 키 값 저장

                //게임 상태 별 키 입력
                switch (isGamePlaying)
                {
                //메뉴 선택
                case TitleState:
                    switch (KeyInput)
                    {
                    case '1': isGamePlaying = GameStartState; break;
                    case '2': isGamePlaying = DescriptionState; break;
                    case '3': isGamePlaying = RankingState; break;
                    case '4': case 'q': isGamePlaying = 0; system("cls"); break;
                    default: continue;
                    } break;

                //뒤로 가기
                case GameStartState:
                case DescriptionState:
                case RankingState:
                case GameOverState:
                    if (KeyInput == 'z' || KeyInput == 'Z') { isGamePlaying = TitleState; break; }
                default:
                    continue;
                }
                KeyEvent = 0;   //맞는 키 입력 시 반복 종료
                system("cls");  //화면 지우기
            }
        }
    }

    //게임 종료 시
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