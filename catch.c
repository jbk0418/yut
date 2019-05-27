#include "catch.h"

/*color�Լ����� color.h�� color.c�� �̿��ϴ°��� ��õ��  */
/*�׸��� ���� ������ �����ϱ� ���ؼ��� color.c�� �ø� �Լ��� ����ؼ� ������ �ʱ�ȭ �ؾ���*/

 r = -1;									//������ ���� �����ϴ� ����� �����ϴ� �������� �ʱ�ȭ ����� extern���� ������


///////////////////////////////////////////
//             ������ �Լ���             //
///////////////////////////////////////////
/*���õ� ���� ���*/
void setcolor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
/*���� �ʱ�ȭ*/
void unsetcolor() {
	unsigned short back = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (back << 4));
}

/*���ڿ� �Է¹޾Ƽ� �Է¹��� ����� ��� -> �غ��� �߾ȵ� ������� ����*/
void color_title(char *t, unsigned short text, unsigned short back) {
	setcolor(text, back);
	printf("%s", t);
	unsetcolor();
}
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
/*��� ��ġ -> ������ �ʱ�ȭ �� �����ڸ��� ���*/
/*���ڻ�    ����   ->��ġ�� ���� ���� ���ϰ� �ؾߵ�*/
void color_menu(mal ** c) {


	int n, i = 0;
	int cmp = -1;

	/*���� �ȳ� */
	intro_color_set();

	for (i = 0; i < 1; i ++) {
		while (1) {
			printf("%d�� ������ �Է��ϼ��� : ", i+1);
			scanf("%d", &c[i][0].Teamcolor);

			/*������ ���ų� ������ ��� ���� �Է������� ������ ���� ������ ����*/
			if(c[i][0].Teamcolor<0||c[i][0].Teamcolor>15||c[i][0].Teamcolor ==c[!i][0].Teamcolor)
				printf("�� �� �Է��ϼ̽��ϴ�.\n\n");
			else
				break;
		}
		/*���� ���� ���������*/
		for (n = 1;  n<3; n++)
			c[i][n].Teamcolor = c[i][0].Teamcolor;
	}
	/*�ȳ��� ������ ����*/
	system("cls");
}


/*gotoxy�� ����ϱ� ���ؼ��� move.c���� ������ ���� �ʰų� gotoxy �����Լ��� ����� �ٸ� ��������� ����°��� ��õ*/
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

/*�����ġ : move �Լ����� key���� �޴°��� key = cmp_cat_carry(team, x, y, num, t); �� �����ؼ� ���*/

/*�Է�: ���� ������ ���� �迭, ���� ������ �� �ִ� ��ǥ, �ε��� ��ȣ��
  ��� : Ű���� �Է��� �޾� �״�� ������*/
  /*��� ���� �Լ��� 3���� ������ ���� ���� -> ������ �Ҷ� �ٷ� ������ �ȵǱ� ������
	��ų� ������ �ִ� ���� �Ǻ��� �� �ִ� �Լ��� ���� �������.*/
