#include "noriyut.h"

int Select(mal* team)
{
	int i = 0;
	char key;
	int x=0, y = 0;
	if (team[0].where == 22 && team[1].where == 22 && team[2].where == 22) //��縻�� ���� �ߴٸ�
		return 3;
	do {
		//������ �϶� �߰�
		while (team[i].where == 22 ||(team[i].Howmany != -1&&team[i].Howmany!=0))
		{
			i=(i+1)%2; //���� �� �� �Ѿ �ٸ� ���� ǥ���ϰ� �Ѵ�
		}
		while (team[i].Howmany != -1 && team[i].Howmany != 0)
		{
			i = (i + 1) % 2;//���� �� �� �Ѿ �ٸ� ���� ǥ���ϰ� �Ѵ�
		}
		x = team[i].x + 4;
		y = team[i].y;
		if (team[i].where % 5 == 0 && team[i].where <= 20)
			x = x + 2;
		else if (team[i].where == 29 || team[i].where == 39)
			x = x + 2;
		gotoxy(x,y);
		printf("��");
		key = _getch();
		move_cursor(key, &i, 2);//������ i��° ���� ����
		while (team[i].where == 22||(team[i].Howmany != -1 && team[i].Howmany != 0))
		{
			move_cursor(key, &i, 2); //���� �� �� �Ѿ �ٸ� ���� ǥ���ϰ� �Ѵ�
		}

		printf("\b ");
	} while (key != 32); //�����̽��ٸ� ���� ����
	

	return i;
}
//������ ���� �ʱ�ȭ
mal** initalize_mal()
{
	
	int i = 0, j = 0, k = 0;
	team = (mal**)malloc(2 * sizeof(mal*));
	for (k = 0; k < 2; k++)
		team[k] = (mal*)malloc(3 * sizeof(mal));
	for (k = 0; k < 2; k++)
	{
		for (i = 0; i < 3; i++)
		{
			team[k][i].x = 64;
			team[k][i].y = 35;//��ǥ
			team[k][i].Teamcolor = 0;//�� ����
			team[k][i].Howmany = -1;//���� ������
			team[k][i].where = 0;
			for (j = 0; j < 10; j++)
				team[k][i].cango[j] = 0;//�����ִ� ���� ��ġ ǥ��
		}
	}
	return team;
} 
/*���� ������ ����ȣ, ���� ���� ���� ����� �迭 ,��ü ������ ������ �޴´�
yut�� ó���� ���� ���� ���� ������ �Լ� �߰��� */
void move(const int t, int *yut, mal** team)
{
	listNode* headnode = NULL;
	int num = 0;
	int i = 0, j = 0;
	//int temp[3] = { 0,0,0 }; //������ ���� ��ġ�� ����� ����
	int max = 0;//���ǰ���
	int x = 0, y = 0;
	int plus = 0; //���� �ѹ��� �������� ���°� ������ ����
	int check = 0; //���� �������� Ȯ���ϴ� ����
	char key;
	initialize(&headnode);

	for (i = 0; i<10; i++)
		insertLast(headnode, yut[i]); //���� ���� �� ����Ʈ�� ����
	i = 0;
	
	num = Select(team[t]);
	max = canmove(team[t][num].cango, headnode, yut);
	do {

		team_mal(team);

		x = basic[team[t][num].cango[i]].x;
		y = basic[team[t][num].cango[i]].y;
		gotoxy(x + 4, y);
		if (team[t][num].cango[i]% 5 == 0 && team[t][num].cango[i] <= 20) //ĭ�� ū���� �� ���� Ŀ���� �����δ�
			gotoxy(x + 6, y);
		else if (team[t][num].cango[i] == 29 || team[t][num].cango[i] == 39)
			gotoxy(x + 6, y);
		printf("��");
		key = cmp_cat_carry(team, x, y, num, t);
		//esc �Է½� ���� �ٽ� �����Ѵ�.
		if (key == 27)
		{
			printf("\b ");
			num = Select(team[t]);
			/*cango�� ��� �Ǿ��ִٸ� canmove()�� ȣ�� �����ʴ´�.
			���� ���� ���� ���� ���'����������������' �ϰ�� �Լ��� ȣ�� ���� ������
			���̳� �� 9�� �������� ������ ����Ƿ� ������� �ʾҴ�*/
			if (team[t][num].cango[0] == team[t][num].where)
				max = canmove(team[t][num].cango, headnode, yut);
			continue;
		}


		if (key == 32) { /*�����̽��� �Է�*/
			gotoxy(x + 4, y);
			if (team[t][num].cango[i] % 5 == 0 && team[t][num].cango[i] <= 20) //ĭ�� ū���� �� ���� Ŀ���� �����δ�
				gotoxy(x + 6, y);
			else if (team[t][num].cango[i] == 29 || team[t][num].cango[i] == 39)
				gotoxy(x + 6, y);
			printf(" ");//Ŀ������
			if (team[t][num].Howmany == -1)
				team[t][num].Howmany = 0;
			if (team[t][num].x != 64 && team[t][num].y != 35) //ó���� �ƴ϶��
			{
				gotoxy(team[t][num].x, team[t][num].y);
				printf("  ");//������ġ�� ���� ����
			}
			gotoxy(basic[team[t][num].cango[i]].x, basic[team[t][num].cango[i]].y);//������ ������ �̵�
			team[t][num].x = basic[team[t][num].cango[i]].x;//x,y ��ǥ ����
			team[t][num].y = basic[team[t][num].cango[i]].y;

			if (team[t][num].cango[i] != 22)
			{
				carry(team[t], num); // ��ų�
				cat(team, num, t); // ���´�
			}


			/*���*/
			print_all_mal(team);
			team_mal(team);


			deleteMiddle(headnode, yut[i]); //�����ִ� ���� ���� �߿��� �̵��� ���� �� ���� 
			if (r == 1)//�������� r
			{
				gotoxy(6, 41);
				printf("�����̽��ٸ� ���� ���� ��������"); //explain �Լ� ����ϵ��� �����ؾ���
				key = _getch();
				YUT = random();
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b'%d' �� ���Խ��ϴ� ", YUT);
				insertLast(headnode, YUT);
			}
			
			team[t][num].where = team[t][num].cango[i];//�̵��� ������ ������ġ ����
			for (j = 0; j < 3; j++)
				if (team[t][j].where != 22)
					for (i = 0; i < 10; i++)
						team[t][j].cango[i] = team[t][j].where;//cango �ʱ�ȭ
			if (team[t][num].where == 22)  //���� �����ϸ� �ٸ��� ����
				num = Select(team[t]);
			i = 0;
			if (num == 3)
				break;
			//�̵��� ��ġ���� ���� ���� ������ �̵��Ҽ��ִ� ��ġ ����
			max = canmove(team[t][num].cango, headnode, yut);
			continue;
		}

		gotoxy(x + 4, y); //Ŀ���� ��ġ
		if (team[t][num].cango[i] % 5 == 0 && team[t][num].cango[i] <= 20)
			gotoxy(x + 6, y);
		else if (team[t][num].cango[i] == 29 || team[t][num].cango[i] == 39)
			gotoxy(x + 6, y);
		printf(" ");//Ŀ������
		move_cursor(key, &i, max); //����Ű�� �����̽��� �Է�
	} while (headnode->rlink != headnode);//�̵��� �� ������� ���� ����
										  //cango�ʱ�ȭ �߰�
	for (j = 0; j < 3; j++)
		for (i = 0; i < 5; i++)
			team[t][j].cango[i] = team[t][j].where;//cango �ʱ�ȭ
	freeList(headnode);
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
/*���� �� ����*/
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
/*����Ʈ�� ����� ���� ��(key) ����*/
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
	int i = 0, j = 41;
	for (i = 0; i <= 20; i++)
	{
		if (i < 6)//�����ʱ�
		{
			p[i].x = 66;
			if (i == 0)//������ġ y��ǥ
			{
				p[i].y = 35;
				continue;
			}
			p[i].y = p[i - 1].y - 6;
		}
		else if (i < 11 && i >= 6)//���ʱ�
		{
			p[i].y = 5;
			p[i].x = p[i - 1].x - 12;
		}
		else if (i >= 11 && i < 16) //���ʱ�
		{
			p[i].x = 6;
			p[i].y = p[i - 1].y + 6;
		}
		else//�Ʒ���
		{
			p[i].y = 35;
			p[i].x = p[i - 1].x + 12;
		}
	}
	p[0].x = 64;
	p[0].y = 35;
	p[20].x = 64;
	p[20].y = 35;
	for (i = 21; i <= 26; i++)

	{
		p[i].x = 51;//���� �������� ����
		p[i].y = 20;
	}
	p[5].x = 64;
	p[5].y = 6;

	p[10].x = 8;
	p[10].y = 6;
	p[15].x = 8;
	p[15].y = 34;
	p[27].x = 8;
	p[27].y = 10;
	for (i = 28; i <= 31; i++) //y=x ������ y��ǥ ���� i=27~31
		p[i].y = p[i - 1].y + 5;
	p[27].y = 9;
	for (i; i <= 36; i++)
	{
		p[i].y = 0;//�������� �������� ���� ��� 
		p[i].x = 0;//���� ���� ���ܵ� �迭����
	}
	for (i; i <= 41; i++) //y=-x������ i=37~41
		p[i].y = p[i - 10].y;
	i = 27;
	p[i++].x = 56; //y=x x��ǥ
	p[i++].x = 48;
	p[i++].x = 37;
	p[i++].x = 26;
	p[i++].x = 16;
	for (i = 27; i <= 31; i++)
	{
		p[j].x = p[i].x;
		j--;
	}
}

