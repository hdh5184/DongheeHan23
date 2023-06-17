#define _CRT_SECURE_NO_WARNINGS

#define GameStartState 1		//게임 시작
#define DescriptionState 2		//게임 설명
#define TitleState 10			//타이틀
#define GameOverState 99		//게임 랭킹
#define GameQuit 0

#include "Musoeun.hpp"
#include "screen.hpp"
#include "setConsole.hpp"

/*현재 게임 상태 별 스크린 출력*/
void GameStateCheck();

char screenBuf[1000];           //화면 출력용 버퍼
int width = 52;                 //버퍼의 너비
int height = 18;                //버퍼의 높이
int isGamePlaying = 10;         //현재 게임 상태 저장용 (목록 : 3~8번째 줄)
int setSpeed = 0;
int summonApple = 0;
int recordScore = 0;                //게임 종료 시 점수 가져오는 변수
int finalScore = 0;

MuSoeun::MGameLoop GamePlay;                        //게임 루프 실행용 객체 생성

int main()
{
    SetCursorState(false);                              //콘솔 내 커서 끄기
    clearBuffer(screenBuf, width, height);              //화면 버퍼 초기화

    //게임 종료할 때 까지 (isGamePlaying == 0) 화면 출력
    while (isGamePlaying)
    {
        //스크린 버퍼 출력 후 스크린 내용 출력
        SetTextColor(0b0111, 0b0000);
        cout << screenBuf;
        GameStateCheck();

        SetTextColor(0b0000, 0b1111);
        system("cls");  //화면 지우기
    }
    //게임 종료 시
    cout << "게임을 종료하였습니다." << endl;
    return 0;
}

void GameStateCheck() {
    switch (isGamePlaying)
    {
    case TitleState:        //타이틀
        isGamePlaying = setTitleToScreen(recordScore);
        break;
    case GameStartState:    //게임 시작 ~ 게임 오버
        setSpeed = selectGameDifficulty();
        summonApple = selectGameSummonApple();
        SetTextColor(0b0000, 0b1111);
        system("cls");

        finalScore = GamePlay.Run(setSpeed, summonApple);   //게임 시작, 게임 오버 시 점수 가져오기
        recordScore = setGameOverToScreen(recordScore, finalScore);
        isGamePlaying = TitleState;
        break;
    case DescriptionState:  //게임 설명
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