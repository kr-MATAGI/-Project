#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in = fopen("tree.inp", "r");
FILE *out = fopen("tree.out", "w");

typedef struct tree {
	struct tree *Llink;
	int data;
	int index;
	struct tree *Rlink;
}node;

int arr[2][10000];
int node_num; //노드의 갯수
int f_condition, s_condition; //첫 번째 조건, 두 번째 조건
int print_condition;//출력해야할 조건
int i, j, k;
int root_index; //전위나 후위 배열에서 루트 노드 인덱스
int inorder_root; //중위 순회에서 루트 값이 있는곳.
int inorder_index;

int rank; // 첫번째가 -1, 0, 1 인지 구분

node *root, *head;

node *add_node(node *p, int data, int index) {

	if (p == NULL) {
		node *temp;
		temp = (node*)malloc(sizeof(node));
		temp->data = data;
		temp->Llink = NULL;
		temp->Rlink = NULL;
		temp->index = index;

		return temp;
	}

	if (root != NULL) {
		if (index < inorder_root)//왼쪽 서브트리
		{
			while (1) {
				if (index < head->index) //왼쪽에 추가
				{
					if (head->Llink == NULL) {
						head->Llink = add_node(head->Llink, data, index);
						head = root;
						break;
					}
					else if (head->Llink != NULL) {
						head = head->Llink;
					}

				}
				else if (index > head->index) { //오른쪽에 추가
					if (head->Rlink == NULL) {
						head->Rlink = add_node(head->Rlink, data, index);
						head = root;
						break;
					}
					else if (head->Rlink != NULL) {
						head = head->Rlink;
					}
				}
			}

		}
		else if (index > inorder_root) {
			while (1){
				if (index < head->index) //왼쪽에 추가
				{
					if (head->Llink == NULL) {
						head->Llink = add_node(head->Llink, data, index);
						head = root;
						break;
					}
					else if (head->Llink != NULL) {
						head = head->Llink;
					}

				}
				else if (index > head->index) { //오른쪽에 추가
					if (head->Rlink == NULL) {
						head->Rlink = add_node(head->Rlink, data, index);
						head = root;
						break;
					}
					else if (head->Rlink != NULL) {
						head = head->Rlink;
					}
				}
			}
		}
	}
}

//전위 순회
void preorder(node *p) {
	if (p == NULL)
		return;
	else {
		fprintf(out, "%d\n", p->data);
		preorder(p->Llink);
		preorder(p->Rlink);
	}
}

//중위 순회
void posetorder(node *p) {
	if (p == NULL)
		return;
	else {
		posetorder(p->Llink);
		posetorder(p->Rlink);
		fprintf(out, "%d\n", p->data);
		
	}
}

/*
-1 >> 전위 순회
0 >> 중위 순회
1 >> 후위 순회
*/

int main()
{
	rank = 0;
	print_condition = 0;

	fscanf(in, "%d", &node_num);
	//첫 번째 탐색
	fscanf(in, "%d", &f_condition);
	for (i = 0; i < node_num; i++) {
		fscanf(in, "%d\n", &arr[0][i]);
	}
	//두 번째 탐색
	fscanf(in, "%d", &s_condition);
	for (i = 0; i < node_num; i++) {
		fscanf(in, "%d\n", &arr[1][i]);
	}

	//루트노드 찾기
	if (f_condition == -1 || f_condition == 1) {
		if (f_condition == -1)
			root_index = 0;
		else if (f_condition == 1)
			root_index = node_num - 1;

	}
	else if (s_condition == -1 || s_condition == 1) {
		if (s_condition == -1) {
			root_index = 0;
			rank = 1;
		}
		else if (s_condition == 1) {
			root_index = node_num - 1;
			rank = 1;
		}
	}

	//루트 노드를 이용한 트리 만들기
	//전위,중위
	if (rank == 0) { //첫번째에 전위나 후위가 나옴
		if (root_index == 0) { //전위가 나옴
			//중위에서 루트 노드 찾기
			for (i = 0; i < node_num; i++) {
				if (arr[rank + 1][i] == arr[rank][root_index]) {
					inorder_root = i;
					//루트 노드 만들기.
					root = add_node(root, arr[rank][root_index], inorder_root);
					head = root;
					break;
				}
			}

			for (i = 1; i < node_num; i++) {
				for (j = 0; j < node_num; j++) {
					if (arr[rank + 1][j] == arr[rank][i]) {
						inorder_index = j;
						break;
					}
				}
				add_node(root, arr[rank][i], inorder_index);
			}
		}
		else { //후위가 나옴
			if (root_index == node_num - 1) {
				for (i = 0; i < node_num; i++) {
					if (arr[rank + 1][i] == arr[rank][root_index]) {
						inorder_root = i;
						//루트 노드 만들기
						root = add_node(root, arr[rank][root_index], inorder_root);
						head = root;
						break;
					}
				}

				for (i = node_num - 2; i >= 0; i--) {
					for (j = 0; j < node_num; j++) {
						if (arr[rank + 1][j] == arr[rank][i]) {
							inorder_index = j;
							break;
						}
					}
					add_node(root, arr[rank][i], inorder_index);
				}
			}
		}

	}
	else if (rank == 1) { //두번째에서 전위나 후위가 나옴
		if (root_index == 0) { //전위가 나옴
							   //중위에서 루트 노드 찾기

							   //rank 중위, rank + 1 전위
			for (i = 0; i < node_num; i++) {
				if (arr[rank][root_index] == arr[rank-1][i]) {
					inorder_root = i;
					//루트 노드 만들기.
					root = add_node(root, arr[rank][root_index], inorder_root);
					head = root;
					break;
				}
			}

			for (i = 1; i < node_num; i++) {
				for (j = 0; j < node_num; j++) {
					if (arr[rank-1][j] == arr[rank][i]) {
						inorder_index = j;
						break;
					}
				}
				add_node(root, arr[rank][i], inorder_index);
			}
		}
		else { //후위가 나옴
			if (root_index == node_num - 1) {
				for (i = 0; i < node_num; i++) {
					if (arr[rank][root_index] == arr[rank-1][i]) {
						inorder_root = i;
						//루트 노드 만들기
						root = add_node(root, arr[rank][root_index], inorder_root);
						head = root;
						break;
					}
				}

				for (i = node_num - 2; i >= 0; i--) {
					for (j = 0; j < node_num; j++) {
						if (arr[rank-1][j] == arr[rank][i]) {
							inorder_index = j;
							break;
						}
					}
					add_node(root, arr[rank][i], inorder_index);
				}
			}
		}
	}



	//출력 조건 및 출력
	print_condition = (f_condition + s_condition);
	if (print_condition == -1) { //후위 출력
		posetorder(root);
	}
	else { //전위 출력
		preorder(root);
	}


}