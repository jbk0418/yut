
/*색 선택을 할경우에 동일한 색상을 선택할 수 있으면 안됨 -> 구현 필요*/
/*글자색 바꾸어 출력-> 끝나면 초기화(15,7) 두번 선언함 9~ 15*/ /*-> 이동시 어떻게 구현?*/
/*문자열을 입력받아 출력후 함수가 끝나게 된다면 다시 초기화*/ /*이동시 편함*/
#include <stdio.h>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	int x, y;//좌표
	int  Teamcolor;//팀 색상
	int Howmany;//업은 말갯수
	int where;//판위에서의 위치를 표시
	int cango[5];//갈수있는 곳의 위치 표시

}mal;


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

/*글자색    배경색   ->겹치는 색깔 고르지 못하게 해야됨*/
void color_menu(mal * c) {

	c->Teamcolor = 0;
	int n, i = 0;
	int cmp = -1;

	/*색깔 안내 필요*/
	intro_color_set();
	for (i = 0; i <= 3; i += 3) {
		while (1) {
			printf("%d팀 색깔을 입력하세요 : ", i / 3 + 1);
			scanf("%d", &c[i].Teamcolor);

			/*팀색이 같거나 범위를 벗어난 수를 입력했을데 경고문출력 그전 문장을 지움*/
			if (c[i].Teamcolor < 0 || c[i].Teamcolor>15 || c[i].Teamcolor == cmp)
				printf("잘 못 입력하셨습니다.\n\n");
			else
				break;
		}
		/*같은 팀은 같은색깔로*/
		for (n = i; i / 3 == n / 3; n++)
			c[n].Teamcolor = c[i].Teamcolor;
		cmp = c[i].Teamcolor;
	}
	/*안내가 끝나면 지움*/
	system("cls");
}



/*선택된 색깔 출력*/
void setcolor(unsigned short text, unsigned short back)			
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
/*색깔 초기화*/
void unsetcolor() {
	unsigned short back=0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (back << 4));
}

/*문자열 입력받아서 입력받은 색깔로 출력 */
void color_title(char *t, unsigned short text, unsigned short back) {
	setcolor(text, back);
	printf("%s", t);
	unsetcolor();
}
