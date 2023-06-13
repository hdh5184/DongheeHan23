#define _CRT_SECURE_NO_WARNINGS

//방향키 값
#define Key_Enter 13
#define Key_Left 75
#define Key_Right 77

#define Move_Up 1
#define Move_Down 2
#define Move_Left 3
#define Move_Right 4

#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include "setConsole.hpp"
using namespace std;

namespace MuSoeun
{
    /*
    void SetTextColor(int backColor, int textColor) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
    }
   
    void gotoxy(int x, int y) {
        COORD pos = { x, y }; // 좌표 저장
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // pos에서 저장된 좌표로 커서 이동
    }

    void SetCursorState(bool visible) {
        CONSOLE_CURSOR_INFO consoleCursorInfo;
        consoleCursorInfo.bVisible = visible;
        consoleCursorInfo.dwSize = 1;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
    }
    */
    

    //게임 스크린의 너비, 높이
    int width = 50, height = 20;

    class Object {
    public:
        int CoordX = 10, CoordY = 5;

        Object() {}
        ~Object() {}

        //자식 클래스가 상속받은 후 메서드를 재정의?할 수 있도록 virtual 설정
        void Render(char* screenBuf, int x, int y, char cr) {
            screenBuf[(width + 1) * y + x] = cr;
        }
    };

    class Snake : public Object {
    public:
        
    };

    class Apple : public Object {
    public:
        
    };

    class Scene
    {
    private:
        char screenBuf[51 * 20 + 1];    //스크린 출력용 버퍼

    public:

        int score;                  //점수 저장용
        int speed;                  //속도 저장용

        vector<Object> objList;     //오브젝트 리스트
        vector<Snake> snakeLine;    //뱀 (콘솔 창 한 문자당 리스트 요소 한 개씩)
        vector<Apple> apples;       //사과
        Snake snake;
        Apple apple;
        

        

        /* 스크린, 뱀, 사과를 출력하는 함수*/
        void Draw() {
            ReleaseScreenBuf(); //스크린 버퍼 초기화
            for (int i = 0; i < snakeLine.size(); i++) {
                //스크린, 뱀의 좌표, 스크린 가로 길이를 매개변수로
                snakeLine[i].Render(screenBuf, snakeLine[i].CoordX, snakeLine[i].CoordY, 'x');

                //머리 부분은 다른 문자로
                if (i == snakeLine.size() - 1) snakeLine[i].Render(screenBuf, snakeLine[i].CoordX, snakeLine[i].CoordY, 'O');
            }

            //사과 출력
            apple.Render(screenBuf, apple.CoordX, apple.CoordY, '$');

            //뱀, 사과가 그려진 스크린 출력
            gotoxy(0, 0);

            for (int i = 0; i < strlen(screenBuf); i++)
            {
                switch (screenBuf[i]) {
                case 'x':
                    SetTextColor(0b0111, 0b1001); break;
                case 'O':
                    SetTextColor(0b0111, 0b0001); break;
                case '$':
                    SetTextColor(0b0111, 0b1100); break;
                default:
                    SetTextColor(0b0111, 0b0010); break;
                }
                cout << screenBuf[i];
            }
            cout << endl;
        }

        /*스크린 버퍼 초기화*/
        void ReleaseScreenBuf() { //테두리가 있는 스크린 저장
            int i = 0;	/* 가로 index */
            int j = 0;  /* 세로 index */
            while (j < height)
            {
                while (i < width + 1) /* 개행문자때문에 + 1*/
                {
                    if (i == width) screenBuf[i + (j * (width + 1))] = '\n';
                    else
                    {
                        if (i == 0 || i == (width - 1) || j == 0 || j == (height - 1))
                            screenBuf[i + (j * (width + 1))] = '#';
                        else
                            screenBuf[i + (j * (width + 1))] = ' ';
                    }
                    i = i + 1;
                }
                i = 0; j = j + 1;
            }
            screenBuf[height * (width + 1) - 1] = '\0';
        }

        /*초기 스크린 화면 초기화*/
        void ClearScreenBuf() {//char* screenBuf
            ReleaseScreenBuf();         //screenBuf 재설정
            system("cls");              //콘솔 내용 모두 지우기
            cout << screenBuf << endl;  //초기화된 screenBuf 출력
        }
        //if screenBut != nullptr(?) delete ㄱㄱ

        /*초기 게임 시작 시 오브젝트 초기화 및 생성*/
        void ObjectCreate() {
            snakeLine.clear();
            snake.CoordX = 10;
            snake.CoordY = 5;

            for (int i = 0; i < 10; i++)
            {
                snake.CoordX++;
                snakeLine.push_back(snake);
            }

            for (int i = 0; i < snakeLine.size(); i++)
                objList.push_back(snakeLine[i]);

            //사과 소환
            SummonApple();
        }

