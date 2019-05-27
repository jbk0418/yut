#include "catch.h"

/*color함수들은 color.h나 color.c를 이용하는것을 추천함  */
/*그리고 말의 색깔을 구현하기 위해서는 color.c에 올린 함수를 사용해서 색들을 초기화 해야함*/

 r = -1;									//잡을지 말지 결정하는 결과를 저장하는 전역변수 초기화 헤더에 extern으로 선언함


///////////////////////////////////////////
//             색결정 함수들             //
///////////////////////////////////////////
/*선택된 색깔 출력*/
void setcolor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
/*색깔 초기화*/
void unsetcolor() {
	unsigned short back = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (back << 4));
}

/*문자열 입력받아서 입력받은 색깔로 출력 -> 해보니 잘안됨 사용하지 말것*/
void color_title(char *t, unsigned short text, unsigned short back) {
	setcolor(text, back);
	printf("%s", t);
	unsetcolor();
}
void intro_color_set()
{
	printf("팀 색 결정\n\n");
	printf("0: 검정색, 1: 파랑색, 2: 초록색\n");
	printf("3: 옥색,   4: 빨강색, 5: 자주색\n");
	printf("6: 노란색, 7: 흰색,   8: 회색\n");
	printf("9: 연한 파랑색,  10: 연한 초록색 \n");
	printf("11: 연한 옥색,    12: 연한 빨강색\n");
	printf("13: 연한 자주색,  14: 연한 노란색\n");
	printf("15: 밝은 흰색\n\n");
}
/*사용 위치 -> 말들의 초기화 가 끝난자리에 사용*/
/*글자색    배경색   ->겹치는 색깔 고르지 못하게 해야됨*/
void color_menu(mal ** c) {


	int n, i = 0;
	int cmp = -1;

	/*색깔 안내 */
	intro_color_set();

	for (i = 0; i < 1; i ++) {
		while (1) {
			printf("%d팀 색깔을 입력하세요 : ", i+1);
			scanf("%d", &c[i][0].Teamcolor);

			/*팀색이 같거나 범위를 벗어난 수를 입력했을데 경고문출력 그전 문장을 지움*/
			if(c[i][0].Teamcolor<0||c[i][0].Teamcolor>15||c[i][0].Teamcolor ==c[!i][0].Teamcolor)
				printf("잘 못 입력하셨습니다.\n\n");
			else
				break;
		}
		/*같은 팀은 같은색깔로*/
		for (n = 1;  n<3; n++)
			c[i][n].Teamcolor = c[i][0].Teamcolor;
	}
	/*안내가 끝나면 지움*/
	system("cls");
}


/*gotoxy를 사용하기 위해서는 move.c에서 구현을 하지 않거나 gotoxy 관련함수를 사용할 다른 헤더파일을 만드는것을 추천*/
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

/*사용위치 : move 함수에서 key값을 받는곳에 key = cmp_cat_carry(team, x, y, num, t); 을 복붙해서 사용*/

/*입력: 유저 정보를 담은 배열, 현재 움직일 수 있는 좌표, 인덱스 번호들
  출력 : 키보드 입력을 받아 그대로 리턴함*/
  /*잡고 업는 함수를 3개로 나누어 놓은 이유 -> 결정을 할때 바로 잡으면 안되기 때문에
	잡거나 업을수 있는 지를 판별할 수 있는 함수를 따로 만들었다.*/
