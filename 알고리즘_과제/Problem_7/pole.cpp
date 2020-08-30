#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in = fopen("pole.inp", "r");
FILE *out = fopen("pole.out", "w");

long long dp[21][21][21];

int main()
{
	int T; //테스트 케이스
	int i, j, k;
	int n, l, r;

	fscanf(in, "%d", &T);

	dp[1][1][1] = 1;

	for (i = 1; i < 21; i++) {
		for (j = 1; j < 21; j++) {
			for (k = 1; k < 21; k++) {
				if (i == 1 && j == 1 && k == 1)
					break;
				if (i < j || i < k)
					break;
				dp[i][j][k] = dp[i - 1][j - 1][k] + dp[i - 1][j][k] * (i - 2) + dp[i - 1][j][k - 1];
			}
		}
	}

	for (i = 0; i < T; i++) {
		fscanf(in, "%d %d %d", &n, &l, &r);

		fprintf(out, "%lld\n", dp[n][l][r]);
	}

}