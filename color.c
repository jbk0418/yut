
/*�� ������ �Ұ�쿡 ������ ������ ������ �� ������ �ȵ� -> ���� �ʿ�*/
/*���ڻ� �ٲپ� ���-> ������ �ʱ�ȭ(15,7) �ι� ������ 9~ 15*/ /*-> �̵��� ��� ����?*/
/*���ڿ��� �Է¹޾� ����� �Լ��� ������ �ȴٸ� �ٽ� �ʱ�ȭ*/ /*�̵��� ����*/
#include <stdio.h>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	int x, y;//��ǥ
	int  Teamcolor;//�� ����
	int Howmany;//���� ������
	int where;//���������� ��ġ�� ǥ��
	int cango[5];//�����ִ� ���� ��ġ ǥ��

}mal;


void intro_color_set()
{
	printf("�� �� ����\n\n");
	printf("0: ������, 1: �Ķ���, 2: �ʷϻ�\n");
	printf("3: ����,   4: ������, 5: ���ֻ�\n");
	printf("6: �����, 7: ���,   8: ȸ��\n");
	printf("9: ���� �Ķ���,  10: ���� �ʷϻ� \n");
	printf("11: ���� ����,    12: ���� ������\n");
	printf("13: ���� ���ֻ�,  14: ���� �����\n");
	printf("15: ���� ���\n\n");
}

/*���ڻ�    ����   ->��ġ�� ���� ���� ���ϰ� �ؾߵ�*/
void color_menu(mal * c) {

	c->Teamcolor = 0;
	int n, i = 0;
	int cmp = -1;

	/*���� �ȳ� �ʿ�*/
	intro_color_set();
	for (i = 0; i <= 3; i += 3) {
		while (1) {
			printf("%d�� ������ �Է��ϼ��� : ", i / 3 + 1);
			scanf("%d", &c[i].Teamcolor);

			/*������ ���ų� ������ ��� ���� �Է������� ������ ���� ������ ����*/
			if (c[i].Teamcolor < 0 || c[i].Teamcolor>15 || c[i].Teamcolor == cmp)
				printf("�� �� �Է��ϼ̽��ϴ�.\n\n");
			else
				break;
		}
		/*���� ���� ���������*/
		for (n = i; i / 3 == n / 3; n++)
			c[n].Teamcolor = c[i].Teamcolor;
		cmp = c[i].Teamcolor;
	}
	/*�ȳ��� ������ ����*/
	system("cls");
}



/*���õ� ���� ���*/
void setcolor(unsigned short text, unsigned short back)			
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
/*���� �ʱ�ȭ*/
void unsetcolor() {
	unsigned short back=0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (back << 4));
}

/*���ڿ� �Է¹޾Ƽ� �Է¹��� ����� ��� */
void color_title(char *t, unsigned short text, unsigned short back) {
	setcolor(text, back);
	printf("%s", t);
	unsetcolor();
}
