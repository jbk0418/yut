#include "noriyut.h"

/*color�Լ����� color.h�� color.c�� �̿��ϴ°��� ��õ��  */
/*�׸��� ���� ������ �����ϱ� ���ؼ��� color.c�� �ø� �Լ��� ����ؼ� ������ �ʱ�ȭ �ؾ���*/
/*�������� 0, 20 �������� 22*/

r = -1; //������ ���� �����ϴ� ����� �����ϴ� �������� �ʱ�ȭ ����� extern���� ������

/*color_select�� ��� ���Ͽ� �߰��ϰ�
  intro�� �����Ѵ�.*/
void color_select(mal **t) {
	char key = NULL;
	int x = 32;
	int i = 0;
	int color=0;
	gotoxy(30, 20);
	for (int i = 10; i <= 15; i++) {
		setcolor(0, i);
		printf("      ");
		unsetcolor();
		printf(" ");
	}
	
	while (i!=2) {

	gotoxy(30, 10);
	printf("%d �� �÷��� ������ �ּ���",i+1);

		gotoxy(x, 22);
		printf("��");
		
		key = getch();

		color = (x - 32) / 7 + 10;

		if (key == 72 || key == 77) {			//������ Ȥ�� ����(���������� �̵�)
			gotoxy(x, 22);
			printf("  ");
			x += 7;
			
			if (x == 74) x = 32;
		}
		else if (key == 75 || key == 80) {		//���� Ȥ�� �Ʒ�(�������� �̵�
			gotoxy(x, 22);
			printf("  ");
			x -= 7;
			if (x == 25) x = 67;
		}
		else if (key == 32 || key == 13) {		//���� Ȥ�� �����̽�(����)
			if (color  == t[!i][0].Teamcolor) {
				gotoxy(35, 32);
				printf("�������� ���� �� �� �����ϴ�..\n\n");
			}

			else {
				gotoxy(x, 22);
				printf("  ");
				t[i][0].Teamcolor = color;
				gotoxy(x, 18);
				printf("%d��", i + 1);
				x = 32;
				i++;
			
			}
		}
	}
}

/*��� ��ġ -> ������ �ʱ�ȭ �� �����ڸ��� ���*/
/*���ڻ�    ����   ->��ġ�� ���� ���� ���ϰ� �ؾߵ�*/
void color_menu(mal ** c) {

			color_select(c);
		
		/*���� ���� ���������*/
		for (int i = 0; i < 2; i++) {
			for (int n = 0; n < 3; n++)
				c[i][n].Teamcolor = c[i][0].Teamcolor;
		}
	
	/*�ȳ��� ������ ����*/
	system("cls");
}




