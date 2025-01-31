#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;

FILE *in = fopen("paper.inp", "r");
FILE *out = fopen("paper.out", "w");

typedef struct HeapType {
	int heap[8000];
	int size;
}HeapType;

void insert_max_heap(HeapType *h, int item)
{
	int i;
	for (i = 1; i <= h->size; i++) {
		if (h->heap[i] == item)
			return;
	}

	h->size = h->size + 1;
	i = h->size; //히프 크기가 하나 증가

				 //트리를 거슬러 올라가면서 부모노드와 비교
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

int delete_max_heap(HeapType *h)
{
	int parent, child;
	int item, temp;

	item = h->heap[1]; //삭제할 루트 노드
	temp = h->heap[(h->size)--];

	parent = 1;
	child = 2; //child는 아래로 아래로 그리고 parent는 child를 따라감.

	while (child <= h->size) {
		//현재 노드의 자식중에서 더 작은 자식노드를 찾는다.
		if ((child < h->size) && (h->heap[child]) < (h->heap[child + 1]))
			child++; //child가 오른쪽 자식
		if (temp >= h->heap[child]) break; //맨밑에 내려옴
										   //한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}


HeapType *init()
{
	HeapType *h = (HeapType*)malloc(sizeof(HeapType));
	h->size = 0;

	return h;
}

int main()
{
	//입력변수
	int T; //테스트 케이스 갯수

	int x, y, w, h; //x축 y축 너비 높이
	int **arr;
	int **paper;
	//출력변수
	int anbo, bubun, boim;//아예안보이는거 부분 보이는거 
	anbo = bubun = 0;
	boim = 1;
	//기타
	int i, j, k;
	int count = 1;
	int sort[8000];
	int paper_kan;
	int sibal; // 넓이
	int one_count = 0;


	fscanf(in, "%d", &T);


	//배열 동적할당
	arr = (int**)malloc(sizeof(int*) * T);
	for (i = 0; i < T; i++) {
		arr[i] = (int*)malloc(sizeof(int) * 4);
	}

	HeapType *heap;
	heap = init();

	//배열에 x,y,w,h 입력
	for (i = 0; i < T; i++) {
		fscanf(in, "%d %d %d %d", &x, &y, &w, &h);
		arr[i][0] = x;
		insert_max_heap(heap, x);
		arr[i][1] = y;
		insert_max_heap(heap, y);
		arr[i][2] = w+x;
		insert_max_heap(heap, w+x);
		arr[i][3] = y+h;
		insert_max_heap(heap, y+h);
	}
	count = heap->size;
	for (i = (count); i > 0; i--) {
		sort[i] = delete_max_heap(heap);
	}
	//paper 2차원배열크기 결정
	paper_kan = count + 1;

	//좌표 압축
	for (i = 0; i < T; i++) {
		for (j = 0; j < 4; j++) {
			for (k = 1; k <= count; k++) {
				if (arr[i][j] == sort[k]) {
					arr[i][j] = k;
					break;
				}
			}
		}
	}
	//좌표압축 확인
	//for (i = 0; i < T; i++) {
	//	for (j = 0; j < 4; j++) {
	//		printf("%d ", arr[i][j]);
	//	}
	//	printf("\n");
	//}

	////배열 동적할당
	paper = (int**)malloc(sizeof(int*) * (paper_kan));
	for (i = 0; i < (paper_kan); i++) {
		paper[i] = (int*)malloc(sizeof(int) * (paper_kan));
	}

	//0으로 모두 초기화.
	for (i = 0; i < paper_kan; i++) {
		for (j = 0; j < paper_kan; j++) {
			paper[i][j] = 0;
		}
	}

	////넓이만큼 T로 채워넣기.
	for (i = 0; i < T; i++) {
		for (j = arr[i][1]; j < arr[i][3]; j++) {
			for (k = arr[i][0]; k < arr[i][2]; k++) {
				paper[j][k] = i + 1;
			}
		}
	}

	////paper 출력
	//for (i = 0; i < paper_kan; i++) {
	//	for (j = 0; j < paper_kan; j++) {
	//		printf("%d ", paper[i][j]);
	//	}
	//	printf("\n");

	//}

	//paer에서 각 도형 검사
	for (i = 0; i < T - 1; i++) {
		sibal = (arr[i][2] - arr[i][0]) * (arr[i][3] - arr[i][1]);
		//sibal = arr[i][2] * arr[i][3];
		one_count = 0;
		for (j = arr[i][1]; j < arr[i][3]; j++) {
			for (k = arr[i][0]; k < arr[i][2]; k++) {
				if (paper[j][k] == i + 1)
					one_count++;
			}
		}
		if (one_count == 0)
			anbo++;
		else if (one_count > 0 && one_count < sibal)
			bubun++;
		else if (one_count == sibal)
			boim++;

	}

	fprintf(out, "%d ", anbo);

	fprintf(out, "%d ", bubun);

	fprintf(out, "%d", boim);

	//동적할당 해제
	for (i = 0; i < T; i++) {
		free(arr[i]);
	}
	free(arr);

	for (i = 0; i < paper_kan; i++) {
		free(paper[i]);
	}
	free(paper);


}