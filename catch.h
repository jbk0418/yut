#pragma once
#include <stdio.h>
#include<conio.h>
#include<windows.h>
#define X_MAX 55
#define Y_MAX 29

/*�� �� ���� �������� ���� ���ö�*/
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


typedef struct {
	int x, y;//��ǥ
	int  Teamcolor;//�� ����
	int Howmany;//���� ������
	int where;//���������� ��ġ�� ǥ��
	int cango[10];//�����ִ� ���� ��ġ ǥ��

}mal;
/*Howmany���� �������� �ö����� ������ -1�� �ö�������� 0�� �־��ش�.*/

typedef struct {
	int x, y;
}pan;

void gotoxy(int x, int y);
/*������Ͽ� ����*/

char cmp_cat_carry(mal **t, int x, int y, int index,int teamnum);					//���Լ� ���� ��쿣 1�� ���°�쿣 2�� �ƹ��͵� �ƴϸ�0�� ������
void carry(mal *t, int index);						//���� ���� �Լ�
void cat(mal **t, int index, int teamnum);							//���� ��� �Լ�


/*������*/
void setcolor(unsigned short text, unsigned short back);
void unsetcolor();
void color_title(char *t, unsigned short text, unsigned short back);
void color_menu(mal ** c);
void intro_color_set();


void team_mal(mal** t);			//���ǿ��� ����ϸ� ���������� ������ش�.


void print_all_mal(mal**t);/*���� ���� ����ϴ� �Լ�*/
int visiable(mal *t, int index);			//��°������� �Ǵ�
void print_mal(mal t);

extern int r;									//������ ���� �����ϴ� ����� �����ϴ� ��������
