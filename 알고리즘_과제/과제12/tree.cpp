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
int node_num; //����� ����
int f_condition, s_condition; //ù ��° ����, �� ��° ����
int print_condition;//����ؾ��� ����
int i, j, k;
int root_index; //������ ���� �迭���� ��Ʈ ��� �ε���
int inorder_root; //���� ��ȸ���� ��Ʈ ���� �ִ°�.
int inorder_index;

int rank; // ù��°�� -1, 0, 1 ���� ����

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
		if (index < inorder_root)//���� ����Ʈ��
		{
			while (1) {
				if (index < head->index) //���ʿ� �߰�
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
				else if (index > head->index) { //�����ʿ� �߰�
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
				if (index < head->index) //���ʿ� �߰�
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
				else if (index > head->index) { //�����ʿ� �߰�
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

//���� ��ȸ
void preorder(node *p) {
	if (p == NULL)
		return;
	else {
		fprintf(out, "%d\n", p->data);
		preorder(p->Llink);
		preorder(p->Rlink);
	}
}

//���� ��ȸ
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
-1 >> ���� ��ȸ
0 >> ���� ��ȸ
1 >> ���� ��ȸ
*/

int main()
{
	rank = 0;
	print_condition = 0;

	fscanf(in, "%d", &node_num);
	//ù ��° Ž��
	fscanf(in, "%d", &f_condition);
	for (i = 0; i < node_num; i++) {
		fscanf(in, "%d\n", &arr[0][i]);
	}
	//�� ��° Ž��
	fscanf(in, "%d", &s_condition);
	for (i = 0; i < node_num; i++) {
		fscanf(in, "%d\n", &arr[1][i]);
	}

	//��Ʈ��� ã��
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

	//��Ʈ ��带 �̿��� Ʈ�� �����
	//����,����
	if (rank == 0) { //ù��°�� ������ ������ ����
		if (root_index == 0) { //������ ����
			//�������� ��Ʈ ��� ã��
			for (i = 0; i < node_num; i++) {
				if (arr[rank + 1][i] == arr[rank][root_index]) {
					inorder_root = i;
					//��Ʈ ��� �����.
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
		else { //������ ����
			if (root_index == node_num - 1) {
				for (i = 0; i < node_num; i++) {
					if (arr[rank + 1][i] == arr[rank][root_index]) {
						inorder_root = i;
						//��Ʈ ��� �����
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
	else if (rank == 1) { //�ι�°���� ������ ������ ����
		if (root_index == 0) { //������ ����
							   //�������� ��Ʈ ��� ã��

							   //rank ����, rank + 1 ����
			for (i = 0; i < node_num; i++) {
				if (arr[rank][root_index] == arr[rank-1][i]) {
					inorder_root = i;
					//��Ʈ ��� �����.
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
		else { //������ ����
			if (root_index == node_num - 1) {
				for (i = 0; i < node_num; i++) {
					if (arr[rank][root_index] == arr[rank-1][i]) {
						inorder_root = i;
						//��Ʈ ��� �����
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



	//��� ���� �� ���
	print_condition = (f_condition + s_condition);
	if (print_condition == -1) { //���� ���
		posetorder(root);
	}
	else { //���� ���
		preorder(root);
	}


}