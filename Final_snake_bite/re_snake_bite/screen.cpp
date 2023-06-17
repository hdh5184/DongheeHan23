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

//"���Ѵ��б� VR���ӡ����а� 202027041 �ѵ���";

int clearBuffer(char* screenBuf, int width, int height)
{
	int i = 0;	/* ���� index */
	int j = 0;  /* ���� index */
	while (j < height)
	{
		while (i < width + 1) /* ���๮�ڶ����� + 1*/
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
	int Select = 1;		//�޴� ���� �Ǻ���
	int KeyEnent = 1;	//Ű �̺�Ʈ �ݺ���
	int keyInput = 1;	//�Է��� Ű �� ����

	while (1) {
		SetTextColor(0b0111, 0b0001);
		gotoxy(12, 3); cout << "���� �� ��� ���� �� ����";
		gotoxy(20, 4); cout << "Snake Bite";

		SetTextColor(0b0001, 0b1111);
		gotoxy(16, 6); cout << "�ְ� ��� - " << setw(4) << right << recordScore << "��";

		SetTextColor(0b0111, 0b0000);
		gotoxy(5, 8); cout << "[��, �� ����Ű�� ���� �޴��� �����ϼ���.]";
		gotoxy(4, 9); cout << "===========================================";
		gotoxy(7, 10); cout << " ���� ����    ���� ����    ���� ���� ";

		SetTextColor(0b0111, 0b0100);
		switch (Select) {	//���� �������� �޴� ǥ��
		case 1:
			gotoxy(7, 10); cout << "<���� ����>";
			gotoxy(6, 12); cout << "\"���̵��� �����ϰ� ������ �����մϴ�.\"   ";
			break;
		case 2:
			gotoxy(20, 10); cout << "<���� ����>";
			gotoxy(6, 12); cout << "    \"���ӿ� ���� ������ Ȯ���մϴ�.\"      ";
			break;
		case 0:
			gotoxy(33, 10); cout << "<���� ����>";
			gotoxy(6, 12); cout << " \"������ �����Ͽ� ���α׷��� �ݽ��ϴ�.\"";
			break;
		}

		SetTextColor(0b0111, 0b0000);
		gotoxy(4, 13); cout << "===========================================";
		gotoxy(6, 14); cout << "[Enter�� ���� ������ �޴��� �����մϴ�.]";

		while (KeyEnent) {
			if (_kbhit()) {
				keyInput = _getch();
				if (keyInput == 224) keyInput = _getch();	//����Ű�� ù ��°�� 224 ��ȯ
				if (Select == 0) Select = 3;				//0 ���Ϸ� ������ �� ������ �Ұ����� ������ ����

				switch (keyInput) {							//�� ��° ��ȯ ������ �޴� ����
				case Key_Left: Select--; break;
				case Key_Right: Select++; break;
				case Key_Enter: return Select % 3;			//������ �޴� �� ��ȯ
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
	gotoxy(12, 3); cout << "���� �� ��� ���� �� ����";
	gotoxy(20, 4); cout << "Snake Bite";

	SetTextColor(0b0111, 0b0000);
	gotoxy(20, 6); cout << "<���Ӽ���>";
	gotoxy(2, 8); cout << "1. ��,�� ����Ű�� ���� �̵���Ų��.";
	gotoxy(2, 9); cout << "2. ����� ������ ���� ���̰� �� ĭ �þ��.";
	gotoxy(2, 10); cout << "3. ����� ���� ���� ���� �ӵ��� �����Ѵ�.";
	gotoxy(2, 11); cout << "4. �� �Ӹ��� ���̳� ���� �ε����� ������ ������.";

	SetTextColor(0b0111, 0b0101);
	gotoxy(2, 12); cout << "*  ���� ���� �� ���̵��� ������ �� �ִ�.";

	SetTextColor(0b0111, 0b0000);
	gotoxy(8, 14); cout << "[Enter�� ���� Ÿ��Ʋ�� ���ư��ϴ�.]";

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
		gotoxy(12, 3); cout << "���� �� ��� ���� �� ����";
		gotoxy(20, 4); cout << "Snake Bite";

		SetTextColor(0b0111, 0b0000);
		gotoxy(4, 7); cout << "===========================================";
		gotoxy(5, 8); cout << " �ſ� ����      ����     �߰�     ����� ";

		SetTextColor(0b0111, 0b0100);
		switch (Select) {
		case 0:
			gotoxy(5, 8); cout << "<�ſ� ����>";
			gotoxy(4, 6); cout << "�ӵ� : ����(50)        *�ӵ��� �ִ� 200����";
			break;
		case 1:
			gotoxy(20, 8); cout << "<����>";
			gotoxy(4, 6); cout << "�ӵ� : �߰�(100)       *�ӵ��� �ִ� 200����";
			break;
		case 2:
			gotoxy(29, 8); cout << "<�߰�>";
			gotoxy(4, 6); cout << "�ӵ� : ����(150)       *�ӵ��� �ִ� 200����";
			break;
		case 3:
			gotoxy(38, 8); cout << "<�����>";
			gotoxy(4, 6); cout << "�ӵ� : �ִ� �ӵ�(200)  *�ӵ��� �ִ� 200����";
			break;
		}

		SetTextColor(0b0111, 0b0000);
		//gotoxy(4, 13); cout << "===========================================";
		gotoxy(9, 14); cout << "[Enter�� ���� ������ �����մϴ�.]";

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
		gotoxy(5, 12); cout << "   ��� 1��      ��� 3��      ��� 5�� ";

		SetTextColor(0b0111, 0b0101);
		switch (Select) {
		case 0:
			gotoxy(7, 12); cout << "<��� 1��>";
			gotoxy(4, 10); cout << "����� 1������ �����Ѵ�.";
			break;
		case 1:
			gotoxy(21, 12); cout << "<��� 3��>";
			gotoxy(4, 10); cout << "����� 3������ �����Ѵ�.";
			break;
		case 2:
			gotoxy(35, 12); cout << "<��� 5��>";
			gotoxy(4, 10); cout << "����� 5������ �����Ѵ�.";
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

//���� ������ �ְ� ����� �Ű������� ������
int setGameOverToScreen(int recordScore, int finalScore)
{
	SetTextColor(0b0100, 0b1111);
	gotoxy(11, 6); cout << "0000000000000000000000000000";
	gotoxy(11, 7); cout << "0                          0";
	gotoxy(11, 8); cout << "0           OOF!           0";
	gotoxy(11, 9); cout << "0                          0";
	gotoxy(11, 10);
	cout << "0 ���� ������ " << setw(4) << right << finalScore << "�� �̴�. 0";
	gotoxy(11, 11); cout << "0                          0";
	gotoxy(11, 12); cout << "0000000000000000000000000000";

	//�ְ� ��� ���� �� �޼��� ��� �� �ְ� ��� ����
	if (finalScore > recordScore) {
		recordScore = finalScore;
		SetTextColor(0b0001, 0b1111);
		gotoxy(10, 14); cout << "<����! �ʰ� ��� �� �� ���>";
	}

	//Ÿ��Ʋ ���� �� �ְ� ��� ��ȯ
	while (1) {
		if (_kbhit()) {
			if (_getch() == Key_Enter) return recordScore;
		}
	}
}