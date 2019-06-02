#include "noriyut.h"

/*color함수들은 color.h나 color.c를 이용하는것을 추천함  */
/*그리고 말의 색깔을 구현하기 위해서는 color.c에 올린 함수를 사용해서 색들을 초기화 해야함*/
/*시작지점 0, 20 골인지점 22*/

r = -1; //잡을지 말지 결정하는 결과를 저장하는 전역변수 초기화 헤더에 extern으로 선언함

/*color_select를 헤더 파일에 추가하고
  intro를 삭제한다.*/
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
	printf("%d 팀 컬러를 선택해 주세요",i+1);

		gotoxy(x, 22);
		printf("△");
		
		key = getch();

		color = (x - 32) / 7 + 10;

		if (key == 72 || key == 77) {			//오른쪽 혹은 위쪽(오른쪽으로 이동)
			gotoxy(x, 22);
			printf("  ");
			x += 7;
			
			if (x == 74) x = 32;
		}
		else if (key == 75 || key == 80) {		//왼쪽 혹은 아래(왼쪽으로 이동
			gotoxy(x, 22);
			printf("  ");
			x -= 7;
			if (x == 25) x = 67;
		}
		else if (key == 32 || key == 13) {		//엔터 혹은 스페이스(결정)
			if (color  == t[!i][0].Teamcolor) {
				gotoxy(35, 32);
				printf("같은색은 선택 할 수 없습니다..\n\n");
			}

			else {
				gotoxy(x, 22);
				printf("  ");
				t[i][0].Teamcolor = color;
				gotoxy(x, 18);
				printf("%d팀", i + 1);
				x = 32;
				i++;
			
			}
		}
	}
}

/*사용 위치 -> 말들의 초기화 가 끝난자리에 사용*/
/*글자색    배경색   ->겹치는 색깔 고르지 못하게 해야됨*/
void color_menu(mal ** c) {

			color_select(c);
		
		/*같은 팀은 같은색깔로*/
		for (int i = 0; i < 2; i++) {
			for (int n = 0; n < 3; n++)
				c[i][n].Teamcolor = c[i][0].Teamcolor;
		}
	
	/*안내가 끝나면 지움*/
	system("cls");
}




