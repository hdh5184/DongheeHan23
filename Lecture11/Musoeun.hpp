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
        vector<Componant*> ComList; //������Ʈ�� ������Ʈ�� �����ϴ� ����Ʈ
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

        vector<Object> objList; //������Ʈ ����Ʈ
        vector<Snake> snakeLine; //�� (�ܼ� â �� ���ڴ� ����Ʈ ��� �� ����)

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
            for (int i = 0; i < snakeLine.size(); i++)
                //��ũ��, ���� ��ǥ, ��ũ�� ���� ���̸� �Ű�������
                snakeLine[i].Render(screenBuf, snakeLine[i].CoordX, snakeLine[i].CoordY, width);
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
            ReleaseScreenBuf();         //screenBuf �ʱ�ȭ
            system("cls");              //�ܼ� ���� ��� �����
            cout << screenBuf << endl;  //�ʱ�ȭ�� screenBuf ���
        }
        //if screenBut != nullptr(?) delete ����

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
            ClearScreenBuf(); //��ũ�� ȭ�� �ʱ�ȭ
            ObjectCreate(); //������Ʈ ����

            while (1) { //������
                Draw(); //���� ��Ÿ�� ��ũ�� ���
                cout << "������ �����÷��� 'z'�� �����ÿ�" << endl;
                if (_kbhit()) {
                    if (_getch() == 'z') break;
                }
            }
        }
    };
}

