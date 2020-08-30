#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *in = fopen("tree.inp", "r");
FILE *out = fopen("tree.out", "w");

typedef struct TreeNode {
	struct TreeNode *left;
	char data;
	int num;
	struct TreeNode *right;
	struct TreeNode *before;
}TreeNode;


TreeNode *t;

TreeNode *add(TreeNode *p, char data, int num, TreeNode *x) {
	if (p == NULL) {
		TreeNode *temp;
		temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->data = data;
		temp->num = num;
		temp->left = NULL;
		temp->right = NULL;
		temp->before = x;

		return temp;
	}

	if (t->data == 'r' && data>='A' && data <='Z') {
		if (t->left == NULL)
			t->left = add(t->left, data, num, t);
		else
			t->right = add(t->right, data, num, t);
	}
	else if (t->data == 'r' && data == 'r') {
		if (t->left == NULL) {
			t->left = add(t->left, data, num, t);
			t = t->left;
		}
		else {
			t->right = add(t->right, data, num, t);
			t = t->right;
		}
	}
}



//전위 순회
void preorder(TreeNode *p) {
	if (p == NULL)
		return;
	else {
		fprintf(out,"%c%d\n", p->data, p->num);
		preorder(p->left);
		preorder(p->right);
	}
}

//중위 순회
void inorder(TreeNode *p) {
	if (p == NULL)
		return;
	else {
		inorder(p->left);
		fprintf(out, "%c%d\n", p->data, p->num);
		inorder(p->right);
	}
}

int main() {

	int K; //테스트 케이스의 갯수
	int i;
	char ch; //한 글자씩 가져옴.
	int r_count = 0; //루트노드 번호 카운트
	int T_num = 0; //트리 넘버 8자리까지.
	int open =0;
	int close = 0;
	fscanf(in, "%d\n", &K);
	TreeNode *root = NULL;
	//가르키는놈

	for (i = 0; i < K; i++) {
		while(1){
			fscanf(in, "%c", &ch);
			if (ch >= 'A' && ch <= 'Z') {
				fscanf(in, "%d", &T_num);
				fprintf(out, "%c%d", ch, T_num);

			}
			else if(ch != '\n')
				fprintf(out, "%c", ch);

			/*if (ch == '\n')
				break;*/

			if (ch == '(') {
				if (r_count == 0) {
					root = add(root, 'r', r_count, NULL);
					r_count++;
					t = root;
					open++;
					
				}
 				else {
					add(root, 'r', r_count, NULL);
					r_count++;
					open++;
				}
			}
			else if (ch >= 'A' && ch <= 'Z') {
				//fscanf(in, "%d", &T_num);
				add(root, ch, T_num, NULL);
			}
			else if (ch == ')') {
					close++;
					if (open == close && t->num ==0)
							break;
				t = t->before;
				
			}

		}
		fprintf(out, "\nPreorder\n");
		preorder(root);
		fprintf(out, "Inorder\n");
		inorder(root);
		root = NULL;
		t = NULL;
		r_count = 0;
		open = 0;
		close = 0;
	}

	return 0;
}