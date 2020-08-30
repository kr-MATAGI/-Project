#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in = fopen("coin.inp", "r");
FILE *out = fopen("coin.out", "w");

int i, j, k, t, x, y;
int a, b, c;

//DP[A][B][C]
int DP[101][101][101][3][3];

void insert(int A, int B, int C)
{

	int count = 0;
	int rotate = 0;

	//C
	for (c = 1; c <= 3; c++) {
		if (C - c < 0)
			break;
		else {
			for (x = 0; x < 3; x++) {
				if (x == c - 1)
					continue;
				for (y = 0; y < 3; y++) {
					rotate++;
					if (DP[A][B][C - c][x][y] == 1)
						count++;
					if (rotate == 6) {
						if (count == 0) {
							DP[A][B][C][c - 1][2] = 1;
							rotate = 0;
							count = 0;
						}
						else {
							DP[A][B][C][c - 1][2] = -1;
							rotate = 0;
							count = 0;
						}
					}
				}
			}
		}
	}

	//B
	for (b = 1; b <= 3; b++) {
		if (B - b < 0)
			break;
		else {
			for (x = 0; x < 3; x++) {
				if (x == b - 1)
					continue;
				for (y = 0; y < 3; y++) {
					rotate++;
					if (DP[A][B - b][C][x][y] == 1)
						count++;
					if (rotate == 6) {
						if (count == 0) {
							DP[A][B][C][b - 1][1] = 1;
							rotate = 0;
							count = 0;
						}
						else {
							DP[A][B][C][b - 1][1] = -1;
							rotate = 0;
							count = 0;
						}
					}
				}
			}
		}
	}
	//A
	for (a = 1; a <= 3; a++) {
		if (A - a < 0)
			break;
		else {
			for (x = 0; x < 3; x++) {
				if (x == a - 1)
					continue;
				for (y = 0; y < 3; y++) {
					rotate++;
					if (DP[A - a][B][C][x][y] == 1)
						count++;
					if (rotate == 6) {
						if (count == 0) {
							DP[A][B][C][a - 1][0] = 1;
							rotate = 0;
							count = 0;
						}
						else {
							DP[A][B][C][a - 1][0] = -1;
							rotate = 0;
							count = 0;
						}
					}

				}

			}
		}
	}
}

int main()
{
	int T; // 테스트 케이스
	int A, B, C; //병
	int check;

	//DP[0][0][0] 초기화
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			DP[0][0][0][i][j] = 1;
		}
	}

	for (i = 0; i < 101; i++) {
		for (j = 0; j < 101; j++) {
			for (k = 0; k < 101; k++) {
				if (i == 0 && j == 0 && k == 0)
					continue;
				for (x = 0; x < 3; x++) {
					for (y = 0; y < 3; y++) {
						insert(i, j, k);
					}
				}
			}
		}
	}


	//DP를 먼저 만들어 놓고 시작
	//이전플레이어가 k개를 가지고 가면 현재 플레이어는 k개를 못 가지고 간다


	fscanf(in, "%d", &T);

	for (t = 0; t < T; t++) {
		check = 0;
		fscanf(in, "%d %d %d", &A, &B, &C);


		//엘리스가 이김  > 1 출력
		for (x = 0; x < 3; x++) {
			for (y = 0; y < 3; y++) {
				if (DP[A][B][C][x][y] == 1) {
					check++;
				}
			}
		}
		if (check >= 1)
			fprintf(out, "(%d %d %d) : 1\n", A, B, C);
		else
			fprintf(out, "(%d %d %d) : -1\n", A, B, C);


	}
}