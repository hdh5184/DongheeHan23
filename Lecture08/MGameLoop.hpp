#include <iostream>
#include <conio.h>
#include <windows.h>

#pragma once; //#define _IS_THIS_HEADER_INCLUDED

#define Key_ESC 27
#define Key_Left 'a'
#define Key_Right 'd'
#define Key_Enter 13

#define ANSI_COLOR_RED		"\x1b[31m" // ��
#define ANSI_COLOR_GREEN	"\x1b[32m" // ��
#define ANSI_COLOR_YELLOW	"\x1b[33m" // ��
#define ANSI_COLOR_RESET	"\x1b[0m" // ��


using namespace std;

namespace Geimu {

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

	class MGameLoop {
	public:
		MGameLoop() {

		}
		~MGameLoop() {

		}

		bool isGameRunning = false;
		bool ExitSet = false;

		void Initialize() { // ���� ���� �� �ʱ�ȭ
			isGameRunning = true;
			cout << ANSI_COLOR_RESET"���� �ʱ�ȭ" << endl;
		}
		
		void Release() { // ���� ���� �� �Ҹ�
			cout << ANSI_COLOR_RESET"���� ����Ǿ����ϴ�." << endl;
		}

		void Update() { // �ݺ� ����
			cout << ANSI_COLOR_RESET"���� Ű �Է� �����" << endl;
			if (_kbhit()) {
				KeyEvent(_getch());
			}
		}

		void Render() {
			cout << ANSI_COLOR_RESET"���� ȭ�� �׸���" << endl;

		}

		void KeyEvent(char KeyInput) {
			gotoxy(5, 5);
			switch (KeyInput)
			{
				// #define���� �̸� �����Ͽ� �� ��� Ȯ���?���� case ����

				/* �� �� ESC ������ ���� ���� ������ ��Ÿ��
				 * �� : ���� ���� / �ƴϿ� : �̾��ϱ�
				 */
			case Key_ESC:
				ExitSet = false; // �� : true / �ƴϿ� : false
				system("cls");
				gotoxy(5, 5);
				cout << "���� �Ͻðڽ��ϱ�?\n" << endl;
				cout << "     [ �� ] "<< ANSI_COLOR_YELLOW"[�ƴϿ�]" << endl;
				while (true)
				{
					gotoxy(0, 7);
					switch (_getch()) {
					case Key_Left:
						ExitSet = true;
						cout << ANSI_COLOR_YELLOW"     [ �� ] " << ANSI_COLOR_RESET"[�ƴϿ�]" << endl;
						continue;
					case Key_Right:
						ExitSet = false;
						cout << ANSI_COLOR_RESET"     [ �� ] " << ANSI_COLOR_YELLOW"[�ƴϿ�]" << endl;
						continue;
					case Key_Enter: 
						if (ExitSet == true) isGameRunning = false;
						break;
					default:
						continue;
					}
					system("cls");
					break;
				}
				break;
			case Key_Left:
				cout << ANSI_COLOR_RED"���� ��ư ����        " << endl;
				break;
			case Key_Right:
				cout << ANSI_COLOR_GREEN"������ ��ư ����       " << endl;
				break;
			case Key_Enter:
				cout << ANSI_COLOR_YELLOW"���� ��ư ����        " << endl;
				break;
			default:  // ����� �� �ٸ� Ű �Է��ϸ� ���� �Ͻ������ϰ� ���� �Է� Ű ���� Ȯ���� �� ����.
				break;
			}

			//���� ���� : esc ������ ���� ���� ���� ��� �ȳ�â�� �� �ƴϿ� ��ư���� �����ϴ� ��� �����
		}


		void Run(){
			SetCursorState(false);
			gotoxy(2, 9);
			Initialize(); // �ʱ�ȭ

			while (isGameRunning) // ���� ����
			{
				gotoxy(2, 10);
				Update(); // ������Ʈ
				gotoxy(2, 11);
				Render(); // ����
			}
			system("cls");

			Release(); // �Ҹ�
		}
	};
}

	