#include <stdio.h>

FILE *in = fopen("drive.inp", "r");
FILE *out = fopen("drive.out", "w");

int min(int a, int b) {
	return (a > b) ? b : a;
}


int garo[103][103];
int sero[103][103];
                             // 0오른쪽 1 아래
int dp[103][103][206][2]; 



int main() {

	int T, M, N, L, G;
	int i, j, k, rotate;
	bool found;
	int cal
	found = false;
	//
	scanf("%d", &T);
	while (T--) {
		fscanf(in, "%d %d %d %d", &M, &N, &L, &G);
		// get max changes
		rotate = M+N
	/*	if (M == N)
			rotate = M + N - 3;
		else if (M < N)
			rotate = 2 * (M - 1);*/
		// Initialize dist & found
		for (i = 0; i <= M; i++)
			for (j = 0; j <= N; j++)
				for (k = 0; k <= rotate; k++) {
					dist[i][j][k][0] = 999;
					dist[i][j][k][1] = 999;
				}
		for (k = 0; k <= rotate; k++) {
			dist[1][1][k][0] = 0;
			dist[1][1][k][1] = 0;
		}
		
		//수평 수직 입력
		for (i = 1; i <= M; i++)
			for (j = 1; j <= N - 1; j++)
				fscanf(in, "%d", &garo[i][j]);
		for (i = 1; i <= M - 1; i++)
			for (j = 1; j <= N; j++)
				fscanf(in, "%d", &sero[i][j]);
		//회전수가 0
		for (j = 2; j <= N; j++)
			dp[1][j][0][0] = dp[1][j - 1][0][0] + garo[1][j - 1];
		for (i = 2; i <= M; i++)
			dp[i][1][0][1] = dp[i - 1][1][0][1] + sero[i - 1][1];
		//회전수가 1
		for (k = 1; k <= rotate; k++) {
			for (i = 2; i <= M; i++) {
				for (j = 2; j <= N; j++) {
					dp[i][j][k][0] = MIN(dp[i][j - 1][k][0] + garo[i][j - 1], dp[i][j - 1][k - 1][1] + garo[i][j - 1]);

					dp[i][j][k][1] = MIN(dp[i - 1][j][k - 1][0] + sero[i - 1][j], dp[i - 1][j][k][1] + sero[i - 1][j]);
				}
			}

				cal = dp[M][N][ch][0];
				if (dp[M][N][ch][1] < cal)
					cal = dp[M][N][ch][1];
				//
				if (cal <= G) {
					fprintf(out, "%d\n", (M + N - 2) * L + ch);
					found = true;
				}
				found = false;
			if (found == true)
				break;
		}
		if (found != false)
			fprintf(out, "-1\n");
	}
}