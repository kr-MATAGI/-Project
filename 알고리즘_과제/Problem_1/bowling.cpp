#include <stdio.h>

FILE *in = fopen("bowling.inp", "r");
FILE *out = fopen("bowling.out", "w");

int main()
{
	//테스트 케이스 (<=10)
	int T;
	int i, j;
	int num1, num2;
	int arr1[10] = { 0, };
	int arr2[10] = { 0, };
	int socre; //각 프레임 점수
	int sum_socre; //총 점수규칙
	int bouns;



	fscanf(in, "%d", &T);

	for (i = 0; i < T; i++)
	{
		//점수 항목 초기화.
		socre = 0;
		sum_socre = 0;

		for (j = 0; j < 10; j++)
		{
			//각 프레임 입력

			fscanf(in, "%d", &num1);

			//공백처리
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
		
		//계산하기
		for (j = 0; j < 10; j++)
		{
			//마지막 프레임에서 첫 째 점수가 10인경우
			if (j == 9 && arr1[j] == 10)
			{
				fscanf(in, "%d", &bouns);
				socre = arr1[j] + arr2[j] + bouns;
				sum_socre = sum_socre + socre;
			}
			//마지막 프레임에서 첫 + 두번쨰가 10점인경우
			else if (j == 9 && arr1[j] + arr2[j] == 10)
			{
				fscanf(in, "%d", &bouns);
				socre = arr1[j] + arr2[j] + bouns;
				sum_socre = sum_socre + socre;
			}

			//스트라이크 후, 다음 두 투구를 추가점수
			else if (arr1[j] == 10)
			{
				//다음에도 스트라이크 칠때
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
			//스페어 : 두번째 투구를 통하여 나머지 핀 모두, 다음 첫 투구때 점수 추가
			else if (arr1[j] + arr2[j] == 10)
			{
				socre = arr1[j] + arr2[j] + arr1[j + 1];
				sum_socre = sum_socre + socre;
			}
			//오픈 : 나머지 스트라이크도 스페어처리도 안됬을때.
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