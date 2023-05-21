#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
using namespace std;

namespace MuSoeun
{
    class Componant {
    public:

        Componant() {}
        ~Componant() {}

        void Start() { }

        void Update() { }
    };


    class Object : public Componant {
    public:
        vector<Componant*> ComList; //오브젝트의 컴포넌트를 저장하는 리스트
        int CoordX = 10, CoordY = 5;

        Object() {}
        ~Object() {}

        //자식 클래스가 상속받은 후 메서드를 재정의?할 수 있도록 virtual 설정
        void virtual Render() {

        }

        //void setComponant() { }
    };

    class Snake : public Object {
    public:
        void Render(char* screenBuf, int x, int y, int width) {
            screenBuf[(width + 1) * y + x] = '#';
        }
    };

    class Scene
    {
    private:
        char screenBuf[51 * 20 + 1];

    public:
        int width = 50, height = 20;
        char input[10];

        vector<Object> objList; //오브젝트 리스트
        vector<Snake> snakeLine; //뱀 (콘솔 창 한 문자당 리스트 요소 한 개씩)

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

        void Draw() {
            for (int i = 0; i < snakeLine.size(); i++)
                //스크린, 뱀의 좌표, 스크린 가로 길이를 매개변수로
                snakeLine[i].Render(screenBuf, snakeLine[i].CoordX, snakeLine[i].CoordY, width);
            gotoxy(0, 0);
            cout << screenBuf << endl; // 뱀이 나타난 스크린 출력
        }


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
                        if (i == 0 || i == 1 || i == (width - 1) || i == (width - 2) || j == 0 || j == (height - 1))
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

        void ClearScreenBuf() {//char* screenBuf
            ReleaseScreenBuf();         //screenBuf 초기화
            system("cls");              //콘솔 내용 모두 지우기
            cout << screenBuf << endl;  //초기화된 screenBuf 출력
        }
        //if screenBut != nullptr(?) delete ㄱㄱ

        void ObjectCreate() {
            Snake snake;

            for (int i = 0; i < 5; i++)
            {
                snake.CoordX++;
                snakeLine.push_back(snake);
            }

            for (int i = 0; i < snakeLine.size(); i++)
                objList.push_back(snakeLine[i]);
        }
    };

    class MGameLoop : public Scene {
    public:
        void Run() {
            ClearScreenBuf(); //스크린 화면 초기화
            ObjectCreate(); //오브젝트 생성

            while (1) { //루프문
                Draw(); //뱀이 나타난 스크린 출력
                cout << "게임을 나가시려면 'z'를 누르시오" << endl;
                if (_kbhit()) {
                    if (_getch() == 'z') break;
                }
            }
        }
    };
}

