#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in = fopen("pandora.inp", "r");
FILE *out = fopen("pandora.out", "w");

char arr[100005];

int main()
{
	//����� 0 , 1 , 2
	int T; //�׽�Ʈ ���̽�
	int t, i, j, k;
	int bang; //1 : ��, 2: �Ʒ�, 3: ����, 4: ������
	char pre_ch;//�������� �ϳ� ����
	int result; //����� ��� ��
	int x, y; //x���� y����
	fscanf(in, "%d", &T);

	for (t = 0; t < T; t++) {

		result = 2;
		bang = 1;
		x = y = 0;
		fscanf(in, "%s", arr);
		pre_ch = arr[0];
		//1 : ��, 2: �Ʒ�, 3: ����, 4: ������
		for (i = 1; i < strlen(arr); i++) {
			if (arr[i] == 'L') { // L �� �Է¹޾��� ���
				if (bang == 1) { //���� ���ϰ� ������
					bang = 3; //�������� ȸ��
					pre_ch = arr[i];
				}
				else if (bang == 2) {//�Ʒ��� ���Ҷ�
					bang = 4; //���������� ȸ��
					pre_ch = arr[i];
				}
				else if (bang == 3) {//������ ���ҋ�
					bang = 2; //�Ʒ���
					pre_ch = arr[i];
				}
				else if (bang == 4) { //�������� ���Ҷ�
					bang = 1; //����
					pre_ch = arr[i];
				}
			}
			//1 : ��, 2: �Ʒ�, 3: ����, 4: ������
			else if (arr[i] == 'R') { //R�� �Է� �޾��� ���
				if (bang == 1) { //���� ���ϰ�������
					bang = 4; //���������� ȸ��
					if (pre_ch == 'R') {
						if (y > 0)
							continue;
						y++;
					}
					pre_ch = arr[i];
				}
				else if (bang == 2) { //������ �Ʒ���
					bang = 3; //�������� ����
					if (pre_ch == 'R') {
						if (y > 0)
							continue;
						y++;
						
					}
					pre_ch = arr[i];
				}
				else if (bang == 3) { //������ ������ ����ų��
					bang = 1; //���� ��ȯ
					if (pre_ch == 'R') {
						if (x> 0)
							continue;
						x++;
					}
						pre_ch = arr[i];
					
				
				}
				else if (bang = 4) { //������ �������� ����ų��
					bang = 2; //�Ʒ��� ��ȯ
					if (pre_ch == 'R') {
						if (x > 0)
							continue;
						x++;
						pre_ch = arr[i];
					}
					pre_ch = arr[i];
				}

			}
			//ó���� ���� R�϶�
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