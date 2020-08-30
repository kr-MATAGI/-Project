#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in = fopen("card.inp", "r");
FILE *out = fopen("card.out", "w");

int DP[1001][1001][2];
int arr[1001];

int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a > b ? b : a;
}

int sovle(int L, int R, int turn) {
	if (L > R) 
		return 0;
	if (DP[L][R][turn] != -1)
		return DP[L][R][turn];
	DP[L][R][turn] = 0;
	if (turn == 0) { //¿¤¸®½º
		DP[L][R][turn] = max(arr[L] + sovle(L + 1, R, 1), arr[R] + sovle(L, R - 1, 1));
	}
	else { //ÄÄ
		DP[L][R][turn] = min(sovle(L + 1, R, 0), sovle(L, R - 1, 0));
	}
	return DP[L][R][turn];
}


int main() {
	int t;
	int i, j, k;
	int n;
	fscanf(in,"%d", &t);
	for(i = 0; i < t ; i++) {
		memset(DP, -1, sizeof(DP));
		memset(arr, 0, sizeof(arr));
		fscanf(in,"%d", &n);
		for (int i = 0; i < n; i++) {
			fscanf(in, "%d", &arr[i]);
		}
		fprintf(out, "%d\n", sovle(0, n - 1, 0));
	}
}