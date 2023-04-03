#include <iostream>
//#include <conio.h>
#include <ncurses>
#include <Windows.h>


char key = 0;										//�Է��� Ű�� ����(��?) ��! ������ ����
int game_state = 0, game_running = 1;				//game_state : ���� ��� / game_running : ���� Ȱ��ȭ(1), ���� ����(0)

int print_title_screen() {
	std::cout << "******************************************" << std::endl;
	std::cout << "*                                        *" << std::endl;
	std::cout << "*               ������ ����              *" << std::endl;
	std::cout << "*              (Snake Bite)              *" << std::endl;
	std::cout << "*                                        *" << std::endl;
	std::cout << "*     1.���� ����                        *" << std::endl;
	std::cout << "*     2.���� ����                        *" << std::endl;
	std::cout << "*     3.���� ��ŷ ����                   *" << std::endl;
	std::cout << "*     4.���� ���� (esc)                  *" << std::endl;
	std::cout << "******************************************" << std::endl;

	return 0;
}

int introduction_screen() {
	std::cout << "******************************************" << std::endl;
	std::cout << "*             ���� ���� ����             *" << std::endl;
	std::cout << "******************************************" << std::endl;
	std::cout << "Ÿ��Ʋ ȭ������ ���ư����? (Y/N)" << std::endl;

	return 0;
}

int input_key() {								// Ű �Է¿� ���� game_state �� ��ȯ
	while (true)
	{
		key = _getch();							// Ű �Է� �� �Է��� Ű�� �� ����

		switch (key)
		{
		case '1': game_state = 1; break;		// 1 �Է� ��
		case '2': game_state = 2; break;		// 2 �Է� �� ���� �ȳ� �������
		case '3': game_state = 3; break;		// 3 �Է� ��
		case '4': game_state = 4; break;		// 4 �Է� �� ���� ����
		case 27: game_state = 27; break;		// esc �Է� �� ���� ����
		default: continue;						// �� case�� �ش����� �ʴ� Ű�� ������ Ű while �ݺ��� ó������ �ٽ�
		}
		break;									// �´� Ű �Է��Ͽ����� while �ݺ��� ����
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
	COORD pos = { x, y }; // ��ǥ ����

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // pos���� ����� ��ǥ�� Ŀ�� �̵�
	std::cout << "������ �����Ϸ��� ESCŰ ������";

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
		switch (game_state)						// game_state ���� ���� �ൿ(?)
		{
		case 0: 
			print_title_screen();				// ��ũ�� ���
			input_key();

			break;
		case 1:
			gotoxy(5, 5);
			input_key_mode1();

			break;
		case 2 :
			introduction_screen();				// ���� ���� ���
			input_key_mode2();

			break;
		case 4: game_running = 0; break;
		case 27: game_running = 0; break;
		default: break;
		}
	}
	std::cout << "������ �����Ͽ����ϴ�." << std::endl;
}