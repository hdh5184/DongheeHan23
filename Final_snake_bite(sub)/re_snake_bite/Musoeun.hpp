#define _CRT_SECURE_NO_WARNINGS

//����Ű ��
#define Key_Enter 13
#define Key_Up 72
#define Key_Left 75
#define Key_Right 77
#define Key_Down 80

#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

namespace MuSoeun
{
    void SetTextColor(int backColor, int textColor) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
    }

    //���� ��ũ���� �ʺ�, ����
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
        void Render(char* screenBuf, int x, int y, char cr) {
            screenBuf[(width + 1) * y + x] = cr;
        }

        //void setComponant() { }
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
        char screenBuf[51 * 20 + 1];    //��ũ�� ��¿� ����

    public:

        int score;                  //���� �����
        int speed;                  //�ӵ� �����

        vector<Object> objList;     //������Ʈ ����Ʈ
        vector<Snake> snakeLine;    //�� (�ܼ� â �� ���ڴ� ����Ʈ ��� �� ����)
        vector<Apple> apples;       //���
        Snake snake;
        Apple apple;

        /*Ŀ�� �̵�*/
        void gotoxy(int x, int y) {
            COORD pos = { x, y }; // ��ǥ ����
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // pos���� ����� ��ǥ�� Ŀ�� �̵�
        }

        /* Ŀ�� �����*/
        void SetCursorState(bool visible) {
            CONSOLE_CURSOR_INFO consoleCursorInfo;
            consoleCursorInfo.bVisible = visible;
            consoleCursorInfo.dwSize = 1;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
        }

        /* ��ũ��, ��, ����� ����ϴ� �Լ�*/
        void Draw() {
            ReleaseScreenBuf(); //��ũ�� ���� �ʱ�ȭ
            for (int i = 0; i < snakeLine.size(); i++) {
                //��ũ��, ���� ��ǥ, ��ũ�� ���� ���̸� �Ű�������
                snakeLine[i].Render(screenBuf, snakeLine[i].CoordX, snakeLine[i].CoordY, 'x');

                //�Ӹ� �κ��� �ٸ� ���ڷ�
                if (i == snakeLine.size() - 1) snakeLine[i].Render(screenBuf, snakeLine[i].CoordX, snakeLine[i].CoordY, 'O');
            }

            //��� ���
            apple.Render(screenBuf, apple.CoordX, apple.CoordY, '$');

            //��, ����� �׷��� ��ũ�� ���
            gotoxy(0, 0);
            cout << screenBuf << endl;
        }

        /*��ũ�� ���� �ʱ�ȭ*/
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

        /*�ʱ� ��ũ�� ȭ�� �ʱ�ȭ*/
        void ClearScreenBuf() {//char* screenBuf
            ReleaseScreenBuf();         //screenBuf �缳��
            system("cls");              //�ܼ� ���� ��� �����
            cout << screenBuf << endl;  //�ʱ�ȭ�� screenBuf ���
        }
        //if screenBut != nullptr(?) delete ����

        /*�ʱ� ���� ���� �� ������Ʈ �ʱ�ȭ �� ����*/
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

            //��� ��ȯ
            SummonApple();
        }

        /*��� �����ϴ� �Լ�*/
        void SummonApple() {
            int re = 0;                 //�ڸ� �ߺ� Ƚ��
            bool falseSummon = false;   //�ڸ� �ߺ� Ȯ�ο�
            while (1) {
                falseSummon = false;

                //�� �ð� ���� ����
                srand((unsigned)time(NULL) + re);

                //x, y ��ǥ ���� ����
                apple.CoordX = (rand() % (width - 2)) + 1;
                apple.CoordY = (rand() % (height - 2)) + 1;

                //��� ��� �ڸ��� �ߺ� Ȯ��
                for (int i = 0; i < snakeLine.size(); i++)
                {
                    if (snakeLine[i].CoordX == apple.CoordX && snakeLine[i].CoordY == apple.CoordY) {
                        //exit(1); �ڸ� �ߺ� �׽�Ʈ��
                        re++; falseSummon = true; break;
                    }
                }

                //��� ��� �ڸ� �ߺ� �� ���� �缳��
                if (falseSummon) continue;
                else break;
            }
        }

        /*�� �̵��ϴ� �Լ�*/
        int Move(int keyInput) {
            int crash = 0;  //�� �浹 Ȯ�ο�

            //����Ű �Է¿� ���� �� �̵� ���� ����
            switch (keyInput)
            {
            case Key_Up: snake.CoordY--; break;
            case Key_Down: snake.CoordY++; break;
            case Key_Left: snake.CoordX--; break;
            case Key_Right: snake.CoordX++; break;
            default: break;
            }

            snakeLine.push_back(snake);

            //���� ����� ������ ��� �����
            if (snake.CoordX == apple.CoordX && snake.CoordY == apple.CoordY) {
                SummonApple(); score++; speed--;
            }
            else snakeLine.erase(snakeLine.begin());

            //�� �浹 ���� �˻�
            crash = Crash(snake.CoordX, snake.CoordY);

            //��, ��� ���
            Draw();

            //�浹 ���� ��ȯ (0 : �浹�� / 1 : �浹 ����)
            return crash;
        }

        /*�浹 ���� �˻�*/
        int Crash(int x, int y) {
            //�� �Ӹ��� ���� ��ų� ���� ���� ������ �浹 �� ��ȯ
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1 || screenBuf[(width + 1) * y + x] == 'x')
                return 0;
            else return 1;  //�� �浹 �� �� �浹 �� ��ȯ
        }
    };

    //���� �����
    class MGameLoop : public Scene {
    public:
        int GamePlay = 1;           //���� ���� ����(0 : ���� ���� / 1 : ���� ���� ��)
        int SnakeMove = Key_Right;  //�ʱ� �� �̵� ���� ����
        int keyInput;               //����Ű �Է� �� �����

        /*���� ���� ����*/
        int Run(int setSpeed) {
            GamePlay = 1;           //���� ����
            SnakeMove = Key_Right;  //�ʱ� �� �̵� ������ ���� ��
            score = 0; speed = 1000 / setSpeed; //����, �ӵ� �ʱ�ȭ

            //��ũ�� ȭ�� �ʱ�ȭ �� ������Ʈ �ʱ�ȭ �� ����
            ClearScreenBuf();
            ObjectCreate();
            MuSoeun::SetTextColor(Gray, Black);

            //���� ���� ����
            while (GamePlay) {
                //��, ����� �׷��� ��ũ�� ���
                Draw();
                cout << "������ �����÷��� 'Enter'�� �����ÿ�" << endl;

                //�ӵ��� ���� ��ũ�� ���� ��� - �� �̵��ӵ�
                Sleep(speed);

                //Ű �Է� ���� ��
                if (_kbhit()) {
                    keyInput = _getch();    //�Է� Ű �� ��ȯ
                    if (keyInput == Key_Enter) break;

                    //[����Ű�� Ű ���� �� �� ��ȯ�ϸ�, ó�� ��ȯ���� 224��.]
                    if (keyInput == 224) {
                        keyInput = _getch();    //�� ���� ��ȯ ���� ����Ű�� �´� �� ��ȯ

                        //���� �̵��ϴ� ������ �ݴ� �������� ��ȯ�� ������
                        if ((SnakeMove == Key_Left && keyInput != Key_Right) || (SnakeMove == Key_Right && keyInput != Key_Left) ||
                            (SnakeMove == Key_Up && keyInput != Key_Down) || (SnakeMove == Key_Down && keyInput != Key_Up)) {
                            SnakeMove = keyInput;   //������ �� �̵� ���� �� ����
                        }
                    }
                    keyInput = 0;
                }

                //���� ���� �ٷ� �� �� �̵� �� ��� ����
                cout << "���� ���� : " << score << endl;
                GamePlay = Move(SnakeMove);
            }

            //���� ���� �� ���� ��Ͽ� ������ ���� ��ȯ
            return score;
        }
    };
}

