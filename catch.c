#include <stdio.h>
#include<conio.h>
#include<windows.h>
#define X_MAX 55
#define Y_MAX 29

/*�� �� ���� �������� ���� ���ö�*/
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


typedef struct {
	int x, y;//��ǥ
	int  Teamcolor;//�� ����
	int Howmany;//���� ������
	int where;//���������� ��ġ�� ǥ��
	int cango[5];//�����ִ� ���� ��ġ ǥ��

}mal;


char cmp_cat_carry(mal *t, pan *p, int index, int* r);					//���Լ� ���� ��쿣 1�� ���°�쿣 2�� �ƹ��͵� �ƴϸ�0�� ������
void carry(mal *t, pan* p, int index, int r);						//���� ���� �Լ�
void cat(mal *t, pan* p, int index, int r);							//���� ��� �Լ�


int main() {
	
}

/*�Է�: mal �迭, ��, ����ȣ ����� ������ ����
  ��� : Ű���� �Է��� �޾� �״�� ������*/
char cmp_cat_carry(mal *t, pan* p, int index, int *r) {
	/*�������� ���� ��ȣ�� �����Ѵ�*/
	mal *cmp = t;

	char key;
	int i = index / 3;    //index�� 0�̸� 1�� 1�̸� 2��
	int n = 0;				//�ݺ������� ���� cmp�� index ���������� 
	int d = 0;				//������ ��Ÿ���� ����
	*r = -1;

	/*�ݺ����� �̿��� ���� �� �ִ� ���� ã�´�.*/

	while (n < 6, n++) {
		/*���� �� ������ X�� ǥ�� */
		/*�ʱ�ȭ �Ǿ� �ִ� ������ �����Ұ�*/
			/*cmp�� ��ǥ�� ���� cmp�� t�� ���� ���� ���*/
		if ((t[index].x == cmp[n].x&&t[index].y == cmp[n].y) && index != n) {

			/*������*/
			if (i != n / 3) {
				/*goto�� �ش� cmp��ǥ �̵�*/
				gotoxy(cmp[n].x, cmp[n].y);
				/*X�� ǥ�� ������� ǥ��*/
				printf("X");
				*r = 1;//��� ����
				break;

			}
			/*������*/
			else if (i == n / 3) {

				/*goto�� �ش� cmp ��ǥ�� �̵�*/
				gotoxy(cmp[n].x, cmp[n].y);
				/*���� �� �ִ� �� ����ǥ�� ex) ����!*/
				printf("%d!", t[i].Howmany + cmp[i].Howmany);
				*r = 0;//��� ����
				break;

			}
		}

	}

	key = getch();			//��ų� ������ ������ ������ �����̽� �Է�.

	/*��ų� ���� �ʰ� ��������*/
	if (key != 32) {
		/*������*/
		/*goto�� �ش� ��ǥ �̵�*/
		printf("��");
		/*�� ����*/
	}
	return key;
	/*������ ���� �����Ѵ�. �������� ������*/
}
/*�Է�: mal �迭, �̵��Ÿ�, ����ȣ*/
void carry(mal *t, pan* p, int index, int r) {
	/*������ Ű�� ����*/
	mal *cmp = t;
	int l, n = 0;
	if (r == 0) {
		while (n < 6, n++) {
			/*��ǥ�� ����                                      ��ȣ�� ���� �������*/
			if ((t[index].x == cmp[n].x&&t[index].y == cmp[n].y) && (index != n && index / 3 == n / 3)) {
				/*�������� �ʱ�ȭ �ϰ� �ε����� �����Ѵ�.*/

				/*�������� ������*/
				if (cmp[n].Howmany == 0 && t[index].Howmany == 0) {

					cmp[n].Howmany++;

					t[index].Howmany++;
					/*cmp ��ġ���� index�� ���� ����*/
					t[index].index[0] = n;
					cmp[n].x = 63;
					cmp[n].y = 31;
					/*���Լ��� ����� ������� ���� �ѵ� Howmany ���*/

				}
				/*�������� ������*/
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
	/*������ �ʱ�ȭ -> ���� ���� ���� �ʱ�ȭ*/
	/*�ʱ�ȭ�� ���� ���⵵�� �ٲܰ�*/
	mal *cmp = t;
	int l, k, n = 0;

	if (r == 1) {
		while (n < 6, n++) {
			/*��ǥ�� ����                                      ��ȣ�� ���� �ٸ����*/
			if ((t[index].x == cmp[n].x&&t[index].y == cmp[n].y) && (index != n && index / 3 != n / 3)) {/*�������� ���� ��Ŵ*/
				cmp[n].x = 63;
				cmp[n].y = 31;

				/*���������� �ʱ�ȭ*/
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