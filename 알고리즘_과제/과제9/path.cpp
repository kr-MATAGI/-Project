#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *in = fopen("path.inp", "r");
FILE *out = fopen("path.out", "w");

int floyd[50][50]; //플로이드 계산을 할곳.
int copy[50][50];
int P[50][50]; //최단경로를 알려줄거.
int v[250];
int v_c;
int f_c;
int len;
int check;
int pri; //0이면 true 1이면 fasle
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
	int n; //간선의 개수 max 50 0부터
	int m; //총 정점의 수 max 500
	int s, t, w; //i, j, 가중치 ..m개의 줄
	//빈줄
	int S, V, T; //출발 정점, 경유지, 목적지 정점 ...-1 -1 -1 나올떄까지
	int i, j, k, x;
	v_c = 0;
	f_c = 0;
	//floyd와 arr_n을 모두 999로 초기화
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
	}//가중치 입력

	//최단거리 계산
	while (1) {
		pri = 0;
		len = 0;
		fscanf(in, "%d %d %d", &S, &V, &T);

		if (S == -1 && V == -1 && T == -1)
			break;

		//floyd 알고리즘
		//출발지 ~ 경유지
		for (k = 0; k < n; k++) {
			//도착점이 나오면 스킵.
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
		
		//floyd와 arr_n을 모두 999로 초기화
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				floyd[i][j] = 999;
				P[i][j] = 999;
			}
		}

		//floyd가중치 다시적기
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				floyd[i][j] = copy[i][j];
			}
		}

		//경유지 ~ 도착지
		for (k = 0; k < n; k++) {
			//출발점이 나오면 스킵.
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
		////출력보기
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


		//배열출력
		if (pri == 0) {
			for (i = 0; i < v_c; i++) {
				fprintf(out, "%d ", v[i]);
			}
			//길이출력
			fprintf(out, "(%d)\n", len);
		}
		else if(pri == 1) //-1출력조건 중간 경로에 S나 T가 나오면 -1, 경로가 없으면 999
			fprintf(out, "%d %d %d (-1)\n", S, V, T);

		//배열 초기화
		for (i = 0; i < v_c; i++) {
			v[i] = 0;
		}
		v_c = 0;

		//floyd와 arr_n을 모두 999로 초기화
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				floyd[i][j] = 999;
				P[i][j] = 999;
			}
		}
		//floyd가중치 다시적기
		for (i = 0; i < 50; i++) {
			for (j = 0; j < 50; j++) {
				floyd[i][j] = copy[i][j];
			}
		}
	}

}
