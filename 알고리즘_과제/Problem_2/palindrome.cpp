#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

//FILE *in = fopen("palindrome.inp", "r");
//FILE *out = fopen("palindrome.out", "w");
ifstream in("palindrome.inp"); //C++에서의 파일 출력
ofstream out("palindrome.out"); //C++에서의 파일 출력

int MAX(int a, int b) {
	return a > b ? a : b;
}

//1000*1000은 백만개... 할당이 안됨..ㄷㄷ

int main()
{
	int T; //테스트 케이스
	int i, j, k;
	char arr1[1000] = { 0, };
	int **arr2;
	int string_len; //문자의 갯수
	int incorrect; //문자 틀린갯수
	int row, col;

	//fscanf(in, "%d", &T);

	in >> T; //C++에서 파일에서 불러오기

	for (i = 0; i < T; i++) {
		//fscanf(in, "%s", &arr1);
		in >> arr1;

		string_len = 0;
		incorrect = 0;

		//총 문자갯수를 구했음.
		for (j = 0; ; j++) {
			if (arr1[j] == 0)
				break;
			string_len++;
		}
		//현 예제 11개 사이즈

		//2차원배열 동적 할당
		arr2 = new int*[string_len+1];
		for (j = 0; j < string_len + 1; j++) {
			arr2[j] = new int[string_len + 1];
		}

		//동적할당한거 초기화
		for (j = 0; j < string_len +1; j++) {
			for (k = 0; k < string_len + 1; k++) {
				arr2[j][k] = 0;
			}
		}

		row = col = 1;

		for (j = string_len - 1; j >= 0; j--) {
			for (k = 0; k < string_len; k++) {
				if (arr1[j] == arr1[k]) {
					arr2[row][col] = arr2[row - 1][col - 1] + 1;
					col++;
				}
				else {
					arr2[row][col] = MAX(arr2[row - 1][col], arr2[row][col - 1]);
					col++;
				}
			}
			row++;
			col = 1;

		}
		incorrect = string_len - arr2[string_len][string_len];


		//2동적할당 배열 해제 (생성의 역순으로 해제)
		for (j = 0; j < string_len + 1; j++) {
			delete[] arr2[j];
		}
		delete[] arr2;

		//출력조건 및 출력
		if (incorrect >= 3)
			//fprintf(out, "-1\n");
			//C++에서 파일에 쓰기.
			out << "-1" << endl;
		else
			//fprintf(out, "%d\n", incorrect);
			out << incorrect << endl;
	}
}
