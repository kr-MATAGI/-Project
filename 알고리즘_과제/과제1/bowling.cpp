#include <stdio.h>

FILE *in = fopen("bowling.inp", "r");
FILE *out = fopen("bowling.out", "w");

int main()
{
	//�׽�Ʈ ���̽� (<=10)
	int T;
	int i, j;
	int num1, num2;
	int arr1[10] = { 0, };
	int arr2[10] = { 0, };
	int socre; //�� ������ ����
	int sum_socre; //�� ������Ģ
	int bouns;



	fscanf(in, "%d", &T);

	for (i = 0; i < T; i++)
	{
		//���� �׸� �ʱ�ȭ.
		socre = 0;
		sum_socre = 0;

		for (j = 0; j < 10; j++)
		{
			//�� ������ �Է�

			fscanf(in, "%d", &num1);

			//����ó��
			if (num1 == 10)
			{
				if (j == 9)
				{
					fscanf(in, "%d", &num2);
					arr1[j] = num1;
					arr2[j] = num2;
					continue;
				}
				arr1[j] = num1;
				continue;
			}
			else
			{
				fscanf(in, "%d", &num2);
				arr1[j] = num1;
				arr2[j] = num2;
			}
		}
		
		//����ϱ�
		for (j = 0; j < 10; j++)
		{
			//������ �����ӿ��� ù ° ������ 10�ΰ��
			if (j == 9 && arr1[j] == 10)
			{
				fscanf(in, "%d", &bouns);
				socre = arr1[j] + arr2[j] + bouns;
				sum_socre = sum_socre + socre;
			}
			//������ �����ӿ��� ù + �ι����� 10���ΰ��
			else if (j == 9 && arr1[j] + arr2[j] == 10)
			{
				fscanf(in, "%d", &bouns);
				socre = arr1[j] + arr2[j] + bouns;
				sum_socre = sum_socre + socre;
			}

			//��Ʈ����ũ ��, ���� �� ������ �߰�����
			else if (arr1[j] == 10)
			{
				//�������� ��Ʈ����ũ ĥ��
				if (arr1[j + 1] == 10)
				{
					if (j == 8 && arr1[j+1] == 10)
					{
						socre = arr1[j] + arr1[j+1] + arr2[j+1];
						sum_socre = sum_socre + socre;
						continue;
					}
					socre = arr1[j] + arr1[j+1] + arr1[j+2];
					sum_socre = sum_socre + socre;
				}
				else
				{
					socre = arr1[j] + arr1[j + 1] + arr2[j + 1];
					sum_socre = sum_socre + socre;
				}
			}
			//����� : �ι�° ������ ���Ͽ� ������ �� ���, ���� ù ������ ���� �߰�
			else if (arr1[j] + arr2[j] == 10)
			{
				socre = arr1[j] + arr2[j] + arr1[j + 1];
				sum_socre = sum_socre + socre;
			}
			//���� : ������ ��Ʈ����ũ�� �����ó���� �ȉ�����.
			else
			{ 
				socre = arr1[j] + arr2[j];
				sum_socre = sum_socre +  socre;
			}
		}

		fprintf(out, "%d\n", sum_socre);
	}
	return 0;
}