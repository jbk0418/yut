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
	int cango[5];//갈수있는 곳의 위치 표시

}mal;


char cmp_cat_carry(mal *t, pan *p, int index, int* r);					//비교함수 잡을 경우엔 1을 업는경우엔 2를 아무것도 아니면0을 리턴함
void carry(mal *t, pan* p, int index, int r);						//말을 업는 함수
void cat(mal *t, pan* p, int index, int r);							//말을 잡는 함수


int main() {
	
}

/*입력: mal 배열, 판, 말번호 결과를 저장할 변수
  출력 : 키보드 입력을 받아 그대로 리턴함*/
char cmp_cat_carry(mal *t, pan* p, int index, int *r) {
	/*팀구분은 말의 번호로 구분한다*/
	mal *cmp = t;

	char key;
	int i = index / 3;    //index가 0이면 1팀 1이면 2팀
	int n = 0;				//반복문에서 사용될 cmp의 index 전역변수로 
	int d = 0;				//결정을 나타내는 변수
	*r = -1;

	/*반복문을 이용해 잡을 수 있는 말을 찾는다.*/

	while (n < 6, n++) {
		/*잡을 수 있으면 X로 표시 */
		/*초기화 되어 있는 변수도 생각할것*/
			/*cmp의 좌표와 같고 cmp와 t가 같지 않을 경우*/
		if ((t[index].x == cmp[n].x&&t[index].y == cmp[n].y) && index != n) {

			/*잡을때*/
			if (i != n / 3) {
				/*goto로 해당 cmp좌표 이동*/
				gotoxy(cmp[n].x, cmp[n].y);
				/*X로 표기 잡는팀색 표기*/
				printf("X");
				*r = 1;//결과 저장
				break;

			}
			/*업을때*/
			else if (i == n / 3) {

				/*goto로 해당 cmp 좌표로 이동*/
				gotoxy(cmp[n].x, cmp[n].y);
				/*업을 수 있는 말 숫자표기 ex) 숫자!*/
				printf("%d!", t[i].Howmany + cmp[i].Howmany);
				*r = 0;//결과 저장
				break;

			}
		}

	}

	key = getch();			//잡거나 업을지 결정함 결정시 스페이스 입력.

	/*잡거나 업지 않고 끝났을때*/
	if (key != 32) {
		/*색구현*/
		/*goto로 해당 좌표 이동*/
		printf("●");
		/*색 해제*/
	}
	return key;
	/*잡을지 말지 결정한다. 안잡으면 다음턴*/
}
/*입력: mal 배열, 이동거리, 말번호*/
void carry(mal *t, pan* p, int index, int r) {
	/*업으면 키로 결정*/
	mal *cmp = t;
	int l, n = 0;
	if (r == 0) {
		while (n < 6, n++) {
			/*좌표가 같고                                      번호와 팀이 같은경우*/
			if ((t[index].x == cmp[n].x&&t[index].y == cmp[n].y) && (index != n && index / 3 == n / 3)) {
				/*업힌말을 초기화 하고 인덱스를 저장한다.*/

				/*업힌말이 없으면*/
				if (cmp[n].Howmany == 0 && t[index].Howmany == 0) {

					cmp[n].Howmany++;

					t[index].Howmany++;
					/*cmp 위치에는 index에 넣질 않음*/
					t[index].index[0] = n;
					cmp[n].x = 63;
					cmp[n].y = 31;
					/*색함수로 배경을 팀색깔과 같게 한뒤 Howmany 출력*/

				}
				/*업힌말이 있으면*/
				else {
					for (l = 0; l < cmp[n].Howmany;) {
						t[index].index[t[index].Howmany] = cmp[n].index[l];
						t[index].Howmany++;

					}
					cmp[n].x = 63;
					cmp[n].y = 31;
				}

			}


		}
	}

}

void cat(mal *t, pan* p, int index, int r) {
	/*잡힌말 초기화 -> 업은 말도 같이 초기화*/
	/*초기화된 말은 못잡도록 바꿀것*/
	mal *cmp = t;
	int l, k, n = 0;

	if (r == 1) {
		while (n < 6, n++) {
			/*좌표가 같고                                      번호와 팀이 다른경우*/
			if ((t[index].x == cmp[n].x&&t[index].y == cmp[n].y) && (index != n && index / 3 != n / 3)) {/*업은말도 제외 시킴*/
				cmp[n].x = 63;
				cmp[n].y = 31;

				/*업힌말들의 초기화*/
				for (k = 0; k < cmp[n].Howmany; k++) {
					for (l = 0; k < cmp[n].Howmany; l++)
						cmp[cmp[n].index[k]].index[l] = -1;
					cmp[cmp[n].index[k]].Howmany = 0;
					cmp[n].index[k] = -1;
				}

				cmp[n].Howmany = 0;
			}
		}
	}

}