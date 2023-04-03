#include <iostream>
//#include <conio.h>
#include <ncurses>
#include <Windows.h>


char key = 0;										//입력한 키의 문자(값?) 를! 저장할 변수
int game_state = 0, game_running = 1;				//game_state : 게임 모드 / game_running : 게임 활성화(1), 게임 종료(0)

int print_title_screen() {
	std::cout << "******************************************" << std::endl;
	std::cout << "*                                        *" << std::endl;
	std::cout << "*               지렁이 게임              *" << std::endl;
	std::cout << "*              (Snake Bite)              *" << std::endl;
	std::cout << "*                                        *" << std::endl;
	std::cout << "*     1.게임 시작                        *" << std::endl;
	std::cout << "*     2.게임 설명                        *" << std::endl;
	std::cout << "*     3.게임 랭킹 보기                   *" << std::endl;
	std::cout << "*     4.게임 종료 (esc)                  *" << std::endl;
	std::cout << "******************************************" << std::endl;

	return 0;
}

int introduction_screen() {
	std::cout << "******************************************" << std::endl;
	std::cout << "*             대충 게임 설명             *" << std::endl;
	std::cout << "******************************************" << std::endl;
	std::cout << "타이틀 화면으로 돌아갈까요? (Y/N)" << std::endl;

	return 0;
}

int input_key() {								// 키 입력에 따른 game_state 값 변환
	while (true)
	{
		key = _getch();							// 키 입력 시 입력한 키의 값 저장

		switch (key)
		{
		case '1': game_state = 1; break;		// 1 입력 시
		case '2': game_state = 2; break;		// 2 입력 시 게임 안내 출력으로
		case '3': game_state = 3; break;		// 3 입력 시
		case '4': game_state = 4; break;		// 4 입력 시 게임 종료
		case 27: game_state = 27; break;		// esc 입력 시 게임 종료
		default: continue;						// 위 case에 해당하지 않는 키를 누르면 키 while 반복문 처음부터 다시
		}
		break;									// 맞는 키 입력하였으면 while 반복문 종료
	}return 0;
}

int input_key_mode1() {
	while (true)
	{
		key = _getch();

		switch (key)
		{
		case 27: game_state = 0; break;
		default: continue;
		}
		break;
	}return 0;
}

int input_key_mode2() {
	while (true)
	{
		key = _getch();

		switch (key)
		{
		case 'y': game_state = 0; break;
		case 'Y': game_state = 0; break;
		default: continue;
		}
		break;
	}return 0;
}

void gotoxy(int x, int y) {
	COORD pos = { x, y }; // 좌표 저장

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // pos에서 저장된 좌표로 커서 이동
	std::cout << "게임을 종료하려면 ESC키 누르기";

	for (int i = 0; i < 12; i++)
	{
		pos.Y++;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		std::cout << "********************************" << std::endl;
	}

	pos.X = x + 1; pos.Y = y + 1;

	for (int i = 0; i < 10; i++)
	{
		pos.Y++;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		std::cout << "                              " << std::endl;
	}
}

int main() {

	
	while (game_running)
	{
		system("cls");
		switch (game_state)						// game_state 값에 따른 행동(?)
		{
		case 0: 
			print_title_screen();				// 스크린 출력
			input_key();

			break;
		case 1:
			gotoxy(5, 5);
			input_key_mode1();

			break;
		case 2 :
			introduction_screen();				// 게임 설명 출력
			input_key_mode2();

			break;
		case 4: game_running = 0; break;
		case 27: game_running = 0; break;
		default: break;
		}
	}
	std::cout << "게임을 종료하였습니다." << std::endl;
}