char cmp_cat_carry(mal **t, int x, int y, int index,int teamnum) {

	char key;
	int n;				//���ε���
	int d = 0;				//�� ��
	r = -1;				//����� ��Ÿ���� ��ų� ���°�찡 ������ -1������ 0 ������ 1�� ������

	/*�ݺ����� �̿��� ���� �� �ִ� ���� ã�´�.*/
	for (n = 0; n < 3; n++) {
		
		/*�ʱ�ȭ �Ǿ� �ִ� ������ �����Ұ�*/

		if (x == 53 && y == 20)break;

		/*���� �� ������ X�� ǥ�� */
		/*������ ��ǥ�� ���� ���� �ε����� �ƴҶ� -> ���°��*/
		else if(x == t[teamnum][n].x&&y == t[teamnum][n].y&&index != n)
		{
			/*goto�� �ش� ��ǥ�� �̵�*/
			gotoxy(x, y);

			/*���� �� �ִ� �� ����ǥ�� ex) ����! */
			if (t[teamnum][index].Howmany == -1 || t[teamnum][n].Howmany == -1) 
				d = 3;
			
			if (t[teamnum][index].Howmany == -1 && t[teamnum][n].Howmany == -1) 
				d = 2;

			setcolor(t[teamnum][index].Teamcolor, 0);

			printf("%d!",d );

			unsetcolor();
			r = 0;//��� ����
			break;
		}

		/*�ٸ����� ��ǥ�� ������ -> ��°��*/
		else if (x == t[!teamnum][n].x&&y == t[!teamnum][n].y) {
			/*goto�� �ش� ��ǥ �̵�*/
			gotoxy(x, y);
			/*X�� ǥ�� ������� ǥ��*/
			printf("X");
			r = 1;//��� ����
			break;

		}

	}


	/*Ű�Է� ó��*/

	key = getch();		//��ų� ������ ������ ������ �����̽� �Է�.

	/*��ų� ���� �ʰ� �������� �ٽ� ������ ���ڸ� ������ش�.*/
	if (key != 32) {

		
		if (r == 1||r==0) {		//��ų� ���� �� �ִ���쿡 �ٸ��� ����߱⿡ �����ִ� ���� �������

			print_all_mal(t);			//���� �ִ� ���� ������ش�.

			r = -1;					//��� �ʱ�ȭ
		}

	}
	return key;					//�Է¹��� key�� ��ȯ

}




/*Howmany�� ���� �� �÷����ִ��� �Ǵ�
  Howmnay �ʱⰪ -1
  �ö� ������ ���� �ִ¸�ŭ ex) 2���� ������ 2�� ����*/



/*�����ġ Ű���� �����̽�(32)�� ������ ��� ���
  move.c���� move�Լ����� �����̽� �Է��� �Ǵ��ϴ� if���ȿ� ���� x,y ��ǥ�����̶�� �ּ��� �޸� �Ʒ��� ����
  carry(team[t], num);				//��ų�
  cat(team, num, t);					//���´�.
 ���� �ִ°� �����ϰ� �����*/

/*�Է�: mal �迭, �̵��Ÿ�, ����ȣ
  �̵����Ŀ� ����Ұ�*/
void carry(mal *t, int index) {

	int n,l;
	int d = 0;

	if (r == 0) {//����� ���°���� ���


		for(n=0;n<3;n++) {
			/*��ǥ�� ����                     ��ȣ�� �ٸ����*/
			if (t[index].x == t[n].x&&t[index].y == t[n].y&&index != n) {

				/*� �����ִ��� if������ �����ؼ� ������ ���� 3�� ���̴� �ϳ��� 2�̻��̸� 3�̴�.*/
				if (t[n].Howmany == -1 || t[index].Howmany == -1)d = 3;

				/*�Ѵ� ������ ������ 2����*/
				if (t[n].Howmany == -1 && t[index].Howmany == -1)d=2;

				  t[index].Howmany = d;
				  t[n].Howmany=d;

				/*��ġ �ʱ�ȭ*/
				t[n].x = 66;
				t[n].y = 35;
				
				/*cango �ʱ�ȭ*/
				for (l = 0; l < 10; l++)
					t[n].cango[l] = 0;

				/*�� ��� ���� */
				gotoxy(t[index].x, t[index].y);
				/*���� ���*/
				setcolor(7, t[index].Teamcolor);
				printf("%d", t[index].Howmany);
				unsetcolor();

			}

		}


	}
}



