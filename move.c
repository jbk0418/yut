#include <stdio.h>
#include<conio.h>
#include<windows.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct  {
	int x ,y;//��ǥ
	int  Teamcolor;//�� ����
	int Howmany;//���� ������
	int cango[5];//�����ִ� ���� ��ġ ǥ��
}mal;
typedef struct  {
	int x, y;
}pan;
pan basic[42];
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteMiddle(listNode* h, int key);

void setpan(pan* p);//������ �� ����
int canmove(int *go, listNode* h,int* yut);//���� ����ŭ ������ go��° �迭�� ��ǥ�� �����ְ���
void gotoxy(int x, int y);
void move_cursor(char key, int* can,const int max);//�����ִ� ��ġ�߿��� �����ֵ��� Ŀ���� ������
void initalize_mal(mal* team);
void move(int num, int *dice, mal* team1);
int select(mal team);//�� ����
int main()
{
	mal team1[3];
	int i = 0;
	int yut[5] = { 1,-1 };
	int yu[5] = { 4,1 };
	int u[5] = { 3 };
	int y[5] = { 4,1};
	setpan(basic);
	initalize_mal(team1);

	
 	move(1, yut, team1);
	
	move(0, yu, team1);
 	move(0, u, team1);
	move(0, y, team1);
}
int select(mal team)
{
	
	return 0;
}
//������ ���� �ʱ�ȭ
void initalize_mal(mal* team)
{
	int i = 0,j=0;
	for (i = 0; i < 3; i++)
	{
		team[i].x = 63;
		team[i].y=31;//��ǥ
	  team[i].Teamcolor=0;//�� ����
	 team[i].Howmany=0;//���� ������
	 for(j=0;j<5;j++)
	 team[i].cango[j]=0;//�����ִ� ���� ��ġ ǥ��
	}
	
}
//������ ���� ��ȣ�� ���� ���� ���� ����� �迭 ,��ü ������ ������ �޴´�
void move(int num,int *dice,mal* team1)
{
	listNode* headnode = NULL;
	
	int yut[5] = {0};//�̵��� ����Ʈ���� ���� �����Ҷ� ������ ����
	char key;
	int i = 0,temp=0;
	int max = 0;//���ǰ���
	int x = 0, y = 0;
	int check=0; //���� �������� Ȯ���ϴ� ����
	initialize(&headnode);
	
	for(i=0;i<5;i++)
		insertLast(headnode, dice[i]); //���� ���� �� ����Ʈ�� ����
	i = 0;
	max=canmove(team1[num].cango, headnode,yut);
	do {
		x = basic[team1[num].cango[i]].x;
		y = basic[team1[num].cango[i]].y;
		gotoxy(x+2, y);
		printf("<");
		key = getch();
		if (key == 32){ /*�����̽��� �Է�*/
			gotoxy(x + 2, y);
			printf(" ");//Ŀ������
			if(team1[num].x!=63 && team1[num].y!=31) //ó���� �ƴ϶��
			{
				gotoxy(team1[num].x, team1[num].y);
				printf("  ");//������ġ�� ���� ����
			}
			gotoxy(basic[team1[num].cango[i]].x, basic[team1[num].cango[i]].y);//������ ������ �̵�
			team1[num].x = basic[team1[num].cango[i]].x;//x,y ��ǥ ����
			team1[num].y = basic[team1[num].cango[i]].y;
			check = team1[num].cango[i];//���� �������� Ȯ��
			deleteMiddle(headnode, yut[i]); //�����ִ� ���� ���� �߿��� �̵��� ���� �� ���� 
			/*�̰��� ���� ������� �������� �Լ��� 
			ȣ���ϰ� �װ��� ����Ʈ�� ����*/
			printf("��");
			temp = team1[num].cango[i];
			for (i = 0; i < 5; i++)
				team1[num].cango[i] = temp;//�̵��� ������ cango �ʱ�ȭ
			i = 0;
			//�̵��� ��ġ���� ���� ���� ������ �̵��Ҽ��ִ� ��ġ ����
			max = canmove(team1[num].cango, headnode, yut); 
			continue;
		}
		//printf("\b \b");
		gotoxy(x + 2, y); //Ŀ���� ��ġ
		printf(" ");//Ŀ������
		move_cursor(key,&i,max); //����Ű�� �����̽��� �Է�
	} while (headnode->rlink != headnode&&check!=22);//�̵��� �� ���ų� ���� �������� �����
	freeList(headnode);
	return 0;
}
int initialize(listNode** h) {


	if (*h != NULL)
		freeList(*h);


	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}
