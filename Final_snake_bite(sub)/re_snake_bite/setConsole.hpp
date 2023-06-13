/* 커서 이동 함수*/
void gotoxy(int x, int y);

/* 콘솔 내 커서 숨기는 함수*/
void SetCursorState(bool visible);

/* 텍스트 색을 변경하는 함수*/
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