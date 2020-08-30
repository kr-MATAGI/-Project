#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory.h>
#define MIN(a,b) (a>b ? b:a)
#define MAX 18181818181818

using namespace std;

FILE *in = fopen("bin.inp", "r");
FILE *out = fopen("bin.out", "w");


int N, M; //N -> 집의수
		  //M -> 쓰레기통의수

int X[100000]; //X좌표
int DP[505][505];
int dist[505][505];

int ABS(int number)
{
	if (number < 0)
		return number*(-1);
	else
		return number;
}

void dist_cal()
{
	int mid;
	for (int i = 1; i <= N; i++) {
		for (int j = i; j <= N; j++) {
			mid = (j - i) / 2;
			dist[i][j] = dist[i][j - 1] + X[j] - X[i + mid];
		}
	}
}

void DP_cal()
{
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			for (int k = 1; k <= i; k++) {
				DP[i][j] = MIN(DP[i][j], DP[i - k][j - 1] + dist[i - k + 1][i]);
			}
		}
	}
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Sort(int start, int end) {

	int i, j;
	int temp;
	int pivot = X[start];
	if (start < end) {
		i = start;
		j = end + 1;

		while (i <= j) {
			do
				i++;
			while (X[i] < pivot);
			do
				j--;
			while (X[j] > pivot);
			if (i < j) {
				swap(&X[i], &X[j]);
			}
			else
				break;
		}

		swap(&X[j], &X[start]);
		Sort(start, j - 1);
		Sort(start + 1, end);
	}
}

int main()
{
	int T;


	fscanf(in, "%d", &T);

	for (int t = 0; t < T; t++) {
		for (int i = 0; i < 100000; i++) { //초기화
			X[i] = 0;
		}
		for (int i = 1; i < 505; i++) { //초기화
			for (int j = 0; j < 505; j++) {
				DP[i][j] = MAX;
				dist[i][j] = 0;
			}
		}
		for (int i = 0; i <= M; i++) //초기화
			DP[0][i] = 0;


		fscanf(in, "%d %d", &N, &M);

		for (int i = 1; i <= N; i++) { //집 좌표 입력
			fscanf(in, "%d", &X[i]);
		}

		Sort(1,N);

		dist_cal();

		DP_cal();


		fprintf(out, "%d\n", DP[N][M]);
	}

}