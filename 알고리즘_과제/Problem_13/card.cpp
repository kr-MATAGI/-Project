#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX(a,b) (a > b ? a : b)

FILE *in = fopen("card.inp", "r");
FILE *out = fopen("card.out", "w");

int i, j, k;

int insert[1001]; //카드를 입력받고 저장하는 배열
int DP[3][1001]; //DP 배열

void default_f(int x) {
	DP[0][x] = insert[x];
	DP[1][x] = insert[x];
	DP[2][x] = insert[x];
}

int main() 
{
	int T; //테스트케이스
	int card_count; //카드 갯수
	int check;

	fscanf(in, "%d", &T);

	for (i = 0; i < T; i++) {
		fscanf(in, "%d", &card_count);

		//입력을 받음
		for (j = 0; j < card_count; j++) {
			fscanf(in, "%d ", &insert[j]);
		}

		check = 0;
		for (j = 0; j < card_count; j++) {
			if (j == 0 || j == 1 || j == 2) {
				default_f(j);
				continue;
			}

			DP[0][j] = insert[j] + MAX(MAX(DP[0][j - 2], DP[1][j - 2]), DP[2][j-2]);
			


			DP[1][j] = insert[j] + MAX(MAX(DP[0][j - 3], DP[1][j - 3]), DP[2][j - 3]);

			if (j == 3) {
				DP[2][j] = -9999;
			}
			else {
				DP[2][j] = insert[j] + MAX(MAX(DP[0][j - 4], DP[1][j - 4]), DP[2][j - 4]);
			}

			if (MAX(MAX(DP[0][j - 2], DP[1][j - 2]), DP[2][j - 2]) == DP[0][j - 2] &&
				MAX(MAX(DP[0][j], DP[1][j]), DP[2][j]) == DP[0][j]) {
				DP[0][j] = insert[j] + MAX(DP[1][j - 2], DP[2][j - 2]);
			}

			/*if (j == card_count - 3) {
				if (MAX(MAX(DP[0][j], DP[1][j]), DP[2][j]) == DP[0][j]) {
					check = 1;
					continue;
				}
			}*/
		}

		/*if (check == 1) {
			fprintf(out, "%d\n", MAX(DP[1][card_count - 1], DP[2][card_count - 1]));
		}*/
		
			fprintf(out, "%d\n", MAX(MAX(DP[0][card_count-1], DP[1][card_count - 1]), DP[2][card_count - 1]));
		memset(DP, 0, sizeof(DP));
		memset(insert, 0, sizeof(insert));
	}
}