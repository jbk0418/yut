#include <stdio.h>
#include <Windows.h>

void gotoxy(int x, int y);
void draw_basic_square(x, y);
void draw_score(int x, int y);
void draw_yutpan(int x, int y);
void board(int x, int y);
void mal_pan(int x, int y);
void insert_money(int a, int b);

int main(void)
{
	int k; //1,2 ÆÀÇ¥Çö
	int x, y;
	x = 1, y = 1;
	gotoxy(x, y);
	draw_basic_square(x, y);
	draw_basic_square(x + 10, y);
	draw_basic_square(x + 20, y);
	draw_basic_square(x + 30, y);
	draw_basic_square(x + 40, y);
	draw_basic_square(x + 50, y);
	x = 1, y = 5;
	draw_basic_square(x + 8, y);
	draw_basic_square(x + 42, y);
	x = 1, y = 6;
	draw_basic_square(x, y);
	draw_basic_square(x + 50, y);
	x = 1, y = 9;
	draw_basic_square(x + 17, y);
	draw_basic_square(x + 33, y);
	x = 1, y = 11;
	draw_basic_square(x, y);
	draw_basic_square(x + 50, y);
	x = 1, y = 14.5;
	draw_basic_square(x + 25, y);
	x = 1, y = 16;
	draw_basic_square(x, y);
	draw_basic_square(x + 50, y);
	x = 1, y = 18;
	draw_basic_square(x + 17, y);
	draw_basic_square(x + 33, y);
	x = 1, y = 21;
	draw_basic_square(x, y);
	draw_basic_square(x + 50, y);
	x = 1, y = 22;
	draw_basic_square(x + 8, y);
	draw_basic_square(x + 42, y);
	x = 1, y = 26;
	draw_basic_square(x, y);
	draw_basic_square(x + 10, y);
	draw_basic_square(x + 20, y);
	draw_basic_square(x + 30, y);
	draw_basic_square(x + 40, y);
	draw_basic_square(x + 50, y);
	

	
	printf("\n");


	x = 60;
	y = 1;
	printf("\n\n\n");
	draw_score(x, y);
	gotoxy(x + 6, y + 1);
	printf("=<1ÆÀ>=");

	printf("\n\n\n");

	y = 5;
	draw_yutpan(x, y);
	gotoxy(x + 6, y + 1);
	printf("<<°³>>");

	y = 24;

	draw_score(x, y);
	gotoxy(x + 3, y + 1);
	printf("ÆÀ 1 : ");
	gotoxy(x + 3, y + 2);
	printf("ÆÀ 2 : ");

	y = 28;
	mal_pan(x, y);
	gotoxy(x + 2, y + 1);
	printf("ÆÀ 1 : ");
	gotoxy(x + 2, y + 3);
	printf("ÆÀ 2 : ");

	x = 1;
	y = 30;
	board(x, y);
	gotoxy(x + 2, y + 2);
	printf("Everything");

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1 , y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_basic_square(int x, int y)			//no touch
{
	unsigned char a = 0xa6, b[7], i;
	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;
	gotoxy(x, y);
	printf("%c%c", a, b[3]);
	gotoxy(x + 2, y);
	printf("%c%c", a, b[1]);
	gotoxy(x + 4, y);
	printf("%c%c", a, b[4]);
	gotoxy(x, y + 1);
	printf("%c%c", a, b[2]);
	gotoxy(x + 4, y + 1);
	printf("%c%c", a, b[2]);
	gotoxy(x, y + 2);
	printf("%c%c", a, b[6]);
	gotoxy(x + 2, y + 2);
	printf("%c%c", a, b[1]);
	gotoxy(x + 4, y + 2);
	printf("%c%c", a, b[5]);
}

void draw_score(int x, int y)
{

	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[7];
	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;
	gotoxy(x, y);
	printf("%c%c", a, b[3]);
	for (int n = 1; n < 15; n++)
	{
		gotoxy(x + (n + 1), y);
		printf("%c%c", a, b[1]);
	}
	gotoxy(x + 16, y);
	printf("%c%c", a, b[4]);
	for (int k = 1; k < 3; k++)
	{
		gotoxy(x, y + k);
		printf("%c%c", a, b[2]);

		gotoxy(x + 16, y + k);
		printf("%c%c", a, b[2]);
	}
	gotoxy(x, y + 3);
	printf("%c%c", a, b[6]);
	for (int n = 1; n < 15; n++)
	{
		gotoxy(x + (n + 1), y + 3);
		printf("%c%c", a, b[1]);
	}
	gotoxy(x + 16, y + 3);
	printf("%c%c", a, b[5]);
	printf("\n");
	printf("\n");
}

void draw_yutpan(int x, int y)
{
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[7];
	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;

	gotoxy(x, y);					//À­º¯
	printf("%c%c", a, b[3]);
	for (int n = 1; n < 15; n++)
	{
		gotoxy(x + (n + 1), y);
		printf("%c%c", a, b[1]);
	}
	gotoxy(x + 16, y);
	printf("%c%c", a, b[4]);
	for (int k = 1; k < 18; k++)	//¼¼·Î
	{
		gotoxy(x, y + k);
		printf("%c%c", a, b[2]);

		gotoxy(x + 16, y + k);
		printf("%c%c", a, b[2]);
	}
	gotoxy(x, y + 18);				//¾Æ·§º¯
	printf("%c%c", a, b[6]);
	for (int n = 1; n < 15; n++)
	{
		gotoxy(x + (n + 1), y + 18);
		printf("%c%c", a, b[1]);
	}
	gotoxy(x + 16, y + 18);
	printf("%c%c", a, b[5]);


	printf("\n");
	printf("\n");
}

void board(int x, int y)
{
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[7];
	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;
	gotoxy(x, y);
	printf("%c%c", a, b[3]);
	for (int n = 1; n < 51; n++)		//°¡·Î
	{
		gotoxy(x + (n + 1), y);
		printf("%c%c", a, b[1]);

	}
	gotoxy(x + 52, y);
	printf("%c%c", a, b[4]);
	for (int k = 1; k < 6; k++)			//¼¼·Î
	{
		gotoxy(x, y + k);
		printf("%c%c", a, b[2]);

		gotoxy(x + 52, y + k);
		printf("%c%c", a, b[2]);
	}
	gotoxy(x, y + 6);
	printf("%c%c", a, b[6]);
	for (int m = 1; m < 51; m++)
	{
		gotoxy(x + (m + 1), y + 6);
		printf("%c%c", a, b[1]);

	}

	gotoxy(x + 52, y + 6);
	printf("%c%c", a, b[5]);
	printf("\n");
	printf("\n");


}

void mal_pan(int x, int y)
{
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[7];
	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;
	gotoxy(x, y);
	printf("%c%c", a, b[3]);
	for (int n = 1; n < 15; n++)
	{
		gotoxy(x + (n + 1), y);
		printf("%c%c", a, b[1]);
	}
	gotoxy(x + 16, y);
	printf("%c%c", a, b[4]);
	for (int k = 1; k < 4; k++)
	{
		gotoxy(x, y + k);
		printf("%c%c", a, b[2]);

		gotoxy(x + 16, y + k);
		printf("%c%c", a, b[2]);
	}
	gotoxy(x, y + 4);
	printf("%c%c", a, b[6]);
	for (int n = 1; n < 15; n++)
	{
		gotoxy(x + (n + 1), y + 4);
		printf("%c%c", a, b[1]);
	}
	gotoxy(x + 16, y + 4);
	printf("%c%c", a, b[5]);
	printf("\n");
	printf("\n");
}

void insert_money(int a, int b) {
	printf("1ÆÀÀÇ º£ÆÃ ±Ý¾×À» ÀÔ·ÂÇØ ÁÖ¼¼¿ä : \n");
	scanf("%d", &a);
	printf("2ÆÀÀÇ º£ÆÃ ±Ý¾×À» ÀÔ·ÂÇØ ÁÖ¼¼¿ä : \n");
	scanf("%d", &b);
}