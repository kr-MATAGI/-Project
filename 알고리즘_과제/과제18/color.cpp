#include <cstdio>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <cstring>
using namespace std;

FILE *in = fopen("color.inp", "r");
FILE *out = fopen("color.out", "w");

const int N = 5005;
const int K = 30;
char a[N], b[N];
int leftA[N][K], leftB[N][K];
int Aline[K], Bline[K];
int lena, lenb;

void ready();
int print();

int dp[N][N];

int main() {
	int t;
	fscanf(in, "%d", &t);
	while (t--) {
		fscanf(in, "%s%s", a + 1, b + 1);
		lena = strlen(a + 1), lenb = strlen(b + 1);
		ready();
		fprintf(out, "%d\n", print());
	}
	return 0;
}

void ready() {
	for (int i = 0; i < K; ++i)
		Aline[i] = Bline[i] = 0;

	for (int i = 1; i <= lena; ++i) {
		Aline[a[i] - 'A']++;
		for (int j = 0; j < 26; ++j) {
			int add = (a[i] - 'A') == j ? 1 : 0;
			leftA[i][j] = leftA[i - 1][j] + add;
		}
	}
	for (int i = 1; i <= lenb; ++i) {
		Bline[b[i] - 'A']++;
		for (int j = 0; j < 26; ++j) {
			int add = (b[i] - 'A') == j ? 1 : 0;
			leftB[i][j] = leftB[i - 1][j] + add;
		}
	}
}

int print() {
	for (int j = 1; j <= lenb; ++j) {
		dp[0][j] = dp[0][j - 1];
		if (leftB[j][b[j] - 'A'] == 1) {
			dp[0][j] -= j;
		}
		if (leftB[j][b[j] - 'A'] == (Bline[b[j] - 'A'] + Aline[b[j] - 'A'])) {
			dp[0][j] += j;
		}
	}

	for (int i = 1; i <= lena; ++i) {
		dp[i][0] = dp[i - 1][0];
		if (leftA[i][a[i] - 'A'] == 1) {
			dp[i][0] -= i;
		}
		if (leftA[i][a[i] - 'A'] == (Aline[a[i] - 'A'] + Bline[a[i] - 'A'])) {
			dp[i][0] += i;
		}
	}

	for (int i = 1; i <= lena; ++i) {
		for (int j = 1; j <= lenb; ++j) {
			int color[] = { a[i] - 'A', b[j] - 'A' };
			int t[] = { dp[i - 1][j], dp[i][j - 1] };
			if (leftA[i][color[0]] == 1 && leftB[j][color[0]] == 0) {
				t[0] -= (i + j);
			}
			if (leftA[i][color[0]] + leftB[j][color[0]] == Aline[color[0]] + Bline[color[0]]) {
				t[0] += (i + j);
			}
			if (leftB[j][color[1]] == 1 && leftA[i][color[1]] == 0) {
				t[1] -= (i + j);
			}
			if (leftB[j][color[1]] + leftA[i][color[1]] == Bline[color[1]] + Aline[color[1]]) {
				t[1] += (j + i);
			}
			dp[i][j] = min(t[0], t[1]);
		}
	}
	return dp[lena][lenb];
}