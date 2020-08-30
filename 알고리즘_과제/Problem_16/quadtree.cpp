#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;


FILE *in = fopen("quadtree.inp", "r");
FILE *out = fopen("quadtree.out", "w");

int i, j, k;

char arr1[1001];
int arr_length;
vector<string> str(1001);

void rotate(int rule)
{
	int cur_index;
	int length;
	string s1, s2, s3, s4, result, ch;
	
	length = arr_length;
	cur_index = 0;

	switch (rule) {
	case 1: //���Ϸ� ������ 3>4>1>2
		while (1) {
			if (length < 0) {
				ch = str.back();
				str.clear();
				for (i = 0; i <= arr_length; i++) {
					arr1[i] = ch[i];
				}
				break;
			}
			if (arr1[length] == 'X') {
				s1 = str.back();
				str.pop_back();

				s2 = str.back();
				str.pop_back();

				s3 = str.back();
				str.pop_back();

				s4 = str.back();
				str.pop_back();

				result = 'X' + s3 + s4 + s1 + s2;
				str.push_back(result);
				length--;
			}
			else {
				ch = arr1[length];
				str.push_back(ch);
				length--;
			}
		}
		break;
	case 2: //�¿�� ������ 2>1>4>3
		while (1) {
			if (length < 0) {
				ch = str.back();
				str.clear();
				for (i = 0; i <= arr_length; i++) {
					arr1[i] = ch[i];
				}
				break;
			}
			if (arr1[length] == 'X') {
				s1 = str.back();
				str.pop_back();

				s2 = str.back();
				str.pop_back();

				s3 = str.back();
				str.pop_back();

				s4 = str.back();
				str.pop_back();

				result = 'X' + s2 + s1 + s4 + s3;
				str.push_back(result);
				length--;
			}
			else {
				ch = arr1[length];
				str.push_back(ch);
				length--;
			}
		}
		break;
	case 3: //�׸� 90�� ������ 3 > 1 > 4 > 2
		while (1) {
			if (length < 0) {
				ch = str.back();
				str.clear();
				for (i = 0; i <= arr_length; i++) {
					arr1[i] = ch[i];
				}
				break;
			}
			if (arr1[length] == 'X') {
				s1 = str.back();
				str.pop_back();
				
				s2 = str.back();
				str.pop_back();
				
				s3 = str.back();
				str.pop_back();
								
				s4 = str.back();
				str.pop_back();			
				
				result = 'X' + s3 + s1 + s4 + s2;
				str.push_back(result);
				length--;
			}
			else {
				ch = arr1[length];
				str.push_back(ch);
				length--;
			}
		}
		break;
	case 4: //�׸� 180�� ȸ���ϱ� 4 > 3 > 2 > 1
		while (1) {
			if (length < 0) {
				ch = str.back();
				str.clear();
				for (i = 0; i <= arr_length; i++) {
					arr1[i] = ch[i];
				}
				break;
			}
			if (arr1[length] == 'X') {
				s1 = str.back();
				str.pop_back();

				s2 = str.back();
				str.pop_back();

				s3 = str.back();
				str.pop_back();

				s4 = str.back();
				str.pop_back();

				result = 'X' + s4 + s3 + s2 + s1;
				str.push_back(result);
				length--;
			}
			else {
				ch = arr1[length];
				str.push_back(ch);
				length--;
			}
		}
		break;
	case 5: //�׸� 270�� ȸ���ϱ� 2 > 4 > 1 > 3
		while (1) {
			if (length < 0) {
				ch = str.back();
				str.clear();
				for (i = 0; i <= arr_length; i++) {
					arr1[i] = ch[i];
				}
				break;
			}
			if (arr1[length] == 'X') {
				s1 = str.back();
				str.pop_back();

				s2 = str.back();
				str.pop_back();

				s3 = str.back();
				str.pop_back();

				s4 = str.back();
				str.pop_back();

				result = 'X' + s2 + s4 + s1 + s3;
				str.push_back(result);
				length--;
			}
			else {
				ch = arr1[length];
				str.push_back(ch);
				length--;
			}
		}
		break;
	}
}

int main()
{
	int t, T;// �׽�Ʈ ���̽�
	fscanf(in, "%d", &T);

	int op1, op2; //����
	/*1 : �׸��� ���Ϸ� �����´�.
	  2 : �׸��� �¿�� �����´�.
	  3 : �׸��� �������� 90�� ȸ���Ѵ�.
	  4 : �׸��� �������� 180�� ȸ���Ѵ�.
	  5 : �׸��� �������� 270�� ȸ���Ѵ�.
	  */

	for (t = 0; t < T; t++) {
	
		arr_length = 0;

		fscanf(in, "%s\n", arr1);
		//�迭�� ���� �˻�
		for (i = 0; ; i++) {
			if (arr1[i] == NULL) {
				arr_length = i-1;
				break;
			}
		}

		fscanf(in, "%d ", &op1);
		rotate(op1);

		fscanf(in, "%d", &op2);
		rotate(op2);
		for (i = 0; i <= arr_length; i++) {
			fprintf(out, "%c", arr1[i]);
		}
		fprintf(out,"\n");
	}

}