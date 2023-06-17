#include "screen.hpp"
#include "setConsole.hpp"
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <windows.h>

#define Key_Enter 13
#define Key_Left 75
#define Key_Right 77

using namespace std;

//"유한대학교 VR게임·앱학과 202027041 한동희";

int clearBuffer(char* screenBuf, int width, int height)
{
	int i = 0;	/* 가로 index */
	int j = 0;  /* 세로 index */
	while (j < height)
	{
		while (i < width + 1) /* 개행문자때문에 + 1*/
		{
			if (i == width)
				screenBuf[i + (j * (width + 1))] = '\n';
			else
			{
				if (i == 0 || i == (width - 1) || j == 0 || j == (height - 1))
					screenBuf[i + (j * (width + 1))] = '#';
				else
					screenBuf[i + (j * (width + 1))] = ' ';
			}
			i = i + 1;
		}
		i = 0;
		j = j + 1;
	}
	screenBuf[height * (width + 1) - 1] = '\0';
	return 0;
}

int setTitleToScreen(int recordScore)
{
	int Select = 1;		//메뉴 선택 판별용
	int KeyEnent = 1;	//키 이벤트 반복용
	int keyInput = 1;	//입력한 키 값 저장

	while (1) {
		SetTextColor(0b0111, 0b0001);
		gotoxy(12, 3); cout << "내가 뱀 띠라서 만든 뱀 게임";
		gotoxy(20, 4); cout << "Snake Bite";

		SetTextColor(0b0001, 0b1111);
		gotoxy(16, 6); cout << "최고 기록 - " << setw(4) << right << recordScore << "점";

		SetTextColor(0b0111, 0b0000);
		gotoxy(5, 8); cout << "[좌, 우 방향키를 눌러 메뉴를 선택하세요.]";
		gotoxy(4, 9); cout << "===========================================";
		gotoxy(7, 10); cout << " 게임 시작    게임 설명    게임 종료 ";

		SetTextColor(0b0111, 0b0100);
		switch (Select) {	//현재 선택중인 메뉴 표시
		case 1:
			gotoxy(7, 10); cout << "<게임 시작>";
			gotoxy(6, 12); cout << "\"난이도를 설정하고 게임을 시작합니다.\"   ";
			break;
		case 2:
			gotoxy(20, 10); cout << "<게임 설명>";
			gotoxy(6, 12); cout << "    \"게임에 대한 설명을 확인합니다.\"      ";
			break;
		case 0:
			gotoxy(33, 10); cout << "<게임 종료>";
			gotoxy(6, 12); cout << " \"게임을 종료하여 프로그램을 닫습니다.\"";
			break;
		}

		SetTextColor(0b0111, 0b0000);
		gotoxy(4, 13); cout << "===========================================";
		gotoxy(6, 14); cout << "[Enter를 눌러 선택한 메뉴를 실행합니다.]";

		while (KeyEnent) {
			if (_kbhit()) {
				keyInput = _getch();
				if (keyInput == 224) keyInput = _getch();	//방향키는 첫 번째로 224 반환
				if (Select == 0) Select = 3;				//0 이하로 내려갈 시 선택이 불가능한 현상을 방지

				switch (keyInput) {							//두 번째 반환 값으로 메뉴 선택
				case Key_Left: Select--; break;
				case Key_Right: Select++; break;
				case Key_Enter: return Select % 3;			//선택한 메뉴 값 반환
				}
				KeyEnent = 0;
			}
		}
		KeyEnent = 1;
		Select %= 3;
	}
}


int setDescriptionToScreen() {
	SetTextColor(0b0111, 0b0001);
	gotoxy(12, 3); cout << "내가 뱀 띠라서 만든 뱀 게임";
	gotoxy(20, 4); cout << "Snake Bite";

	SetTextColor(0b0111, 0b0000);
	gotoxy(20, 6); cout << "<게임설명>";
	gotoxy(2, 8); cout << "1. 좌,우 방향키로 뱀을 이동시킨다.";
	gotoxy(2, 9); cout << "2. 사과를 먹으면 뱀의 길이가 한 칸 늘어난다.";
	gotoxy(2, 10); cout << "3. 사과를 먹을 수록 뱀의 속도가 증가한다.";
	gotoxy(2, 11); cout << "4. 뱀 머리가 벽이나 몸에 부딪히면 게임이 끝난다.";

	SetTextColor(0b0111, 0b0101);
	gotoxy(2, 12); cout << "*  게임 시작 전 난이도를 선택할 수 있다.";

	SetTextColor(0b0111, 0b0000);
	gotoxy(8, 14); cout << "[Enter를 눌러 타이틀로 돌아갑니다.]";

	while (1) {
		if (_kbhit()) {
			if(_getch() == Key_Enter) return 10;
		}
	}
}