/*입력: 유저 정보를 담은 배열, 현재 움직일 수 있는 좌표, 인덱스 번호들
출력 : 키보드 입력을 받아 그대로 리턴함*/
/*잡고 업는 함수를 3개로 나누어 놓은 이유 -> 결정을 할때 바로 잡으면 안되기 때문에
잡거나 업을수 있는 지를 판별할 수 있는 함수를 따로 만들었다.*/
char cmp_cat_carry(mal **t, int x, int y, int index, int teamnum) {

	char key = NULL;
	int n;				//말인덱스
	int d = 0;				//말 수
	r = -1;				//결과를 나타내며 잡거나 업는경우가 없으면 -1업으면 0 잡으면 1을 저장함

						/*반복문을 이용해 잡을 수 있는 말을 찾는다.*/
	for (n = 0; n < 3; n++) {

		/*초기화 되어 있는 변수도 생각할것*/

		if (x == 51 && y == 20) {
			r = -1;
			break;
		}
		/*잡을 수 있으면 X로 표시 */

		/*팀원의 좌표가 같고 같은 인덱스가 아닐때 -> 업는경우*/
		else if (x == t[teamnum][n].x&&y == t[teamnum][n].y&&index != n&&t[teamnum][n].where !=22&&t[teamnum][n].where!=0)	//골인지점이면 업지 않는다.
		{
			/*goto로 해당 좌표로 이동*/
			gotoxy(x, y);

			/*업을 수 있는 말 숫자표기 ex) 숫자! */
			if (t[teamnum][index].Howmany == -1 || t[teamnum][index].Howmany == 0 || t[teamnum][n].Howmany == 0)
				d = 3;
			if ((t[teamnum][index].Howmany == -1 || t[teamnum][index].Howmany == 0) && t[teamnum][n].Howmany == 0)
				d = 2;
		
			setcolor(t[teamnum][index].Teamcolor, 0);

			printf("%d!", d);

			unsetcolor();
			r = 0;//결과 저장
			break;
		}

		/*다른팀의 좌표가 같을때 -> 잡는경우&&t[teamnum][n].cango[9] != 0*/
		else if (x == t[!teamnum][n].x&&y == t[!teamnum][n].y&&t[!teamnum][n].where!=22&&t[!teamnum][n].where != 0) {
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


		if (r == 1 || r == 0) {		//잡거나 업을 수 있던경우에 다르게 출력했기에 원래있던 말을 출력해줌

			print_all_mal(t);			//원래 있던 말을 출력해준다.

			r = -1;					//결과 초기화
		}

	}
	return key;					//입력받은 key값 반환

}




/*Howmany로 판위 에 올려져있는지 판단
Howmnay 초기값 -1
올라가 있으면 같이 있는만큼 ex) 2같이 있으면 2로 저장*/




/*입력: mal 배열, 이동거리, 말번호
이동한후에 사용할것*/
void carry(mal *t, int index) {

	int n, l;
	int d = 0;

	if (r == 0) {//결과가 업는경우일 경우


		for (n = 0; n<3; n++) {

			if (t[n].where == 22) {

			}

			/*좌표가 같고                     번호가 다른경우*/
			else if (t[index].x == t[n].x&&t[index].y == t[n].y&&index != n) {
			

				/*몇개 같이있는지 if문으로 구분해서 저장함 말이 3개 뿐이니 하나가 2이상이면 3이다.*/
				if (t[index].Howmany == -1 || t[index].Howmany == 0 || t[n].Howmany == 0)
					d = 3;
				if ((t[index].Howmany == -1 || t[index].Howmany == 0) && t[n].Howmany == 0)
					d = 2;

				/*엎혀있던 말들도 값을 넣어줌*/
				if (t[index].Howmany > 0) {
					for (int k = 0; k < 3; k++) {
						if (t[k].Howmany == t[index].Howmany)
							t[k].Howmany = d;
					}
				}
				t[index].Howmany = d;
				t[n].Howmany = d;
				
				/*위치 초기화*/
				t[n].x = 64;
				t[n].y = 35;
				t[n].where = 0;
			
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



void cat(mal **t, int index, int teamnum) {
	/*잡힌말 초기화 -> 업은 말도 같이 초기화*/
	/*초기화된 말은 못잡도록 바꿀것*/

	int n, l;
	
	if (r == 1) {		//결과가 잡는 경우일 경우

		for (n = 0; n<3; n++) {
			/*상대팀과 좌표가 같은 경우*/
			if (t[!teamnum][n].where == 22){
			
			}

			else if (t[teamnum][index].x == t[!teamnum][n].x&&t[teamnum][index].y == t[!teamnum][n].y) {
				 
				/*업은말 초기화*/
				if (t[!teamnum][n].Howmany != 0)
				for (l = 0; l < 3; l++) {
					if (t[!teamnum][n].Howmany == t[!teamnum][l].Howmany && n != l) {
						t[!teamnum][l].x = 64;
						t[!teamnum][l].y = 35;
						t[!teamnum][l].Howmany = -1;
						t[!teamnum][l].where = 0;
					}
				}
		
				/*잡힌말 초기화*/
				t[!teamnum][n].x = 64;
				t[!teamnum][n].y = 35;

				t[!teamnum][n].where = 0;
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
 	x1 = 82;
	x2 = 82;
	y1 = 36;
	y2 = 38;

	for (index = 0; index < 3; index++) {

		/*1번팀 gotoxy를 사용해 x79 y36*/
		gotoxy(x1, y1);
		printf("         ");				//이전값 삭제
		gotoxy(x1, y1);
		/*위치가 초기이고 업혀있지 않다면 출력함*/
		if (t[0][index].x == 64 && t[0][index].y == 35 && t[0][index].Howmany == -1&&t[0][index].where ==0) {
			setcolor(t[0][index].Teamcolor, 0);
			printf("●");/*이부분 바꿀것*/
			unsetcolor();

			x1 += 2;
			/*색 초기화*/
		}

		/*2번팀 gotoxy를 사용해 x79 y38*/
		gotoxy(x2, y2);
		printf("         ");				//이전값 삭제
		gotoxy(x2, y2);
		if (t[1][index].x == 64 && t[1][index].y == 35 && t[1][index].Howmany == -1 && t[1][index].where == 0) {

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
	if (t[index].where == 22)
		return 0;
	if (t[index].where == 20)
		return 1;
	if ((t[index].where ==0)||(t[index].x ==51 &&t[index].y ==20)/*53 20이부분에 골인지점*/)
		return 0;
	return 1;
}

void print_mal(mal t) {
	/*출력할 위치로 이동*/

	gotoxy(t.x, t.y);

	/*업은 말의 수에 따라 다르게 출력한다.*/
	if (t.Howmany >= 1) {
		if (t.Teamcolor != 15) {
			setcolor(7, t.Teamcolor);
			printf(" %d", t.Howmany);
			unsetcolor();
		}
		else {			/*하얀색이면 보이지 않기 때문에 검은색 글씨로 바꾸어준다.*/
			setcolor(0, t.Teamcolor);
			printf(" %d", t.Howmany);
			unsetcolor();
		}
	}
	/*업은 말이 없을때*/
	else {
		setcolor(t.Teamcolor, 0);
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

		if (visiable(t[0], i)) {

			print_mal(t[0][i]);
		}

		/*2번팀 말출력*/
		if (visiable(t[1], i)) {

			print_mal(t[1][i]);
		}

	}
	print_score(t);
	//team_mal(t);

}

void print_score(mal**t) {
	int x1 = 83; /*바꿀것*/
	int y1 = 31;
	int x2 = 83;
	int y2 = 33;
	
		for (int k = 0; k < 3; k++) {
			if (t[0][k].where == 22) {
				gotoxy(x1,y1);
				setcolor(t[0][k].Teamcolor, 0);
				printf("●");
				unsetcolor();
				x1 += 2;
			}
			if (t[1][k].where == 22) {
				gotoxy(x2, y2);
				setcolor(t[1][k].Teamcolor, 0);
				printf("●");
				unsetcolor();
				x2 += 2;
			}
		}
}