        /*사과 생성하는 함수*/
        void SummonApple() {
            int re = 0;                 //자리 중복 횟수
            bool falseSummon = false;   //자리 중복 확인용
            while (1) {
                falseSummon = false;

                //매 시간 난수 생성
                srand((unsigned)time(NULL) + re);

                //x, y 좌표 랜덤 설정
                apple.CoordX = (rand() % (width - 2)) + 1;
                apple.CoordY = (rand() % (height - 2)) + 1;

                //뱀과 사과 자리의 중복 확인
                for (int i = 0; i < snakeLine.size(); i++)
                {
                    if (snakeLine[i].CoordX == apple.CoordX && snakeLine[i].CoordY == apple.CoordY) {
                        //exit(1); 자리 중복 테스트용
                        re++; falseSummon = true; break;
                    }
                }

                //뱀과 사과 자리 중복 시 난수 재설정
                if (falseSummon) continue;
                else break;
            }
        }

        /*뱀 이동하는 함수*/
        int Move(int SnakeMove, int keyInput) {
            //int crash = 0;  //뱀 충돌 확인용

            switch (keyInput)
            {
            case Key_Left:
                switch (SnakeMove)
                {
                case Move_Up: SnakeMove = Move_Left; break;
                case Move_Down: SnakeMove = Move_Right; break;
                case Move_Left: SnakeMove = Move_Down; break;
                case Move_Right: SnakeMove = Move_Up; break;
                }
                break;
            case Key_Right:
                switch (SnakeMove)
                {
                case Move_Up: SnakeMove = Move_Right; break;
                case Move_Down: SnakeMove = Move_Left; break;
                case Move_Left: SnakeMove = Move_Up; break;
                case Move_Right: SnakeMove = Move_Down; break;
                }
                break;
            }

            //방향키 입력에 따른 뱀 이동 방향 저장
            switch (SnakeMove)
            {
            case Move_Up: snake.CoordY--; break;
            case Move_Down: snake.CoordY++; break;
            case Move_Left: snake.CoordX--; break;
            case Move_Right: snake.CoordX++; break;
            default: break;
            }

            snakeLine.push_back(snake);

            //뱀이 사과에 닿으면 사과 재생성
            if (snake.CoordX == apple.CoordX && snake.CoordY == apple.CoordY) {
                SummonApple(); score++;
                speed = (speed == 0) ? 0 : speed - 1;
            }
            else snakeLine.erase(snakeLine.begin());

            return SnakeMove;
        }
        
        /*충돌 유무 검사*/
        int Crash(int x, int y) {
            //뱀 머리가 벽에 닿거나 뱀의 몸에 닿으면 충돌 값 반환
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1 || screenBuf[(width + 1) * y + x] == 'x')
                return 0;
            else return 1;  //미 충돌 시 미 충돌 값 반환
        }
    };

    //게임 실행용
    class MGameLoop : public Scene {
    public:
        int GamePlay = 1;           //게임 실행 유무(0 : 게임 오버 / 1 : 게임 실행 중)
        int SnakeMove = Move_Right;  //초기 뱀 이동 방향 저장
        int keyInput;               //방향키 입력 값 저장용

        /*게임 실행 루프*/
        int Run(int setSpeed) {
            GamePlay = 1;           //게임 실행
            SnakeMove = Move_Right;  //초기 뱀 이동 방향은 오른 쪽
            score = 0; speed = setSpeed; //점수, 속도 초기화

            //스크린 화면 초기화 후 오브젝트 초기화 및 생성
            ClearScreenBuf();
            ObjectCreate();
            SetTextColor(0b0111, 0b0000);

            //게임 실행 루프
            while (GamePlay) {
                //뱀, 사과가 그려진 스크린 출력
                Draw();

                SetTextColor(0b0000, 0b1111);
                cout << "게임을 나가시려면 'Enter'를 누르시오" << endl;

                //속도에 따른 스크린 버퍼 출력 - 뱀 이동속도
                Sleep(speed);

                int keyEvent = 0;

                //키 입력 감지 시
                if (_kbhit()) {
                    switch (_getch()) {
                    case Key_Enter:
                        return score;
                    case 224:
                        keyInput = _getch();
                        if (keyInput == Key_Left || keyInput == Key_Right)
                        break;
                    }
                }
                SnakeMove = Move(SnakeMove, keyInput);
                keyInput = 0;

                //뱀 충돌 여부 검사
                GamePlay = Crash(snake.CoordX, snake.CoordY);

                SetTextColor(0b0000, 0b1111);
                cout << "점수 : " << score << "    이동 속도 : " << 200 - speed << endl;
            }

            //게임 오버 시 점수 기록에 저장할 점수 반환
            return score;
        }
    };
}