#include <stdio.h>
#include<conio.h>
#include<windows.h>
#define X_MAX 20
#define Y_MAX 10// 4/8 ���� �����ؼ� ���� ���� �����Ҽ� �־����
#define MAX_PS 4

typedef struct pieces {
	int x=X_MAX-2 ,y=Y_MAX;//��ǥ
	int carry;//���� ������

}pic;
typedef struct TEAM {
	pic p[MAX_PS];
	int color;
	int score;
	int side;
}team;
//void move(mal* team,int x,int y, int dice);
void gotoxy(int x, int y);
void move_cursor(char key, team *s,int d);
int main()
{
	team t;
	char key;
	int d = 0;//��ĭ ����
	int x = X_MAX, y = Y_MAX;
	do {
		gotoxy(t.p->x+2,t.p->y);
		printf("<");
		key = getch();
		if (key == 32)
		{
			t.p->x = x;
			t.p->y = y;
			gotoxy(x - 2, y);
			printf("��");//������ ����� ���� ���� ��� �Ǹ� �� ���������� �Ѵ�
			printf("��ĭ �����̴��� �Է�:");
		scanf("%d", &d);
			continue;
		}
		printf("\b \b ");
		move_cursor(key, &t,d);
	} while (key != 27);//esc������ ����
}
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void move_cursor(char key, team *s,int d)
{
	switch (key)
	{
	/*case 72://��
		*y1 = *y1 - 2;
		if (*y1 < 1)
			*y1 = 1;
		break;*/
	case 75://��
		s->p->y += d ;
		break;
	case 77://��
		s->p->y -= d ;
		break;
	/*case 80://��
		*y1 = *y1 + 2;
		if (*y1 > Y_MAX)
			*y1 = Y_MAX;
		break;*/
	default:
		return;
	}
}