/*���� �ÿ� ���� �ɼ� �ִ� ���̳� ��ġ�� ����(max) ,������ ���̳� ��ġ�� ��ȣ(can),ȭ��ǥŰ ��(key)*/
void move_cursor(char key, int* can, const int max)
{
	switch (key)
	{
	case 75://��
		*can = *can - 1;
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
/*basic[cango]���� cango���� ���Ѵ� */
int canmove(int *go, listNode* h, int* yut)
{
	int i = 0;
	listNode* n = h->rlink;

	while (n != NULL && n != h)
	{
		yut[i] = n->key;//�迭�� ���� ���� ����Ʈ�� ������ �ֽ�ȭ ��Ű�� ���Ŀ� ����Ʈ���� ���� ��ų�� ����Ѵ�
						//������ġ�� ���� Ư���� ��찡 �ִ��� ���Ѵ�
		if (go[i] == 5 && n->key != -1) //�������� ĭ
		{
			go[i] = 27 + n->key - 1;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 10 && n->key != -1) //���� ��ĭ
		{
			go[i] = 37 + n->key - 1;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 29 && n->key != -1) //���߾� ĭ
		{
			go[i] = 39 + n->key;
			if (go[i] > 42)
				go[i] = 22;
			if (go[i] == 42) //y=-x������ ������ ��ĭ�� ����
				go[i] = 20;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 27 && n->key == -1)//������ ó������ �鵵
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
		if (go[i] == 0 && n->key == -1) //���� ������� ���� ���̰� �鵵�ϰ��
		{
			n = n->rlink; //�̸��� �̵������� ��ġ���� �鵵�� ��츦 �������� �ʴ´�
			continue;
		}
		go[i] += n->key;//���� ����ŭ ����
		
		n = n->rlink;
		
		if (go[i] == 42) //y=-x������ ������ ��ĭ�� ����
			go[i] = 20;

		if (go[i] > 31 && go[i] < 37) //y=x�� �󿡼� y=0 ������ �Ѿ��
			go[i] = go[i] - 17;

		if ((go[i] > 20 && go[i] < 27) || go[i]>42)//������
			go[i] = 22;// cango�� 22�� ����
		if (go[i] == 0) //�鵵�� ó����ġ�� ������ ������ ��ġ�� �ٲ��ش�.
			go[i] = 20;
		
		i++;


	}
	return i - 1;
}
