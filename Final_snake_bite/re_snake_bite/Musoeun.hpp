#define _CRT_SECURE_NO_WARNINGS

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
    class Object {
    public:
        int CoordX = 10, CoordY = 5;

        void virtual Render(char* screenBuf, int width, int x, int y, char cr) {
            screenBuf[(width + 1) * y + x] = cr;
        }
    };

    class Snake : public Object {
    public:
        void Render(char* screenBuf, int width, int x, int y, char cr) {   //���� �Ӹ�
            screenBuf[(width + 1) * y + x] = cr;
        }

        void Render(char* screenBuf, int width, int x, int y) {            //���� ����
            screenBuf[(width + 1) * y + x] = 'x';
        }
    };

    class Apple : public Object {
    public:
        void Render(char* screenBuf, int width, int x, int y) {            //���
            screenBuf[(width + 1) * y + x] = '$';
        }
    };

    class Scene : public Object
    {
    private:
        char screenBuf[51 * 20 + 1];    //��ũ�� ��¿� ����
        //���� ��ũ���� �ʺ�, ����
        int width = 50, height = 20;

    public:
        int score;                  //���� �����
        int speed;                  //�ӵ� �����

        vector<Snake> snakeLine;    //�� (�ܼ� â �� ���ڴ� ����Ʈ ��� �� ����)
        vector<Apple> Apples;
        Snake snake;
        Apple apple;
        
        /* ��ũ��, ��, ����� ����ϴ� �Լ�*/
        void Draw() {
            ReleaseScreenBuf(); //��ũ�� ���� �ʱ�ȭ
            for (int i = 0; i < snakeLine.size(); i++) {
                //��ũ��, ���� ��ǥ, ��ũ�� ���� ���̸� �Ű�������
                snakeLine[i].Render(screenBuf, width, snakeLine[i].CoordX, snakeLine[i].CoordY);

                //�Ӹ� �κ��� �ٸ� ���ڷ�
                if (i == snakeLine.size() - 1) snakeLine[i].Render(screenBuf, width, snakeLine[i].CoordX, snakeLine[i].CoordY, 'O');
            }

            for (int j = 0; j < Apples.size(); j++)
            {
                //��� ���
                Apples[j].Render(screenBuf, width, Apples[j].CoordX, Apples[j].CoordY);
            }

            

            //��, ����� �׷��� ��ũ�� ���
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
        void ObjectCreate(int setSummonApple) {
            snakeLine.clear();
            Apples.clear();
            snake.CoordX = 10;
            snake.CoordY = 10;

            for (int i = 0; i < 5; i++)
            {
                snake.CoordX++;
                snakeLine.push_back(snake);
            }

            
            switch (setSummonApple)
            {
            case 5:
                apple.CoordX = 33; apple.CoordY = 8; Apples.push_back(apple);
                apple.CoordX = 27; apple.CoordY = 12; Apples.push_back(apple);
            case 3:
                apple.CoordX = 27; apple.CoordY = 8; Apples.push_back(apple);
                apple.CoordX = 33; apple.CoordY = 12; Apples.push_back(apple);
            case 1:
                apple.CoordX = 30; apple.CoordY = 10; Apples.push_back(apple);
            }
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
                    for (int j = 0; j < Apples.size(); j++)
                    {
                        if (Apples[j].CoordX == apple.CoordX && Apples[j].CoordY == apple.CoordY) {
                            //exit(1); �ڸ� �ߺ� �׽�Ʈ��
                            re++; falseSummon = true; break;
                        }
                    }
                }
                //��� ��� �ڸ� �ߺ� �� ���� �缳��
                if (falseSummon) continue;
                else break;
            }
        }

        /*�� �̵��ϴ� �Լ�*/
        int Move(int SnakeMove, int keyInput) {
            //int crash = 0;  //�� �浹 Ȯ�ο�

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

            //����Ű �Է¿� ���� �� �̵� ���� ����
            switch (SnakeMove)
            {
            case Move_Up: snake.CoordY--; break;
            case Move_Down: snake.CoordY++; break;
            case Move_Left: snake.CoordX--; break;
            case Move_Right: snake.CoordX++; break;
            default: break;
            }

            snakeLine.push_back(snake);

            //���� ����� ������ ��� �����
            for (int i = 0; i < Apples.size(); i++)
            {
                if (snake.CoordX == Apples[i].CoordX && snake.CoordY == Apples[i].CoordY) {
                    SummonApple(); score++;
                    Apples.push_back(apple);
                    speed = (speed == 0) ? 0 : speed - 1;
                    Apples.erase(remove_if(Apples.begin(), Apples.end(), [&](Apple a)
                        { return a.CoordX == snake.CoordX && a.CoordY == snake.CoordY; }), Apples.end());
                    return SnakeMove;
                }
                else continue;
            }
            snakeLine.erase(snakeLine.begin());
            return SnakeMove;
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
    private:
        int GamePlay = 1;           //���� ���� ����(0 : ���� ���� / 1 : ���� ���� ��)
        int SnakeMove = Move_Right;  //�ʱ� �� �̵� ���� ����
        int keyInput;               //����Ű �Է� �� �����

    public:
        /*���� ���� ����*/
        int Run(int setSpeed, int setSummonApple) {
            GamePlay = 1;           //���� ����
            SnakeMove = Move_Right;  //�ʱ� �� �̵� ������ ���� ��
            score = 0; speed = setSpeed; //����, �ӵ� �ʱ�ȭ

            //��ũ�� ȭ�� �ʱ�ȭ �� ������Ʈ �ʱ�ȭ �� ����
            ClearScreenBuf();
            ObjectCreate(setSummonApple);
            SetTextColor(0b0111, 0b0000);

            //���� ���� ����
            while (GamePlay) {
                //��, ����� �׷��� ��ũ�� ���
                Draw();

                SetTextColor(0b0000, 0b1111);
                cout << "������ �����÷��� 'Enter'�� �����ÿ�" << endl;

                //�ӵ��� ���� ��ũ�� ���� ��� - �� �̵��ӵ�
                Sleep(speed);

                int keyEvent = 0;

                //Ű �Է� ���� ��
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

                //�� �浹 ���� �˻�
                GamePlay = Crash(snake.CoordX, snake.CoordY);

                SetTextColor(0b0000, 0b1111);
                cout << "���� : " << score << "    �̵� �ӵ� : " << 200 - speed << endl;
            }

            //���� ���� �� ���� ��Ͽ� ������ ���� ��ȯ
            return score;
        }
    };
}