int freeList(listNode* h) {

	if (h->rlink == h)
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink;

	listNode* prev = NULL;
	while (p != NULL && p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;
	if (key == 0)
		return 1;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = h;
	node->llink = h;

	if (h->rlink == h) 
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}
	else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}
int deleteMiddle(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while (n != NULL && n != h) {
		if (n->key == key) {
		
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			
			return 0;
		}

		n = n->rlink;
	}

	
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


void setpan(pan* p)
{
	int i = 0,j=41;
	for (i = 0; i <= 20; i++)
	{
		if (i < 6)
		{
			p[i].x = 65;
			if (i == 0)
			{
				p[i].y = 32;
				continue;
			}
			p[i].y = p[i - 1].y - 6;
		}
		else if (i < 11 && i >= 6)
		{
			p[i].y = 2;
			p[i].x = p[i - 1].x - 12;
		}
		else if (i >= 11 && i < 16)
		{
			p[i].x = 5;
			p[i].y = p[i - 1].y + 6;
		}
		else
		{
			p[i].y = 32;
			p[i].x = p[i - 1].x + 12;
		}
	}
    p[0].x = 63;
	p[0].y = 31;
	p[20].x = 63;
	p[20].y = 31;
	for (i = 21; i <= 26; i++)

	{
		p[i].x = 53;//���� �������� ����
		p[i].y = 17;
	}
	p[5].x = 63;
	p[5].y = 3;
	
	p[10].x = 7;
	p[10].y = 3;
	p[15].x = 7;
	p[15].y = 31;
	p[27].x = 55;
	p[27].y = 7;
	for (i=28; i <= 31; i++) //y=x ������ i=27~31
		p[i].y = p[i - 1].y + 5;
	for (i; i <= 36; i++)
	{
		p[i].y = 0;//�������� �������� ���� ��� 
		p[i].x = 0;//���� ���� ���ܵ� �迭����
	}
	for (i; i <= 41; i++) //y=-x������ i=37~41
		p[i].y = p[i - 10].y;
	i = 27;
	p[i++].x = 55;
	p[i++].x = 47;
	p[i++].x = 36;
	p[i++].x = 25;
	p[i++].x = 15;
	for (i=27; i <= 31; i++) 
	{
		p[j].x = p[i].x;
		j--;
	}
}
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void move_cursor(char key, int* can,const int max)
{
	switch (key)
	{
	case 75://��
		*can =*can- 1;
		if (*can < 0)
			*can = max;
		break;
	case 77://��
		*can = *can + 1;
		if (*can > max)
			*can = 0;
		break;
	default:
		return;
	}
}
int canmove(int *go, listNode* h,int* yut)
{
	int i = 0;
	listNode* n = h->rlink;
	while(n!=NULL&&n!=h)
	{
		yut[i] = n->key;
		if (go[i] == 5&&n->key!=-1) //�������� ĭ
		{
			go[i] = 27+n->key-1;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 10 && n->key != -1) //���� ��ĭ
		{
			go[i] = 37+n->key-1;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 29 && n->key != -1) //���߾� ĭ
		{
			go[i] = 39+n->key;
			if (go[i] > 42)
				go[i] = 22;
			i++;
			n = n->rlink;
			continue;
		}
		if(go[i]==27&&n->key==-1)//������ ó������ �鵵
		{
			go[i] = 5;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 37 && n->key == -1)//������ ó������ �鵵
		{
			go[i] = 10;
			i++;
			n = n->rlink;
			continue;
		}

		go[i] += n->key;
		if (go[i] == 42) //y=-x������ ������ ��ĭ�� ����
			go[i] = 20;

		if (go[i] > 31 && go[i] < 37) //y=x�� �󿡼� y=0 ������ �Ѿ��
			go[i] = go[i] - 17;
		
		if ((go[i] > 21 && go[i] < 27)||go[i]>42)//������
			go[i] = 22;
		if (go[i] == 0)
			go[i] = 20;
		i++;
		n = n->rlink;
		
	}
	return i-1;
}
