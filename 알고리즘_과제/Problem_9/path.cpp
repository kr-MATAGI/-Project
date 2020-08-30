#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *in = fopen("path.inp", "r");
FILE *out = fopen("path.out", "w");

int floyd[50][50]; //�÷��̵� ����� �Ұ�.
int copy[50][50];
int P[50][50]; //�ִܰ�θ� �˷��ٰ�.
int v[250];
int v_c;
int f_c;
int len;
int check;
int pri; //0�̸� true 1�̸� fasle
void f_folyd(int start, int end) {
	int i, j;
	if (pri == 1)
		return;
	
	if (P[start][end] == 999) {
		if (floyd[start][end] == 999) {
			pri = 1;
			return;
		}
		v[v_c] = end;
		v_c++;
		len = len + floyd[start][end];
		return;
	}

	else if (P[start][end] != 999) {
		if (P[start][end] == check) {
			pri = 1;
			return;
		}
		f_folyd(start, P[start][end]);
		f_folyd(P[start][end], end);
	}
}


int main()
{
	int n; //������ ���� max 50 0����
	int m; //�� ������ �� max 500
	int s, t, w; //i, j, ����ġ ..m���� ��
	//����
	int S, V, T; //��� ����, ������, ������ ���� ...-1 -1 -1 ���Ë�����
	int i, j, k, x;
	v_c = 0;
	f_c = 0;
	//floyd�� arr_n�� ��� 999�� �ʱ�ȭ
	for (k = 0; k < 50; k++) {
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				floyd[i][j] = 999;
				P[i][j] = 999;
				copy[i][j] = 999;
			}
		}
	}

	fscanf(in, "%d %d", &n, &m);

	for (i = 0; i < m; i++) {
		fscanf(in, "%d %d %d", &s, &t, &w);
		floyd[s][t] = w;
		copy[s][t] = w;
	}//����ġ �Է�

	//�ִܰŸ� ���
	while (1) {
		pri = 0;
		len = 0;
		fscanf(in, "%d %d %d", &S, &V, &T);

		if (S == -1 && V == -1 && T == -1)
			break;

		//floyd �˰���
		//����� ~ ������
		for (k = 0; k < n; k++) {
			//�������� ������ ��ŵ.
			if (k == T)
				continue;
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					if (i == j) {
						floyd[i][j] = 0;
						continue;
					}
					if (floyd[i][k] + floyd[k][j] < floyd[i][j]) {
						P[i][j] = k;
						floyd[i][j] = floyd[i][k] + floyd[k][j];
					}
				}
			}
		}

		v[v_c] = S;
		v_c++;
		check = T;
		f_folyd(S, V);
		
		//floyd�� arr_n�� ��� 999�� �ʱ�ȭ
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				floyd[i][j] = 999;
				P[i][j] = 999;
			}
		}

		//floyd����ġ �ٽ�����
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				floyd[i][j] = copy[i][j];
			}
		}

		//������ ~ ������
		for (k = 0; k < n; k++) {
			//������� ������ ��ŵ.
			if (k == S)
				continue;
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					if (i == j) {
						floyd[i][j] = 0;
						continue;
					}
					if (floyd[i][k] + floyd[k][j] < floyd[i][j]) {
						P[i][j] = k;
						floyd[i][j] = floyd[i][k] + floyd[k][j];
					}
				}
			}
		}
		////��º���
		//for (i = 0; i < n; i++) {
		//	for (j = 0; j < n; j++) {
		//		printf("%3d ", floyd[i][j]);
		//	}
		//	printf("\n");
		//}
		//printf("\n");
		//for (i = 0; i < n; i++) {
		//	for (j = 0; j < n; j++) {
		//		printf("%3d ", P[i][j]);
		//	}
		//	printf("\n");
		//}

		check = S;
		f_folyd(V, T);

		memset(floyd, 0, sizeof(floyd));
		memset(P, 0, sizeof(P));


		//�迭���
		if (pri == 0) {
			for (i = 0; i < v_c; i++) {
				fprintf(out, "%d ", v[i]);
			}
			//�������
			fprintf(out, "(%d)\n", len);
		}
		else if(pri == 1) //-1������� �߰� ��ο� S�� T�� ������ -1, ��ΰ� ������ 999
			fprintf(out, "%d %d %d (-1)\n", S, V, T);

		//�迭 �ʱ�ȭ
		for (i = 0; i < v_c; i++) {
			v[i] = 0;
		}
		v_c = 0;

		//floyd�� arr_n�� ��� 999�� �ʱ�ȭ
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				floyd[i][j] = 999;
				P[i][j] = 999;
			}
		}
		//floyd����ġ �ٽ�����
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				floyd[i][j] = copy[i][j];
			}
		}
	}

}
