#include "noriyut.h"

int Select(mal* team)
{
	int i = 0;
	char key;
	int x = 0, y = 0;
	if (team[0].where == 22 && team[1].where == 22 && team[2].where == 22) //모든말이 골인 했다면
		return 3;
	do {
		//끝난말 일때 추가
		while (team[i].where == 22 || (team[i].Howmany >= 1 && team[i].where == 0))
		{
			i = (i + 1) % 3;
		}
		x = team[i].x + 4;
		y = team[i].y;
		if (team[i].where % 5 == 0 && team[i].where <= 20)
			x = x + 2;
		else if (team[i].where == 29 || team[i].where == 39)
			x = x + 2;
		gotoxy(x, y);
		printf("◁");
		key = _getch();
		move_cursor(key, &i, 2);//선택할 i번째 말을 고른다
		while (team[i].where == 22 || (team[i].Howmany >= 1 && team[i].where == 0))
		{
			move_cursor(key, &i, 2); //업은 말 은 넘어가 다른 말을 표시하게 한다
		}

		printf("\b\b ");
	} while (key != 32); //스페이스바를 눌러 선택


	return i;
}
//말들의 정보 초기화
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
			team[k][i].x = 65;
			team[k][i].y = 35;//좌표
			team[k][i].Teamcolor = 0;//팀 색상
			team[k][i].Howmany = -1;//업은 말갯수
			team[k][i].where = 0;
			for (j = 0; j < 10; j++)
				team[k][i].cango[j] = 0;//갈수있는 곳의 위치 표시
		}
	}
	return team;
}
/*턴을 진행할 팀번호, 나온 윷의 값이 저장된 배열 ,전체 말들의 정보를 받는다
yut는 처음엔 윷의 값을 저장 하지만 함수 중간에 */
void move(const int t, int *yut, mal** team)
{
	listNode* headnode = NULL;
	int num = 0;
	int i = 0, j = 0, k = 0;
	//int temp[3] = { 0,0,0 }; //말들의 현재 위치가 저장된 변수
	int max = 0;//윷의갯수
	int x = 0, y = 0;
	int plus = 0; //윷을 한번더 던졋을때 나온값 저장할 변수
	int check = 0; //
	char key;
	initialize(&headnode);

	for (k = 0; k < 10; k++)
		insertLast(headnode, yut[k]); //나온 윷의 값 리스트에 저장
	if (headnode->rlink->key == -1)
		for (i = 0; i < 3; i++)
			if (team[t][i].where == 0 || team[t][i].where == 22)
				check++;
	if (check == 3)//움직일수있는 말이 없다면
	{
		setcolor(11, 0);
		gotoxy(6, 41);
		printf("빽도로 이동할 수 있는 말이 없습니다. 상대의 차례로 넘어갑니다.                  ");
		unsetcolor();
		freeList(headnode);
		return;
	}
	i = 0;
	check = 0;
	do {
		num = Select(team[t]);
		max = canmove(team[t][num].cango, headnode, yut);
		if (max == -1)
		{
			setcolor(11, 0);
			gotoxy(6, 41);
			printf("이동할 수 있는 곳이 없습니다. 다른말을 선택 하십시오.                  ");
			unsetcolor();
		}
	} while (max == -1); //이동할수 있는 칸이 없다면 다시 선택한다.
	do {

		team_mal(team);

		x = basic[team[t][num].cango[i]].x;
		y = basic[team[t][num].cango[i]].y;
		gotoxy(x + 4, y);
		if (team[t][num].cango[i] % 5 == 0 && team[t][num].cango[i] <= 20) //칸이 큰곳은 더 옆에 커서를 움직인다
			gotoxy(x + 6, y);
		else if (team[t][num].cango[i] == 29 || team[t][num].cango[i] == 39)
			gotoxy(x + 6, y);
		printf("◁");
		key = cmp_cat_carry(team, x, y, num, t);
		//esc 입력시 말을 다시 선택한다.
		if (key == 27)
		{
			printf("\b\b ");
			print_all_mal(team);
			do {
				num = Select(team[t]);
				/*cango가 계산 되어있다면 canmove()를 호출 하지않는다.*/

				if (team[t][num].cango[0] == team[t][num].where)
					max = canmove(team[t][num].cango, headnode, yut);
			} while (max == -1); //이동할수 있는 칸이 없다면 다시 선택한다.


			continue;
		}


		if (key == 32) { /*스페이스바 입력*/
			gotoxy(x + 4, y);
			if (team[t][num].cango[i] % 5 == 0 && team[t][num].cango[i] <= 20) //칸이 큰곳은 더 옆에 커서를 움직인다
				gotoxy(x + 6, y);
			else if (team[t][num].cango[i] == 29 || team[t][num].cango[i] == 39)
				gotoxy(x + 6, y);
			printf("\b  ");//커서지움
			if (team[t][num].Howmany == -1)
				team[t][num].Howmany = 0;
			if (team[t][num].where != 0) //처음이 아니라면
			{
				gotoxy(team[t][num].x, team[t][num].y);
				printf("  ");//이전위치의 말을 지움
			}
			gotoxy(basic[team[t][num].cango[i]].x, basic[team[t][num].cango[i]].y);//선택한 곳으로 이동
			team[t][num].x = basic[team[t][num].cango[i]].x;//x,y 좌표 저장
			team[t][num].y = basic[team[t][num].cango[i]].y;


			team[t][num].where = team[t][num].cango[i];//이동한 곳으로 현재위치 저장

			carry(team[t], num); // 잡거나
			cat(team, num, t); // 업는다

							   //업은말이 골인했다면
			if (team[t][num].where == 22 && team[t][num].Howmany >= 1) {
				if (team[t][(num + 1) % 3].Howmany == team[t][num].Howmany) //Howmany가 같은 말을 찾는다
					team[t][(num + 1) % 3].where = 22;
				if (team[t][(num + 2) % 3].Howmany == team[t][num].Howmany)
					team[t][(num + 2) % 3].where = 22; //0인 where값을 22로 만든다.
				setcolor(11, 0);
				gotoxy(6, 41);
				printf("말이 골인지점에 들어왔습니다. +%d 점                           ", team[t][num].Howmany);
				unsetcolor();

			}
			else if (team[t][num].where == 22 && team[t][num].Howmany == 0)
			{
				setcolor(11, 0);
				gotoxy(6, 41);
				printf("말이 골인지점에 들어왔습니다. +1 점                           ");
				unsetcolor();
			}

			/*출력*/
			print_all_mal(team);
			team_mal(team);


			deleteMiddle(headnode, yut[i]); //남아있는 윷의 값들 중에서 이동한 윷의 값 삭제 
			if (r == 1)//전역변수 r
			{
				setcolor(13, 0);
				gotoxy(6, 41);
				printf("상대팀의 말을 잡았습니다. 잡힌 말은 말판으로 이동합니다.    "); //explain 함수 사용하도록 수정해야함
				gotoxy(6, 43);
				printf("스페이스바를 눌러 윷을 한번 더 던지십시오.                 ");
				key = _getch();
				do {
					YUT = random();
				} while (YUT == 6);
				sound_yut();
				insertLast(headnode, YUT);
				gotoxy(6, 41);
				explain(YUT);
				gotoxy(6, 43);
				printf("                                                       ");
				while (YUT == 4 || YUT == 5)
				{
					switch (YUT) {
					case 4:
						gotoxy(6, 41);
						setcolor(11, 0);
						explain(YUT);
						unsetcolor();
						break;
					case 5:
						gotoxy(6, 41);
						setcolor(11, 0);
						explain(YUT);
						unsetcolor();
						break;
					}
					while (getch() != 32);
					do {
						YUT = random();
					} while (YUT == 6);
					sound_yut();
					insertLast(headnode, YUT);
				}
				gotoxy(6, 41);
				setcolor(13, 0);
				explain(YUT);
				unsetcolor();
				
				
				
			}
			if (r == 0)
			{
				setcolor(12, 0);
				gotoxy(6, 41);
				printf("말을 업었습니다. 지금부터 말을 %d개씩 이동합니다.            ", team[t][num].Howmany);
				unsetcolor();
			}

			for (j = 0; j < 3; j++)
				for (k = 0; k < 10; k++)
					team[t][j].cango[k] = team[t][j].where;//cango 초기화


			if (team[t][0].where == 22 && team[t][1].where == 22 && team[t][2].where == 22) //모든말이 골인 했다면
			{
				num = 3;
				break;
			}


			if (team[t][num].where == 22 && headnode->rlink != headnode)  //말이 골인하면 다른말 선택
				do {
					num = Select(team[t]);
					if (num == 3)
						break;
					if (headnode->rlink->key == -1&&headnode->rlink->rlink!=headnode) //백도가 남은경우
						for (k = 0; k < 3; k++)
							if (team[t][k].where == 0 || team[t][k].where == 22)
							{
								check++;
							}
					if (check == 3) //이동할수있는 말이 없다면 백도 삭제
					{
						setcolor(11, 0);
						gotoxy(6, 41);
						printf("빽도로 이동할 수 있는 말이 없습니다.                         ");
						unsetcolor();
						deleteMiddle(headnode, -1);
						break;
					}
					i = 0;
					if (team[t][num].cango[0] == team[t][num].where)
						max = canmove(team[t][num].cango, headnode, yut);
					if (max == -1)
					{
						setcolor(11, 0);
						gotoxy(6, 41);
						printf("이동할 수 있는 곳이 없습니다. 다른말을 선택 하십시오.                  ");
						unsetcolor();
					}
						
				} while (max == -1); //이동할수 있는 칸이 없다면 다시 선택한다.
				if (num == 3)
					break;
				i = 0;
				if (team[t][num].cango[0] == team[t][num].where)
					max = canmove(team[t][num].cango, headnode, yut);
				continue;
		}

		gotoxy(x + 4, y); //커서의 위치
		if (team[t][num].cango[i] % 5 == 0 && team[t][num].cango[i] <= 20)
			gotoxy(x + 6, y);
		else if (team[t][num].cango[i] == 29 || team[t][num].cango[i] == 39)
			gotoxy(x + 6, y);
		printf("   ");//커서지움
		move_cursor(key, &i, max); //방향키나 스페이스바 입력
	} while (headnode->rlink != headnode);//이동할 수 없을경우 턴을 종료
										  //cango초기화 추가
	if (num == 3)
		endgame = 1;  //게임 끝
	for (j = 0; j < 3; j++)
		for (i = 0; i < 10; i++)
			team[t][j].cango[i] = team[t][j].where;//cango 초기화
	freeList(headnode);
	setcolor(11, 0);
	gotoxy(6, 41);
	printf("                      %d 팀의 차례!                         ", (t == 1) ? 2 : 1);
	unsetcolor();
	Sleep(1000);
}
int initialize(listNode * *h) {


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
/*윷의 값 저장*/
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
/*리스트에 저장된 윷의 값(key) 삭제*/
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
		if (i < 6)//오른쪽길
		{
			p[i].x = 67;
			if (i == 0)//시작위치 y좌표
			{
				p[i].y = 35;
				continue;
			}
			p[i].y = p[i - 1].y - 6;
		}
		else if (i < 11 && i >= 6)//위쪽길
		{
			p[i].y = 5;
			p[i].x = p[i - 1].x - 12;
			if (i == 8)
				p[i].x--;
		}
		else if (i >= 11 && i < 16) //왼쪽길
		{
			p[i].x = 6;
			p[i].y = p[i - 1].y + 6;
		}
		else//아랫길
		{
			p[i].y = 35;
			p[i].x = p[i - 1].x + 12;
			if (i == 18)
				p[i].x++;
		}
	}
	p[0].x = 65;
	p[0].y = 35;
	p[20].x = 65;
	p[20].y = 35;
	for (i = 21; i <= 26; i++)

	{
		p[i].x = 51;//말이 나갈때의 공간
		p[i].y = 20;
	}
	p[5].x = 65;
	p[5].y = 6;

	p[10].x = 8;
	p[10].y = 6;
	p[15].x = 8;
	p[15].y = 34;
	p[27].y = 10;
	for (i = 28; i <= 31; i++) //y=x 지름길 y좌표 설정 i=27~31
		p[i].y = p[i - 1].y + 5;
	
	for (i; i <= 36; i++)
	{
		p[i].y = 0;//지름길이 끝났을때 원래 길로 
		p[i].x = 0;//가기 위해 남겨둔 배열공간
	}
	for (i; i <= 41; i++) //y=-x지름길 i=37~41
		p[i].y = p[i - 10].y;
	i = 27;
	p[i++].x = 57; //y=x x좌표
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