/*�Է�: ���� ������ ���� �迭, ���� ������ �� �ִ� ��ǥ, �ε��� ��ȣ��
��� : Ű���� �Է��� �޾� �״�� ������*/
/*��� ���� �Լ��� 3���� ������ ���� ���� -> ������ �Ҷ� �ٷ� ������ �ȵǱ� ������
��ų� ������ �ִ� ���� �Ǻ��� �� �ִ� �Լ��� ���� �������.*/
char cmp_cat_carry(mal **t, int x, int y, int index, int teamnum) {

	char key = NULL;
	int n;				//���ε���
	int d = 0;				//�� ��
	r = -1;				//����� ��Ÿ���� ��ų� ���°�찡 ������ -1������ 0 ������ 1�� ������

						/*�ݺ����� �̿��� ���� �� �ִ� ���� ã�´�.*/
	for (n = 0; n < 3; n++) {

		/*�ʱ�ȭ �Ǿ� �ִ� ������ �����Ұ�*/

		if (x == 51 && y == 20) {
			r = -1;
			break;
		}
		/*���� �� ������ X�� ǥ�� */

		/*������ ��ǥ�� ���� ���� �ε����� �ƴҶ� -> ���°��*/
		else if (x == t[teamnum][n].x&&y == t[teamnum][n].y&&index != n&&t[teamnum][n].where !=22&&t[teamnum][n].where!=0)	//���������̸� ���� �ʴ´�.
		{
			/*goto�� �ش� ��ǥ�� �̵�*/
			gotoxy(x, y);

			/*���� �� �ִ� �� ����ǥ�� ex) ����! */
			if (t[teamnum][index].Howmany == -1 || t[teamnum][index].Howmany == 0 || t[teamnum][n].Howmany == 0)
				d = 3;
			if ((t[teamnum][index].Howmany == -1 || t[teamnum][index].Howmany == 0) && t[teamnum][n].Howmany == 0)
				d = 2;
		
			setcolor(t[teamnum][index].Teamcolor, 0);

			printf("%d!", d);

			unsetcolor();
			r = 0;//��� ����
			break;
		}

		/*�ٸ����� ��ǥ�� ������ -> ��°��&&t[teamnum][n].cango[9] != 0*/
		else if (x == t[!teamnum][n].x&&y == t[!teamnum][n].y&&t[!teamnum][n].where!=22&&t[!teamnum][n].where != 0) {
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


		if (r == 1 || r == 0) {		//��ų� ���� �� �ִ���쿡 �ٸ��� ����߱⿡ �����ִ� ���� �������

			print_all_mal(t);			//���� �ִ� ���� ������ش�.

			r = -1;					//��� �ʱ�ȭ
		}

	}
	return key;					//�Է¹��� key�� ��ȯ

}




/*Howmany�� ���� �� �÷����ִ��� �Ǵ�
Howmnay �ʱⰪ -1
�ö� ������ ���� �ִ¸�ŭ ex) 2���� ������ 2�� ����*/




/*�Է�: mal �迭, �̵��Ÿ�, ����ȣ
�̵����Ŀ� ����Ұ�*/
void carry(mal *t, int index) {

	int n, l;
	int d = 0;

	if (r == 0) {//����� ���°���� ���


		for (n = 0; n<3; n++) {

			if (t[n].where == 22) {

			}

			/*��ǥ�� ����                     ��ȣ�� �ٸ����*/
			else if (t[index].x == t[n].x&&t[index].y == t[n].y&&index != n) {
			

				/*� �����ִ��� if������ �����ؼ� ������ ���� 3�� ���̴� �ϳ��� 2�̻��̸� 3�̴�.*/
				if (t[index].Howmany == -1 || t[index].Howmany == 0 || t[n].Howmany == 0)
					d = 3;
				if ((t[index].Howmany == -1 || t[index].Howmany == 0) && t[n].Howmany == 0)
					d = 2;

				/*�����ִ� ���鵵 ���� �־���*/
				if (t[index].Howmany > 0) {
					for (int k = 0; k < 3; k++) {
						if (t[k].Howmany == t[index].Howmany)
							t[k].Howmany = d;
					}
				}
				t[index].Howmany = d;
				t[n].Howmany = d;
				
				/*��ġ �ʱ�ȭ*/
				t[n].x = 64;
				t[n].y = 35;
				t[n].where = 0;
			
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



void cat(mal **t, int index, int teamnum) {
	/*������ �ʱ�ȭ -> ���� ���� ���� �ʱ�ȭ*/
	/*�ʱ�ȭ�� ���� ���⵵�� �ٲܰ�*/

	int n, l;
	
	if (r == 1) {		//����� ��� ����� ���

		for (n = 0; n<3; n++) {
			/*������� ��ǥ�� ���� ���*/
			if (t[!teamnum][n].where == 22){
			
			}

			else if (t[teamnum][index].x == t[!teamnum][n].x&&t[teamnum][index].y == t[!teamnum][n].y) {
				 
				/*������ �ʱ�ȭ*/
				if (t[!teamnum][n].Howmany != 0)
				for (l = 0; l < 3; l++) {
					if (t[!teamnum][n].Howmany == t[!teamnum][l].Howmany && n != l) {
						t[!teamnum][l].x = 64;
						t[!teamnum][l].y = 35;
						t[!teamnum][l].Howmany = -1;
						t[!teamnum][l].where = 0;
					}
				}
		
				/*������ �ʱ�ȭ*/
				t[!teamnum][n].x = 64;
				t[!teamnum][n].y = 35;

				t[!teamnum][n].where = 0;
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
 	x1 = 82;
	x2 = 82;
	y1 = 36;
	y2 = 38;

	for (index = 0; index < 3; index++) {

		/*1���� gotoxy�� ����� x79 y36*/
		gotoxy(x1, y1);
		printf("         ");				//������ ����
		gotoxy(x1, y1);
		/*��ġ�� �ʱ��̰� �������� �ʴٸ� �����*/
		if (t[0][index].x == 64 && t[0][index].y == 35 && t[0][index].Howmany == -1&&t[0][index].where ==0) {
			setcolor(t[0][index].Teamcolor, 0);
			printf("��");/*�̺κ� �ٲܰ�*/
			unsetcolor();

			x1 += 2;
			/*�� �ʱ�ȭ*/
		}

		/*2���� gotoxy�� ����� x79 y38*/
		gotoxy(x2, y2);
		printf("         ");				//������ ����
		gotoxy(x2, y2);
		if (t[1][index].x == 64 && t[1][index].y == 35 && t[1][index].Howmany == -1 && t[1][index].where == 0) {

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
	if (t[index].where == 22)
		return 0;
	if (t[index].where == 20)
		return 1;
	if ((t[index].where ==0)||(t[index].x ==51 &&t[index].y ==20)/*53 20�̺κп� ��������*/)
		return 0;
	return 1;
}

void print_mal(mal t) {
	/*����� ��ġ�� �̵�*/

	gotoxy(t.x, t.y);

	/*���� ���� ���� ���� �ٸ��� ����Ѵ�.*/
	if (t.Howmany >= 1) {
		if (t.Teamcolor != 15) {
			setcolor(7, t.Teamcolor);
			printf(" %d", t.Howmany);
			unsetcolor();
		}
		else {			/*�Ͼ���̸� ������ �ʱ� ������ ������ �۾��� �ٲپ��ش�.*/
			setcolor(0, t.Teamcolor);
			printf(" %d", t.Howmany);
			unsetcolor();
		}
	}
	/*���� ���� ������*/
	else {
		setcolor(t.Teamcolor, 0);
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

		if (visiable(t[0], i)) {

			print_mal(t[0][i]);
		}

		/*2���� �����*/
		if (visiable(t[1], i)) {

			print_mal(t[1][i]);
		}

	}
	print_score(t);
	//team_mal(t);

}

void print_score(mal**t) {
	int x1 = 83; /*�ٲܰ�*/
	int y1 = 31;
	int x2 = 83;
	int y2 = 33;
	
		for (int k = 0; k < 3; k++) {
			if (t[0][k].where == 22) {
				gotoxy(x1,y1);
				setcolor(t[0][k].Teamcolor, 0);
				printf("��");
				unsetcolor();
				x1 += 2;
			}
			if (t[1][k].where == 22) {
				gotoxy(x2, y2);
				setcolor(t[1][k].Teamcolor, 0);
				printf("��");
				unsetcolor();
				x2 += 2;
			}
		}
}