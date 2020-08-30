#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in = fopen("bitmap.inp", "r");
FILE *out = fopen("bitmap.out", "w");

char arr[201][201] = { 0, };
int i, j, k;
int list_count;
int ch_count; //띄워쓰기.
int d_count;
int row, col; //행과 열을 입력받음
char Dc; //D에서 입력받도록 하는것.
char BD; //B와 D인지 입력받음
void B_cal(int s_r, int b_r, int s_c, int b_c) {
	int small_row, small_col; //쿼터 계산시 쓰는 행과 열 시작값.
	int big_row, big_col;//쿼터 계산시 쓰는 행과 열 끝값
	int one_count;//1의 갯수 세기
				  //1의 갯수가 1개 라도 있으면 그건 D
	int mid_row, mid_col;
	one_count = 0;
	small_row = s_r;
	big_row = b_r;
	small_col = s_c;
	big_col = b_c;
	mid_row = (big_row + small_row) / 2;
	mid_col = (small_col + big_col) / 2;
	if (small_row > big_row || small_col > big_col)
		return;
	//배열을 돌아서 1의 갯수 검사하기
	for (i = small_row; i <= big_row; i++) {
		for (j = small_col; j <= big_col; j++) {
			if (arr[i][j] == '1') 
				one_count++;//1이 나오면 카온트 추가
		}
	}
	//모두가 1이 입력들어왔을 경우
	if (one_count == (big_col - small_col + 1) * (big_row - small_row + 1)) {
		fprintf(out, "1");
		ch_count++;
		if (ch_count % 50 == 0) {
			fprintf(out, "\n");
		}
	}
	//모두가 0이 입력이 들어왔을경우
	else if (one_count == 0) {
		fprintf(out, "0");
		ch_count++;
		if (ch_count % 50 == 0) {
			fprintf(out, "\n");
		}
	}

	//0과 1 섞여서 들어왔을 경우
	else if (one_count >= 1) {
		fprintf(out, "D");
		ch_count++;
		if (ch_count % 50 == 0) {
			fprintf(out, "\n");
		}

		B_cal(small_row, mid_row, small_col, mid_col);
		B_cal(small_row, mid_row, mid_col + 1, big_col);
		B_cal(mid_row + 1, big_row, small_col, mid_col);
		B_cal(mid_row + 1, big_row, mid_col + 1, big_col);

	}
}

void D_cal(int s_r, int b_r, int s_c, int b_c) 
{
	int small_row, small_col; //쿼터 계산시 쓰는 행과 열 시작값.
	int big_row, big_col;//쿼터 계산시 쓰는 행과 열 끝값
	int mid_row, mid_col;
	
	small_row = s_r;
	big_row = b_r;
	small_col = s_c;
	big_col = b_c;
	mid_row = (big_row + small_row) / 2;
	mid_col = (small_col + big_col) / 2;
	if (small_row > big_row || small_col > big_col) 
		return;
	if (arr[row][col] != 0)
		return;

	//D가 들어온다
	if (Dc == 'D') {
		if (small_row < big_row || small_col < big_col) {
			Dc = fgetc(in);
			if (Dc == '\n')
				Dc = fgetc(in);
			D_cal(small_row, mid_row, small_col, mid_col);
			D_cal(small_row, mid_row, mid_col + 1, big_col);
			D_cal(mid_row + 1, big_row, small_col, mid_col);
			D_cal(mid_row + 1, big_row, mid_col + 1, big_col);
		}
	}

	for (i = small_row; i <= big_row; i++) {
		for (j = small_col; j <= big_col; j++) {
			if (arr[i][j] == 0) {
				arr[i][j] = Dc;
			}
			else
				return;
		}
	}
	Dc = fgetc(in);
	if (Dc == '\n' && arr[row][col] == 0) {
		Dc = fgetc(in);
	}
}

int main()
{
	
	char ch;
	
	
	int area; //칸의 넓이
	while (1)
	{
	
		ch_count = 0;
		
		d_count = 0;
		while (1) {
			BD = fgetc(in);
			if (BD != '\n')
				break;
		}
		if (BD == '#')
			break;
		fscanf(in, "%d %d\n", &row, &col);
		//50개씩 입력받아야됨.
		area = row * col;


		//0로 초기화
		for (i = 0; i < 201; i++) {
			for (j = 0; j < 201; j++) {
				arr[i][j] = 0;
			}
		}

		//B형식으로 시작할때 입력받기
		if (BD == 'B') {
			fprintf(out, "D%4d%4d\n", row, col);
			ch = -1;
			for (i = 1; i <= row; i++) {
				for (j = 1; j <= col; j++) {
					ch = fgetc(in);
					if (ch == 0 || ch == '\n')
						ch = fgetc(in);
					arr[i][j] = ch;

				}
			}

			B_cal(1, row, 1, col);
			if (ch_count % 50 != 0) {
				fprintf(out, "\n");
			}
		}
		//D형식일 때 입력 받기 및 계산
		else if (BD == 'D') {
			fprintf(out, "B%4d%4d\n", row, col);
			Dc = fgetc(in);
			
			//첫글자가 0이면 모두가 0이다
			if (Dc == '0') {
				for (i = 1; i <= row; i++) {
					for (j = 1; j <= col; j++) {
						fprintf(out, "0");
						ch_count++;
						if (ch_count % 50 == 0 && ch_count != (row*col)) {
								fprintf(out, "\n");
						}
					}
				}
				fprintf(out, "\n");
				continue;
			}
			//첫글자가 1이면 모두가 1이다.
			else if (Dc == '1') {
				for (i = 1; i <= row; i++) {
					for (j = 1; j <= col; j++) {
						fprintf(out, "1");
						ch_count++;
						if (ch_count % 50 == 0 && ch_count != (row*col)) {
								fprintf(out, "\n");
						}
					}
				}
					fprintf(out, "\n");
				continue;
			}

				D_cal(1, row, 1, col);

				for (i = 1; i <= row; i++) {
					for (j = 1; j <= col; j++) {
						fprintf(out, "%c", arr[i][j]);
						ch_count++;
						if (ch_count % 50 == 0 && ch_count != (row*col)) {
								fprintf(out, "\n");
						}
					}
				}
				fprintf(out, "\n");
		}
	}
}