/*선택 시에 선택 될수 있는 말이나 위치의 갯수(max) ,선택할 말이나 위치의 번호(can),화살표키 값(key)*/
void move_cursor(char key, int* can, const int max)
{
	switch (key)
	{
	case 75://좌
		*can = *can - 1;
		if (*can < 0)
			*can = max;
		break;
	case 77://우
		*can = *can + 1;
		if (*can > max)
			*can = 0;
		break;
	default:
		return;
	}
}
/*basic[cango]에서 cango값을 정한다 */
int canmove(int *go, listNode* h, int* yut)
{
	int i = 0;
	listNode* n = h->rlink;

	while (n != NULL && n != h)
	{
		yut[i] = n->key;//배열의 윷의 값을 리스트의 값으로 최신화 시키고 이후에 리스트에서 삭제 시킬때 사용한다
						//현재위치를 보고 특수한 경우가 있는지 비교한다
		if (go[i] == 5 && n->key != -1) //오른쪽위 칸
		{
			go[i] = 27 + n->key - 1;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 10 && n->key != -1) //왼쪽 위칸
		{
			go[i] = 37 + n->key - 1;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 29 && n->key != -1) //정중앙 칸
		{
			go[i] = 39 + n->key;
			if (go[i] > 42)
				go[i] = 22;
			if (go[i] == 42) //y=-x선에서 나가기 전칸에 갈때
				go[i] = 20;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 27 && n->key == -1)//지름길 처음에서 백도
		{
			go[i] = 5;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 37 && n->key == -1)//지름길 처음에서 백도
		{
			go[i] = 10;
			i++;
			n = n->rlink;
			continue;
		}
		if (go[i] == 0 && n->key == -1) //말이 출발하지 못한 말이고 백도일경우
		{
			n = n->rlink; //이말의 이동가능한 위치에서 백도의 경우를 저장하지 않는다
			continue;
		}
		go[i] += n->key;//윷의 값만큼 진행

		n = n->rlink;

		if (go[i] == 42) //y=-x선에서 나가기 전칸에 갈때
			go[i] = 20;

		if (go[i] > 31 && go[i] < 37) //y=x선 상에서 y=0 선으로 넘어갈때
			go[i] = go[i] - 17;

		if ((go[i] > 20 && go[i] < 27) || go[i]>42)//나갈때
			go[i] = 22;// cango를 22로 저장
		if (go[i] == 0) //백도로 처음위치로 갔을때 마지막 위치로 바꿔준다.
			go[i] = 20;

		i++;


	}
	return i - 1;
}
