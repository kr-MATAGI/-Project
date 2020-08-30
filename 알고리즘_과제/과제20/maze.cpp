#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>

FILE *in = fopen("maze.inp", "r");
FILE *out = fopen("maze.out", "w");

using namespace std;


typedef struct ARR{
	int open;
	bool pass;
}arr;

arr XY[10000][10000];

int result[100000];
int print[100000];

int row, col;

int start, cal_end, sum_kan;

bool maze_end;

vector<int> v;

void DFS(int x, int y)
{
	
	if (maze_end == true)
		return;
	XY[x][y].pass = true;
	if (col*x+y == cal_end) {
		maze_end = true;
		return;
	}
	if (maze_end == false) {
		if (x == 0 && y == 0) {
			v.push_back(row*x + y);
			XY[x][y].pass = true;

			cout << v.back() << endl;
		}

		//동쪽
		//최대 행과 열보다 작고 동쪽이 오픈되어있을경우
		if (y + 1 < col && x < row) {
			if (XY[x][y].open == 1 || XY[x][y].open == 3) {
				if (XY[x][y + 1].pass == false) { //방문하지 않은 노드일 경우만
					v.push_back(col*x + (y + 1));
					XY[x][y+1].pass = true;

					DFS(x, y + 1);
					if (maze_end == true)
						return;
					v.pop_back();


				}
			}
		}

		//서쪽
		if (y - 1 >= 0 && x < row) {
			if (XY[x][y-1].open == 1 || XY[x][y-1].open == 3) {
				if (XY[x][y - 1].pass == false) {
					v.push_back(col*x + (y - 1));
					XY[x][y - 1].pass = true;

					DFS(x, y - 1);

					if (maze_end == true)
						return;

					v.pop_back();

				}
			}
		}
		//남쪽
		if (x + 1 < row && y < col) {
			if (XY[x][y].open == 2 || XY[x][y].open == 3) {
				if (XY[x + 1][y].pass == false) {
					v.push_back(col*(x + 1) + y);
					XY[x + 1][y].pass = true;

					DFS(x + 1, y);
					if (maze_end == true)
						return;

					v.pop_back();

				}
			}
		}

		//북쪽
		if (x - 1 >= 0 && y < col) {
			if (XY[x - 1][y].open == 2 || XY[x - 1][y].open == 3) {
				if (XY[x - 1][y].pass == false) {
					v.push_back(col*(x - 1) + y);
					XY[x - 1][y].pass = true;

					DFS(x - 1, y);

					if (maze_end == true)
						return;
					v.pop_back();

				}
			}
		}

	}

}

int main()
{


	int block, index;

	

	fscanf(in, "%d %d", &row, &col);

	start = 0;
	cal_end = row*col - 1;
	sum_kan = row*col;

	while (1) {
		fscanf(in, "%d %d", &index, &block);
		if (index == -1 && block == -1)
			break; //-1 -1이 나오면 끝난다.

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i*col + j == index) {
					XY[i][j].open = block;
					break;
				}
			}
		}
	}

	DFS(0,0);

	if (maze_end == true) {
		int size = v.size();
		for (int i = 0; i < size; i++) {
			result[i] = v.back(); v.pop_back();
		}

		for (int i = size-1, j = 0; i >= 0; i--,j++) {
			print[j] = result[i];
		}
		for (int i = 0; i < size; i++) {
			fprintf(out, "%d\n", print[i]);
		}
	}
	else
		fprintf(out, "No Solution!");

}