char cmp_cat_carry(mal **t, int x, int y, int index,int teamnum) {

	char key;
	int n;				//말인덱스
	int d = 0;				//말 수
	r = -1;				//결과를 나타내며 잡거나 업는경우가 없으면 -1업으면 0 잡으면 1을 저장함

	/*반복문을 이용해 잡을 수 있는 말을 찾는다.*/
	for (n = 0; n < 3; n++) {
		
		/*초기화 되어 있는 변수도 생각할것*/

		if (x == 53 && y == 20)break;

		/*잡을 수 있으면 X로 표시 */
		/*팀원의 좌표가 같고 같은 인덱스가 아닐때 -> 업는경우*/
		else if(x == t[teamnum][n].x&&y == t[teamnum][n].y&&index != n)
		{
			/*goto로 해당 좌표로 이동*/
			gotoxy(x, y);

			/*업을 수 있는 말 숫자표기 ex) 숫자! */
			if (t[teamnum][index].Howmany == -1 || t[teamnum][n].Howmany == -1) 
				d = 3;
			
			if (t[teamnum][index].Howmany == -1 && t[teamnum][n].Howmany == -1) 
				d = 2;

			setcolor(t[teamnum][index].Teamcolor, 0);

			printf("%d!",d );

			unsetcolor();
			r = 0;//결과 저장
			break;
		}

		/*다른팀의 좌표가 같을때 -> 잡는경우*/
		else if (x == t[!teamnum][n].x&&y == t[!teamnum][n].y) {
			/*goto로 해당 좌표 이동*/
			gotoxy(x, y);
			/*X로 표기 잡는팀색 표기*/
			printf("X");
			r = 1;//결과 저장
			break;

		}

	}


	/*키입력 처리*/

	key = getch();		//잡거나 업을지 결정함 결정시 스페이스 입력.

	/*잡거나 업지 않고 끝났을때 다시 원래의 문자를 출력해준다.*/
	if (key != 32) {

		
		if (r == 1||r==0) {		//잡거나 업을 수 있던경우에 다르게 출력했기에 원래있던 말을 출력해줌

			print_all_mal(t);			//원래 있던 말을 출력해준다.

			r = -1;					//결과 초기화
		}

	}
	return key;					//입력받은 key값 반환

}




/*Howmany로 판위 에 올려져있는지 판단
  Howmnay 초기값 -1
  올라가 있으면 같이 있는만큼 ex) 2같이 있으면 2로 저장*/



/*사용위치 키값이 스페이스(32)가 들어왔을 경우 사용
  move.c에서 move함수에서 스페이스 입력을 판단하는 if문안에 쓰고 x,y 좌표저장이라고 주석이 달린 아래에 구현
  carry(team[t], num);				//잡거나
  cat(team, num, t);					//업는다.
 위에 있는거 복붙하고 지울것*/

/*입력: mal 배열, 이동거리, 말번호
  이동한후에 사용할것*/
void carry(mal *t, int index) {

	int n,l;
	int d = 0;

	if (r == 0) {//결과가 업는경우일 경우


		for(n=0;n<3;n++) {
			/*좌표가 같고                     번호가 다른경우*/
			if (t[index].x == t[n].x&&t[index].y == t[n].y&&index != n) {

				/*몇개 같이있는지 if문으로 구분해서 저장함 말이 3개 뿐이니 하나가 2이상이면 3이다.*/
				if (t[n].Howmany == -1 || t[index].Howmany == -1)d = 3;

				/*둘다 업은게 없으면 2로함*/
				if (t[n].Howmany == -1 && t[index].Howmany == -1)d=2;

				  t[index].Howmany = d;
				  t[n].Howmany=d;

				/*위치 초기화*/
				t[n].x = 66;
				t[n].y = 35;
				
				/*cango 초기화*/
				for (l = 0; l < 10; l++)
					t[n].cango[l] = 0;

				/*말 출력 이후 */
				gotoxy(t[index].x, t[index].y);
				/*숫자 출력*/
				setcolor(7, t[index].Teamcolor);
				printf("%d", t[index].Howmany);
				unsetcolor();

			}

		}


	}
}