int selectGameDifficulty() {
	int Select = 0;
	int KeyEnent = 1;
	int keyInput = 1;

	while (1)
	{
		SetTextColor(0b0111, 0b0001);
		gotoxy(12, 3); cout << "내가 뱀 띠라서 만든 뱀 게임";
		gotoxy(20, 4); cout << "Snake Bite";

		SetTextColor(0b0111, 0b0000);
		gotoxy(4, 7); cout << "===========================================";
		gotoxy(5, 8); cout << " 매우 쉬움      쉬움     중간     어려움 ";

		SetTextColor(0b0111, 0b0100);
		switch (Select) {
		case 0:
			gotoxy(5, 8); cout << "<매우 쉬움>";
			gotoxy(4, 6); cout << "속도 : 느림(50)        *속도는 최대 200까지";
			break;
		case 1:
			gotoxy(20, 8); cout << "<쉬움>";
			gotoxy(4, 6); cout << "속도 : 중간(100)       *속도는 최대 200까지";
			break;
		case 2:
			gotoxy(29, 8); cout << "<중간>";
			gotoxy(4, 6); cout << "속도 : 높음(150)       *속도는 최대 200까지";
			break;
		case 3:
			gotoxy(38, 8); cout << "<어려움>";
			gotoxy(4, 6); cout << "속도 : 최대 속도(200)  *속도는 최대 200까지";
			break;
		}

		SetTextColor(0b0111, 0b0000);
		//gotoxy(4, 13); cout << "===========================================";
		gotoxy(9, 14); cout << "[Enter를 눌러 게임을 시작합니다.]";

		while (KeyEnent) {
			if (_kbhit()) {
				keyInput = _getch();
				if (keyInput == 224) keyInput = _getch();
				if (Select == 0) Select = 4;

				switch (keyInput) {
				case Key_Left: Select--; break;
				case Key_Right: Select++; break;
				case Key_Enter: 
					switch (Select % 4)
					{
					case 0: return 150;
					case 1: return 100;
					case 2: return 50;
					case 3: return 0;
					}
				}
				KeyEnent = 0;
			}
		}
		KeyEnent = 1;
		Select %= 4;
	}
}

int selectGameSummonApple() {
	int Select = 0;
	int KeyEnent = 1;
	int keyInput = 1;
	while (1) {
		SetTextColor(0b0111, 0b0000);
		gotoxy(4, 11); cout << "===========================================";
		gotoxy(5, 12); cout << "   사과 1개      사과 3개      사과 5개 ";

		SetTextColor(0b0111, 0b0101);
		switch (Select) {
		case 0:
			gotoxy(7, 12); cout << "<사과 1개>";
			gotoxy(4, 10); cout << "사과를 1개까지 생성한다.";
			break;
		case 1:
			gotoxy(21, 12); cout << "<사과 3개>";
			gotoxy(4, 10); cout << "사과를 3개까지 생성한다.";
			break;
		case 2:
			gotoxy(35, 12); cout << "<사과 5개>";
			gotoxy(4, 10); cout << "사과를 5개까지 생성한다.";
			break;
		}

		while (KeyEnent) {
			if (_kbhit()) {
				keyInput = _getch();
				if (keyInput == 224) keyInput = _getch();
				if (Select == 0) Select = 3;

				switch (keyInput) {
				case Key_Left: Select--; break;
				case Key_Right: Select++; break;
				case Key_Enter:
					switch (Select % 3)
					{
					case 0: return 1;
					case 1: return 3;
					case 2: return 5;
					}
				}
				KeyEnent = 0;
			}
		}
		KeyEnent = 1;
		Select %= 3;
	}
}

//게임 점수와 최고 기록을 매개변수로 가져옴
int setGameOverToScreen(int recordScore, int finalScore)
{
	SetTextColor(0b0100, 0b1111);
	gotoxy(11, 6); cout << "0000000000000000000000000000";
	gotoxy(11, 7); cout << "0                          0";
	gotoxy(11, 8); cout << "0           OOF!           0";
	gotoxy(11, 9); cout << "0                          0";
	gotoxy(11, 10);
	cout << "0 너의 점수는 " << setw(4) << right << finalScore << "점 이다. 0";
	gotoxy(11, 11); cout << "0                          0";
	gotoxy(11, 12); cout << "0000000000000000000000000000";

	//최고 기록 도달 시 메세지 출력 후 최고 기록 갱신
	if (finalScore > recordScore) {
		recordScore = finalScore;
		SetTextColor(0b0001, 0b1111);
		gotoxy(10, 14); cout << "<놀라운! 너가 얻어 낸 새 기록>";
	}

	//타이틀 복귀 시 최고 기록 반환
	while (1) {
		if (_kbhit()) {
			if (_getch() == Key_Enter) return recordScore;
		}
	}
}