void cat(mal **t, int index,int teamnum) {
	/*������ �ʱ�ȭ -> ���� ���� ���� �ʱ�ȭ*/
	/*�ʱ�ȭ�� ���� ���⵵�� �ٲܰ�*/

	int n,l;

	if (r == 1) {		//����� ��� ����� ���
		
		for(n=0;n<3;n++) {
			/*������� ��ǥ�� ���� ���*/
			
			if (t[teamnum][index].x == t[!teamnum][n].x&&t[teamnum][index].y == t[!teamnum][n].y) {

				/*������ �ʱ�ȭ*/
				for (l = 0; l < 3; l++) {
					if (t[!teamnum][n].Howmany == t[!teamnum][l].Howmany && n != l)
						t[!teamnum][l].Howmany = -1;
				}
				printf("�ʱ�");
				/*������ �ʱ�ȭ*/
				t[!teamnum][n].x = 66;
				t[!teamnum][n].y = 35;

				t[!teamnum][n].Howmany = -1;
			

				/*cango �ʱ�ȭ*/
				for (l = 0; l < 10; l++)
					t[!teamnum][n].cango[l] = 0;
				
				gotoxy(t[teamnum][index].x, t[teamnum][index].y);
				/*���� ���� ��������� ����ϰ� �ƴϸ� �������*/
				if (t[teamnum][index].Howmany == 0)printf("��");

				else {/*�۾��� ������ ������ �ٸ��� ���߿� �����Ұ�*/
					setcolor(7, t[teamnum][index].Teamcolor);
					printf("%d", t[teamnum][index].Howmany);
					unsetcolor();
				}

			}
		}
	}
}

/*�����ġ ó�� ���� ���� �ʱ�ȭ ������ �����
  �׸��� move�Լ� �������� ���� �̵��� ���� �Ⱥκе鿡 ����ϸ��*/

/*���� �� ���   ���ǿ��� ����ϴ� �Լ�*/
void team_mal(mal **t) {
	int index = 0;
	int x1, x2, y1, y2;
	x1 = 79;
	x2 = 79;
	y1 = 36;
	y2 = 38;
	
	for (index = 0; index < 3; index++) {
		
		/*1���� gotoxy�� ����� x79 y36*/
		gotoxy(x1, y1);
		printf("           ");				//������ ����
		gotoxy(x1, y1);
		/*��ġ�� �ʱ��̰� �������� �ʴٸ� �����*/
		if (t[0][index].x == 66 && t[0][index].y == 35 && t[0][index].Howmany == -1) {
			setcolor(t[0][index].Teamcolor, 0);
			printf("��");/*�̺κ� �ٲܰ�*/
			unsetcolor();
			
			x1 += 2;
			/*�� �ʱ�ȭ*/
		}

		/*2���� gotoxy�� ����� x79 y38*/
		gotoxy(x2, y2);
		printf("           ");				//������ ����
		gotoxy(x2, y2);
		if (t[1][index].x == 66 && t[1][index].y == 35 && t[1][index].Howmany == -1) {

			/*�� �Լ�*/
			setcolor(t[1][index].Teamcolor, 0);
			printf("��");
			unsetcolor();

			x2 += 2;
			/*�� �ʱ�ȭ*/


		}
	}
}

/*���� ��ġ�� Ȯ���ؼ� �������� ��Ÿ���� ���� ������*/
int visiable(mal *t, int index) {
	if ((t[index].x == 66 && t[index].y == 35)/*�̺κп� ��������*/)
		return 0;
	return 1;
}

void print_mal(mal t) {
	/*����� ��ġ�� �̵�*/
	
	gotoxy(t.x, t.y);

	/*���� ���� ���� ���� �ٸ��� ����Ѵ�.*/
	if (t.Howmany >= 1) {
		setcolor(7, t.Teamcolor);
		printf(" %d", t.Howmany);
		unsetcolor();
	}
	/*���� ���� ������*/
	else {
		setcolor(t.Teamcolor,0);
		printf("��");
		unsetcolor();
	}
}

/*�����ġ*/

/*���� �������� �ִ� ������ �����*/
void print_all_mal(mal**t) {
	int i;
	
	for (i = 0; i < 3; i++) {

		/*1���� �� ���*/
	
		if (visiable(t[0],i)) {
			
			print_mal(t[0][i]);
		}

		/*2���� �����*/
		if (visiable(t[1],i)) {

			print_mal(t[1][i]);
		}

	}
	team_mal(t);

}