void cat(mal **t, int index,int teamnum) {
	/*잡힌말 초기화 -> 업은 말도 같이 초기화*/
	/*초기화된 말은 못잡도록 바꿀것*/

	int n,l;

	if (r == 1) {		//결과가 잡는 경우일 경우
		
		for(n=0;n<3;n++) {
			/*상대팀과 좌표가 같은 경우*/
			
			if (t[teamnum][index].x == t[!teamnum][n].x&&t[teamnum][index].y == t[!teamnum][n].y) {

				/*업은말 초기화*/
				for (l = 0; l < 3; l++) {
					if (t[!teamnum][n].Howmany == t[!teamnum][l].Howmany && n != l)
						t[!teamnum][l].Howmany = -1;
				}
				printf("초깃");
				/*잡힌말 초기화*/
				t[!teamnum][n].x = 66;
				t[!teamnum][n].y = 35;

				t[!teamnum][n].Howmany = -1;
			

				/*cango 초기화*/
				for (l = 0; l < 10; l++)
					t[!teamnum][n].cango[l] = 0;
				
				gotoxy(t[teamnum][index].x, t[teamnum][index].y);
				/*업은 말이 없으면●을 출력하고 아니면 숫자출력*/
				if (t[teamnum][index].Howmany == 0)printf("●");

				else {/*글씨의 색깔은 배경색과 다르게 나중에 변경할것*/
					setcolor(7, t[teamnum][index].Teamcolor);
					printf("%d", t[teamnum][index].Howmany);
					unsetcolor();
				}

			}
		}
	}
}

/*사용위치 처음 말이 전부 초기화 됬을때 사용함
  그리고 move함수 내에서는 말의 이동이 결정 된부분들에 사용하면됨*/

/*남은 말 출력   윷판에서 사용하는 함수*/
void team_mal(mal **t) {
	int index = 0;
	int x1, x2, y1, y2;
	x1 = 79;
	x2 = 79;
	y1 = 36;
	y2 = 38;
	
	for (index = 0; index < 3; index++) {
		
		/*1번팀 gotoxy를 사용해 x79 y36*/
		gotoxy(x1, y1);
		printf("           ");				//이전값 삭제
		gotoxy(x1, y1);
		/*위치가 초기이고 업혀있지 않다면 출력함*/
		if (t[0][index].x == 66 && t[0][index].y == 35 && t[0][index].Howmany == -1) {
			setcolor(t[0][index].Teamcolor, 0);
			printf("●");/*이부분 바꿀것*/
			unsetcolor();
			
			x1 += 2;
			/*색 초기화*/
		}

		/*2번팀 gotoxy를 사용해 x79 y38*/
		gotoxy(x2, y2);
		printf("           ");				//이전값 삭제
		gotoxy(x2, y2);
		if (t[1][index].x == 66 && t[1][index].y == 35 && t[1][index].Howmany == -1) {

			/*색 함수*/
			setcolor(t[1][index].Teamcolor, 0);
			printf("●");
			unsetcolor();

			x2 += 2;
			/*색 초기화*/


		}
	}
}

/*말을 위치를 확인해서 말판위에 나타낼지 말지 결정함*/
int visiable(mal *t, int index) {
	if ((t[index].x == 66 && t[index].y == 35)/*이부분에 골인지점*/)
		return 0;
	return 1;
}

void print_mal(mal t) {
	/*출력할 위치로 이동*/
	
	gotoxy(t.x, t.y);

	/*업은 말의 수에 따라 다르게 출력한다.*/
	if (t.Howmany >= 1) {
		setcolor(7, t.Teamcolor);
		printf(" %d", t.Howmany);
		unsetcolor();
	}
	/*업은 말이 없을때*/
	else {
		setcolor(t.Teamcolor,0);
		printf("●");
		unsetcolor();
	}
}

/*사용위치*/

/*현재 말판위에 있는 말들을 출력함*/
void print_all_mal(mal**t) {
	int i;
	
	for (i = 0; i < 3; i++) {

		/*1번팀 말 출력*/
	
		if (visiable(t[0],i)) {
			
			print_mal(t[0][i]);
		}

		/*2번팀 말출력*/
		if (visiable(t[1],i)) {

			print_mal(t[1][i]);
		}

	}
	team_mal(t);

}