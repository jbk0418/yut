#include <stdio.h>




#define _CRT_SECURE_NO_WARNINGS
#define MAX_X 30
#define MAX_Y 30
#define MAX_PS 4											//�� ����
#define MAX_P 2

typedef struct piceses
{
	int X;						//��ġ
	int Y;
	int carry;					//���� ����	
}pic;

typedef struct TEAM
{
	pic p[MAX_PS];
	int color;
	int score;
	int side;					//�� ����
}team;

void catch (team *t, int dice, int k);
void carry(team *t, int dice, int k);

int main() {
	team t[MAX_P];
	t[0].side = 1;
	/*carry �ʱ�ȭ*/
	t[1].side = 2;


	int k = 1;						//�̵��� �� ��ȣ 1����: 1,2,3,4�α��� 2���� 5,6,7,8
	int dice = 3;					//�ֻ���

	catch (t, dice, k);

	return 0;
}

void catch (team *t, int dice, int k) {
	int f, p, carry;


	if (k <= 4 && k > 0) {														//1���� �����϶�

		for (f = 0; f < 4; f++) {
			if (t[0].p[k].X == t[1].p[f].X &&t[0].p[k].Y == t[1].p[f].Y) {		//1������ ���� ��������
																				//�����͵� ���ִ°� �����ؾߵ�
				t[1].p[f].X = -1;												//������ �ǿ��� ������ߵ�
				t[1].p[f].Y = -1;
				break;

			}

		}
	}
	else if (k <= 8) {
		for (f = 0; f < 4; f++) {
			if (t[1].p[k - 4].X == t[0].p[f].X&&t[1].p[k - 4].Y == t[0].p[k - 4].Y) {		//2������ ���� ����� ���

				t[0].p[f].X = -1;
				t[0].p[f].Y = -1;
				break;
			}

		}
	}
	else {
		printf("�߸��� �Է�-> catch�Լ�");
	}
}

void carry(team *t, int dice, int k) {
	int f, p, carry;

	if (k <= 4 && k > 0) {														//1���� �����϶�

		for (f = 0; f < 4; f++) {
			if (t[0].p[k].X == t[0].p[f].X &&t[0].p[k].Y == t[0].p[f].Y) {	//���� ���
			   /*������ ������ ���� ����*/
				t[0].p[k].carry += 1;								//tip ������ �Ѹ��� �ΰ� ������ ���� ���ڷ� ǥ��
				t[0].p[f].X == -1;
				t[0].p[f].Y == -1;
				break;

			}
		}
	}
	else if (k <= 8) {
		for (f = 0; f < 4; f++) {

			if (t[1].p[k - 4].X == t[1].p[f].X&&t[1].p[k - 4].Y == t[1].p[k - 4].Y) {
				t[1].p[k - 4].carry += 1;								//tip ������ �Ѹ��� �ΰ� ������ ���� ���ڷ� ǥ��
				t[1].p[f].X == -1;
				t[1].p[f].Y == -1;
				//������ �����Ұ�
				break;
			}
		}
	}
	else {
		printf("�߸��� �Է�-> catch�Լ�");
	}
}

