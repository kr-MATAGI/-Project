#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX(a,b) (a > b ? a : b)

FILE *in = fopen("stickers.inp", "r");
FILE *out = fopen("stickers.out", "w");

int i, j, k, t;
int arr[2][100001];
int DP[2][100001];

int main()
{
	int T; //테스트 케이스
	int st_num; // 스티커 가로 갯수

	fscanf(in, "%d", &T); //총 횟수 입력

	for (t = 0; t < T; t++) {
		fscanf(in, "%d", &st_num); //가로갯수 입력

								   //스티커 입력
		for (i = 0; i < st_num; i++) {
			fscanf(in, "%d ", &arr[0][i]);
		}
		for (i = 0; i < st_num; i++) {
			fscanf(in, "%d ", &arr[1][i]);
		}

		DP[0][0] = arr[0][0];
		DP[1][0] = arr[1][0];

		for (i = 1; i < st_num; i++) {
			DP[0][i] = MAX(MAX(DP[1][i - 1] + arr[0][i], DP[0][i - 2] + arr[0][i]), DP[1][i - 2] + arr[0][i]);
			DP[1][i] = MAX(MAX(DP[0][i - 1] + arr[1][i], DP[1][i - 2] + arr[1][i]), DP[0][i - 2] + arr[1][i]);
		}

		fprintf(out, "%d\n", MAX(DP[0][st_num - 1], DP[1][st_num - 1]));

		memset(arr, 0, sizeof(arr));
		memset(DP, 0, sizeof(DP));
	}
}
