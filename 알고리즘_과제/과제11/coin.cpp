#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in = fopen("coin.inp", "r");
FILE *out = fopen("coin.out", "w");

int DP[101][101][101];
int result;
int A, B, C;
int lose;

void Check(int A, int B, int C) {
	int i;

	for (i = 1; i <= 3; i++) {
		if (A - i < 0)
			break;
		if (DP[A - i][B][C] == 1) {
			lose++;
			return;
		}
	}

	for (i = 1; i <= 3; i++) {
		if (B - i < 0)
			break;
		if (DP[A][B - i][C] == 1) {
			lose++;
			return;
		}
	}

	for (i = 1; i <= 3; i++) {
		if (C - i < 0)
			break;
		if (DP[A][B][C - i] == 1) {
			lose++;
			return;
		}
	}
}

int main()
{
	int t, i, j, k;
	int T; //테스트 케이스
	lose = 0;
	//0이면 이기고 1이면 진다.
	fscanf(in, "%d", &T);

	//DP만들기

	DP[0][0][1] = 1;
	DP[0][1][0] = 1;
	DP[1][0][0] = 1;

	for (i = 0; i < 101; i++) {
		for (j = 0; j < 101; j++) {
			for (k = 0; k < 101; k++) {
				if (i == 0 && j == 0 && k == 0)
					continue;
				if (i == 0 && j == 0 && k == 1)
					continue;
				if (i == 0 && j == 1 && k == 0)
					continue;
				if (i == 1 && j == 0 && k == 0)
					continue;
				Check(i, j, k);

				if (lose >= 1) {
					DP[i][j][k] = 0;
				}
				if(lose == 0) {
					DP[i][j][k] = 1;
				}
				lose = 0;
			}
		}
	}

	//
	for (t = 0; t < T; t++) {
		fscanf(in, "%d %d %d", &A, &B, &C);

		if (DP[A][B][C] == 0)
			fprintf(out, "(%d %d %d) : 1\n", A, B, C);
		else
			fprintf(out, "(%d %d %d) : -1\n", A, B, C);
	}
}
