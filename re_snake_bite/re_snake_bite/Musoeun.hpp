#define _CRT_SECURE_NO_WARNINGS

#define Key_Up 72
#define Key_Left 75
#define Key_Right 77
#define Key_Down 80

#include <conio.h>
#include <iostream>
//#include <stdlib.h>
#include <vector>
#include <windows.h>
using namespace std;

namespace MuSoeun
{
    int width = 50, height = 20;

    class Componant {
    public:

        Componant() {}
        ~Componant() {}

        void Start() { }

        void Update() { }
    };

    class Componant1 : public Componant {

    };


    class Object : public Componant {
    public:
        vector<Componant> ComList; //������Ʈ�� ������Ʈ�� �����ϴ� ����Ʈ
        int CoordX = 10, CoordY = 5;

        Object() {}
        ~Object() {}

        //�ڽ� Ŭ������ ��ӹ��� �� �޼��带 ������?�� �� �ֵ��� virtual ����
        void virtual Render() {

        }

        //void setComponant() { }
    };

    class Snake : public Object {
    public:
        void Render(char* screenBuf, int x, int y, char cr) {
            screenBuf[(width + 1) * y + x] = cr;
        }
    };

    class Apple : public Object {
    public:
        void Render(char* screenBuf, int x, int y, char cr) {
            screenBuf[(width + 1) * y + x] = cr;
        }
    };

    class Scene
    {
    private:
        char screenBuf[51 * 20 + 1];

    public:

        int score;
        int speed;

        vector<Object> objList; //������Ʈ ����Ʈ
        vector<Snake> snakeLine; //�� (�ܼ� â �� ���ڴ� ����Ʈ ��� �� ����)
        vector<Apple> apples;
        Snake snake;
        Apple apple;

        void gotoxy(int x, int y) {
            COORD pos = { x, y }; // ��ǥ ����
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // pos���� ����� ��ǥ�� Ŀ�� �̵�
        }

        void SetCursorState(bool visible) {
            CONSOLE_CURSOR_INFO consoleCursorInfo;
            consoleCursorInfo.bVisible = visible;
            consoleCursorInfo.dwSize = 1;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
        }

        void Draw() {
            ReleaseScreenBuf();
            for (int i = 0; i < snakeLine.size(); i++) {
                //��ũ��, ���� ��ǥ, ��ũ�� ���� ���̸� �Ű�������
                snakeLine[i].Render(screenBuf, snakeLine[i].CoordX, snakeLine[i].CoordY, 'x');
                if (i == snakeLine.size() - 1) snakeLine[i].Render(screenBuf, snakeLine[i].CoordX, snakeLine[i].CoordY, 'O');
            }
            apple.Render(screenBuf, apple.CoordX, apple.CoordY, '$');
            gotoxy(0, 0);
            cout << screenBuf << endl; // ���� ��Ÿ�� ��ũ�� ���
        }


        void ReleaseScreenBuf() { //�׵θ��� �ִ� ��ũ�� ����
            int i = 0;	/* ���� index */
            int j = 0;  /* ���� index */
            while (j < height)
            {
                while (i < width + 1) /* ���๮�ڶ����� + 1*/
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

        void ClearScreenBuf() {//char* screenBuf
            ReleaseScreenBuf();         //screenBuf �ʱ�ȭ
            system("cls");              //�ܼ� ���� ��� �����
            cout << screenBuf << endl;  //�ʱ�ȭ�� screenBuf ���
        }
        //if screenBut != nullptr(?) delete ����

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

            SummonApple();
        }

        void SummonApple() {
            int re = 0;
            bool falseSummon = false;
            while (1) {
                falseSummon = false;
                srand((unsigned)time(NULL) + re);
                apple.CoordX = (rand() % (width - 2)) + 1;
                apple.CoordY = (rand() % (height - 2)) + 1;

                for (int i = 0; i < snakeLine.size(); i++)
                {
                    if (snakeLine[i].CoordX == apple.CoordX && snakeLine[i].CoordY == apple.CoordY) {
                        //exit(1); �׽�Ʈ��
                        re++; falseSummon = true; break;
                    }
                }
                if (falseSummon) continue;
                else break;
            }
        }

        int Move(int keyInput) {
            int crash = 0;
            switch (keyInput)
            {
            case Key_Up: snake.CoordY--; break;
            case Key_Down: snake.CoordY++; break;
            case Key_Left: snake.CoordX--; break;
            case Key_Right: snake.CoordX++; break;
            default: break;
            }


            snakeLine.push_back(snake);
            if (snake.CoordX == apple.CoordX && snake.CoordY == apple.CoordY) {
                SummonApple(); score++; speed--;
            }
            else snakeLine.erase(snakeLine.begin());
            crash = Crash(snake.CoordX, snake.CoordY);
            Draw();

            return crash;

        }

        int Crash(int x, int y) {
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1 || screenBuf[(width + 1) * y + x] == 'x')
                return 0;
            else return 1;
        }
    };

    class MGameLoop : public Scene {
    public:
        int GamePlay = 1;
        int SnakeMove = Key_Right;
        int keyInput;
        int Run() {
            GamePlay = 1;
            SnakeMove = Key_Right;
            score = 0; speed = 100;
            ClearScreenBuf(); //��ũ�� ȭ�� �ʱ�ȭ
            ObjectCreate(); //������Ʈ ����

            while (GamePlay) { //������
                Draw(); //���� ��Ÿ�� ��ũ�� ���
                cout << "������ �����÷��� 'z'�� �����ÿ�" << endl;
                Sleep(speed);
                if (_kbhit()) {
                    keyInput = _getch();
                    if (keyInput == 'z') break;
                    if (keyInput == 224) {
                        keyInput = _getch();
                        if ((SnakeMove == Key_Left && keyInput != Key_Right) || (SnakeMove == Key_Right && keyInput != Key_Left) ||
                            (SnakeMove == Key_Up && keyInput != Key_Down) || (SnakeMove == Key_Down && keyInput != Key_Up)) {
                            SnakeMove = keyInput;
                        }
                    }
                    keyInput = 0;
                }
                //score = snakeLine.size() - 10;
                cout << "���� ���� : " << score << endl;
                GamePlay = Move(SnakeMove);
            }
            return score;
        }
    };
}

