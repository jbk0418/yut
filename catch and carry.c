#include <stdio.h>




#define _CRT_SECURE_NO_WARNINGS
#define MAX_X 30
#define MAX_Y 30
#define MAX_PS 4											//말 개수
#define MAX_P 2

typedef struct piceses
{
	int X;						//위치
	int Y;
	int carry;					//업은 여부	
}pic;

typedef struct TEAM
{
	pic p[MAX_PS];
	int color;
	int score;
	int side;					//팀 구분
}team;

void catch (team *t, int dice, int k);
void carry(team *t, int dice, int k);

int main() {
	team t[MAX_P];
	t[0].side = 1;
	/*carry 초기화*/
	t[1].side = 2;


	int k = 1;						//이동할 말 번호 1번팀: 1,2,3,4로구분 2번팀 5,6,7,8
	int dice = 3;					//주사위

	catch (t, dice, k);

	return 0;
}

void catch (team *t, int dice, int k) {
	int f, p, carry;


	if (k <= 4 && k > 0) {														//1번팀 차례일때

		for (f = 0; f < 4; f++) {
			if (t[0].p[k].X == t[1].p[f].X &&t[0].p[k].Y == t[1].p[f].Y) {		//1번팀의 말이 잡았을경우
																				//업은것도 없애는거 구현해야됨
				t[1].p[f].X = -1;												//잡으면 판에서 사라져야됨
				t[1].p[f].Y = -1;
				break;

			}

		}
	}
	else if (k <= 8) {
		for (f = 0; f < 4; f++) {
			if (t[1].p[k - 4].X == t[0].p[f].X&&t[1].p[k - 4].Y == t[0].p[k - 4].Y) {		//2번팀의 말이 잡았을 경우

				t[0].p[f].X = -1;
				t[0].p[f].Y = -1;
				break;
			}

		}
	}
	else {
		printf("잘못된 입력-> catch함수");
	}
}

void carry(team *t, int dice, int k) {
	int f, p, carry;

	if (k <= 4 && k > 0) {														//1번팀 차례일때

		for (f = 0; f < 4; f++) {
			if (t[0].p[k].X == t[0].p[f].X &&t[0].p[k].Y == t[0].p[f].Y) {	//업은 경우
			   /*업으면 업은말 숫자 저장*/
				t[0].p[k].carry += 1;								//tip 업으면 한말만 두고 나머지 제거 숫자로 표현
				t[0].p[f].X == -1;
				t[0].p[f].Y == -1;
				break;

			}
		}
	}
	else if (k <= 8) {
		for (f = 0; f < 4; f++) {

			if (t[1].p[k - 4].X == t[1].p[f].X&&t[1].p[k - 4].Y == t[1].p[k - 4].Y) {
				t[1].p[k - 4].carry += 1;								//tip 업으면 한말만 두고 나머지 제거 숫자로 표현
				t[1].p[f].X == -1;
				t[1].p[f].Y == -1;
				//업은거 구현할것
				break;
			}
		}
	}
	else {
		printf("잘못된 입력-> catch함수");
	}
}

