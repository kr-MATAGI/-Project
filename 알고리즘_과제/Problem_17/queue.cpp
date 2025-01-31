#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX(a,b) (a > b ? a : b)

FILE *in = fopen("queue.inp", "r");
FILE *out = fopen("queue.out", "w");

int arr[2000000];
int i, j, k;
int insert_index;
int root_index;

/*
key 삽입시 : insertion 알고리즘 사용, 
               즉 heap마지막에 key값을 넣은 후 위로 올라가면서
			   key값의 위치를 조정

d			: heap에서 루트를 삭제
			마지막 key값을 root에 올린 후, adjust 알고리즘을 이용
				하여 heap을 조정.

r			: Heap의 구조를 일부 보여준다.
				heap의 root에서 출발하여 좌측자식들만 보여준다.

q			: 종료

*/

//insertion
void insertion(int key)
{
	int compare_index;
	int temp;
	compare_index = insert_index;

	//1부터 삽입
	arr[insert_index] = key;
	insert_index++;

	while (1) {
		if (arr[compare_index / 2] < arr[compare_index] && compare_index /2 > 0) {
			temp = arr[compare_index / 2];
			arr[compare_index / 2] = arr[compare_index];
			arr[compare_index] = temp;
			compare_index = compare_index / 2;
		}
		else
			break;
	}
}

//adjust
void adjust()
{
	int temp_index, temp;
	int max_index;
	temp_index = insert_index-1;
	insert_index--;
	arr[1] = arr[temp_index]; //마지막꺼를 제일 처음으로
	arr[temp_index] = 0;
	temp_index = 1;

	while (1) { //추가한거는 총 노드 갯수/ 2 +1 보타 크면 자식이 없다.
		/* 값이 0일경우, temp_index*2가 최대치보다 클경우, temp*2가 현재 총노드의 갯수 초과할 경우, 자식이 없는것을 참조할 경우*/
		if (arr[temp_index * 2] == 0 || temp_index*2 > 1000000 || temp_index*2 >= insert_index || temp_index >= ((insert_index-1)/2) +1)
			break;
		else if (arr[temp_index] < MAX(arr[temp_index * 2], arr[(temp_index * 2) + 1])) {
			for (i = temp_index*2; i <= temp_index*2+1; i++) {//둘중 큰값찾기
				if (MAX(arr[temp_index * 2], arr[(temp_index * 2) + 1]) == arr[i]) {
					max_index = i;
					break;
				}
			}
			temp = arr[temp_index];
			arr[temp_index] = arr[max_index];
			arr[max_index] = temp;
			temp_index = max_index;
		}
		else
			break;
	}
}

//report
void report()
{
	int temp_index;
	temp_index = root_index;
	while (1) {
		if (arr[temp_index] == 0 && temp_index >= insert_index)
			break;
		else {
			fprintf(out, "%d ", arr[temp_index]);
			temp_index *= 2;
		}
	}
	fprintf(out, "\n");
}

int main() 
{
	int key, pre_key;
	char operation;
	
	pre_key = 0;
	insert_index = 1;
	root_index = 1;

	while (1) {
		
		fscanf(in, "%d", &key); 
		if (pre_key != key) {
			insertion(key);
		}
		pre_key = key;

		fscanf(in, "%c", &operation);
		if (operation == 'q')//종료
			break;
		else if (operation == 'd')//삭제
			adjust();
		else if (operation == 'r')//확인
			report();
	}
}