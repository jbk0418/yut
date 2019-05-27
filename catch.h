#pragma once
#include <stdio.h>
#include<conio.h>
#include<windows.h>
#define X_MAX 55
#define Y_MAX 29

/*윷 모 같은 연속적인 수가 나올때*/
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


typedef struct {
	int x, y;//좌표
	int  Teamcolor;//팀 색상
	int Howmany;//업은 말갯수
	int where;//판위에서의 위치를 표시
	int cango[10];//갈수있는 곳의 위치 표시

}mal;
/*Howmany에는 말판위에 올라가있지 않으면 -1을 올라와있으면 0을 넣어준다.*/

typedef struct {
	int x, y;
}pan;

void gotoxy(int x, int y);
/*헤더파일에 선언*/

char cmp_cat_carry(mal **t, int x, int y, int index,int teamnum);					//비교함수 잡을 경우엔 1을 업는경우엔 2를 아무것도 아니면0을 리턴함
void carry(mal *t, int index);						//말을 업는 함수
void cat(mal **t, int index, int teamnum);							//말을 잡는 함수


/*색결정*/
void setcolor(unsigned short text, unsigned short back);
void unsetcolor();
void color_title(char *t, unsigned short text, unsigned short back);
void color_menu(mal ** c);
void intro_color_set();


void team_mal(mal** t);			//윷판에서 사용하며 남은말들을 출력해준다.


void print_all_mal(mal**t);/*말을 전부 출력하는 함수*/
int visiable(mal *t, int index);			//출력가능한지 판단
void print_mal(mal t);

extern int r;									//잡을지 말지 결정하는 결과를 저장하는 전역변수
