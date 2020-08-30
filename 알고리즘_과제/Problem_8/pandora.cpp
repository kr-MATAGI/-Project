#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in = fopen("pandora.inp", "r");
FILE *out = fopen("pandora.out", "w");

char arr[100005];

int main()
{
	//출력은 0 , 1 , 2
	int T; //테스트 케이스
	int t, i, j, k;
	int bang; //1 : 위, 2: 아래, 3: 왼쪽, 4: 오른쪽
	char pre_ch;//이전문자 하나 저장
	int result; //출력할 결과 값
	int x, y; //x단조 y단조
	fscanf(in, "%d", &T);

	for (t = 0; t < T; t++) {

		result = 2;
		bang = 1;
		x = y = 0;
		fscanf(in, "%s", arr);
		pre_ch = arr[0];
		//1 : 위, 2: 아래, 3: 왼쪽, 4: 오른쪽
		for (i = 1; i < strlen(arr); i++) {
			if (arr[i] == 'L') { // L 을 입력받았을 경우
				if (bang == 1) { //위로 향하고 있을때
					bang = 3; //왼쪽으로 회전
					pre_ch = arr[i];
				}
				else if (bang == 2) {//아래를 향할때
					bang = 4; //오른쪽으로 회전
					pre_ch = arr[i];
				}
				else if (bang == 3) {//왼쪽을 향할떄
					bang = 2; //아래로
					pre_ch = arr[i];
				}
				else if (bang == 4) { //오른쪽을 향할때
					bang = 1; //위로
					pre_ch = arr[i];
				}
			}
			//1 : 위, 2: 아래, 3: 왼쪽, 4: 오른쪽
			else if (arr[i] == 'R') { //R을 입력 받았을 경우
				if (bang == 1) { //위로 향하고있을때
					bang = 4; //오른쪽으로 회전
					if (pre_ch == 'R') {
						if (y > 0)
							continue;
						y++;
					}
					pre_ch = arr[i];
				}
				else if (bang == 2) { //방향이 아래쪽
					bang = 3; //왼쪽으로 전진
					if (pre_ch == 'R') {
						if (y > 0)
							continue;
						y++;
						
					}
					pre_ch = arr[i];
				}
				else if (bang == 3) { //방향이 왼쪽을 가리킬떄
					bang = 1; //위로 전환
					if (pre_ch == 'R') {
						if (x> 0)
							continue;
						x++;
					}
						pre_ch = arr[i];
					
				
				}
				else if (bang = 4) { //방향이 오른쪽을 가리킬때
					bang = 2; //아래로 전환
					if (pre_ch == 'R') {
						if (x > 0)
							continue;
						x++;
						pre_ch = arr[i];
					}
					pre_ch = arr[i];
				}

			}
			//처음과 끝이 R일때
			if (i == strlen(arr) - 1) {
				if (arr[i] == 'R' && arr[0] == 'R') {
					if (bang == 1 || bang == 2){
						if (y > 0)
							break;
						y++;
					}
					else if (bang == 3 || bang == 4) {
						if (x > 0)
							break;
						x++;
					}
				}
			}
		}
		result = result - (x+ y);
		fprintf(out, "%d\n", result);
	}
}