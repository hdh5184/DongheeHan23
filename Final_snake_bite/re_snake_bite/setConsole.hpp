/* Ŀ�� �̵� �Լ�*/
void gotoxy(int x, int y);

/* �ܼ� �� Ŀ�� ����� �Լ�*/
void SetCursorState(bool visible);

/* �ؽ�Ʈ ���� �����ϴ� �Լ�*/
void SetTextColor(int backColor, int textColor);

/*					<Console Text Color>

	0b00xx	00			01			10			11
			Black,		DarkBlue,	DarkGreen,	DarkSkyBlue,
	0b01xx
			DarkRed,	DarkPurple,	DarkYellow,	Gray,
	0b10xx
			DarkGray,	Blue,		Green,		SkyBlue,
	0b11xx
			Red,		Purple,		Yellow,		White
*/