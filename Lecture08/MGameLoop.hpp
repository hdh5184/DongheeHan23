#include <iostream>
#include <conio.h>
#include <windows.h>

#pragma once; //#define _IS_THIS_HEADER_INCLUDED

#define Key_ESC 27
#define Key_Left 'a'
#define Key_Right 'd'
#define Key_Enter 13

#define ANSI_COLOR_RED		"\x1b[31m" // 색
#define ANSI_COLOR_GREEN	"\x1b[32m" // 색
#define ANSI_COLOR_YELLOW	"\x1b[33m" // 색
#define ANSI_COLOR_RESET	"\x1b[0m" // 색


using namespace std;

namespace Geimu {

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

	class MGameLoop {
	public:
		MGameLoop() {

		}
		~MGameLoop() {

		}

		bool isGameRunning = false;
		bool ExitSet = false;

		void Initialize() { // 게임 시작 시 초기화
			isGameRunning = true;
			cout << ANSI_COLOR_RESET"게임 초기화" << endl;
		}
		
		void Release() { // 게임 종료 시 소멸
			cout << ANSI_COLOR_RESET"게임 종료되었습니다." << endl;
		}

		void Update() { // 반복 실행
			cout << ANSI_COLOR_RESET"게임 키 입력 대기중" << endl;
			if (_kbhit()) {
				KeyEvent(_getch());
			}
		}

		void Render() {
			cout << ANSI_COLOR_RESET"게임 화면 그리기" << endl;

		}

		void KeyEvent(char KeyInput) {
			gotoxy(5, 5);
			switch (KeyInput)
			{
				// #define으로 미리 정의하여 값 대신 확장명?으로 case 가능

				/* 한 번 ESC 누르면 게임 종료 선택지 나타남
				 * 예 : 게임 종료 / 아니오 : 이어하기
				 */
			case Key_ESC:
				ExitSet = false; // 예 : true / 아니오 : false
				system("cls");
				gotoxy(5, 5);
				cout << "종료 하시겠습니까?\n" << endl;
				cout << "     [ 예 ] "<< ANSI_COLOR_YELLOW"[아니오]" << endl;
				while (true)
				{
					gotoxy(0, 7);
					switch (_getch()) {
					case Key_Left:
						ExitSet = true;
						cout << ANSI_COLOR_YELLOW"     [ 예 ] " << ANSI_COLOR_RESET"[아니오]" << endl;
						continue;
					case Key_Right:
						ExitSet = false;
						cout << ANSI_COLOR_RESET"     [ 예 ] " << ANSI_COLOR_YELLOW"[아니오]" << endl;
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
				cout << ANSI_COLOR_RED"왼쪽 버튼 눌림        " << endl;
				break;
			case Key_Right:
				cout << ANSI_COLOR_GREEN"오른쪽 버튼 눌림       " << endl;
				break;
			case Key_Enter:
				cout << ANSI_COLOR_YELLOW"엔터 버튼 눌림        " << endl;
				break;
			default:  // 디버그 시 다른 키 입력하면 실행 일시정지하고 로컬 입력 키 값을 확인할 수 있음.
				break;
			}

			//오늘 과제 : esc 누르고 게임 나갈 지에 대안 안내창과 예 아니오 버튼마냥 선택하는 기능 만들기
		}


		void Run(){
			SetCursorState(false);
			gotoxy(2, 9);
			Initialize(); // 초기화

			while (isGameRunning) // 게임 루프
			{
				gotoxy(2, 10);
				Update(); // 업데이트
				gotoxy(2, 11);
				Render(); // 렌더
			}
			system("cls");

			Release(); // 소멸
		}
	};
}

	