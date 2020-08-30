#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <vector>

//프림이 빠를까? 크루스칼이 빠를까???

using namespace std;

FILE *in = fopen("mst.inp", "r");
FILE *out = fopen("mst.out", "w");

int i, j, k;

struct EDGE {
	int u, v;
	int w;
	int index;
	int visit;
};

bool cmp_edge(EDGE a, EDGE b) {
	if (a.w == b.w)
		return a.index < b.index;
	else 
		return a.w < b.w;
}

//입력배열
EDGE a[100001];
EDGE b[100001];

//결과 배열
int result_edge[10001];

//정점 배열
int vertex[10001];

int N, M; //정점과 EDGE
int kru_sum, kru_min_edge, kru_min_index;
int re_end;

void kruskal()
{
	int edge_count; //n-1개의 엣지를 찾으면 종료하도록
	int vertex_1, vertex_2;
	int p, q;
	int cur_index; //정렬된 a의 현재 인덱스
	int different_start; //가중치로 정렬된 구조체를 다시 인덱스로 정렬
	cur_index = 0;
	different_start = 0;
	edge_count = 0;

	while (1) {
		if (edge_count == N - 1) {
			re_end = edge_count;
			fprintf(out, "Tree edges by Kruskal algorithm: %d\n", kru_sum);
			for (k = 0; k < edge_count; k++) {
				fprintf(out, "%d\n", result_edge[k]);
			}
			break;
		}
		
		//최소값의 edge 찾기
		kru_min_edge = a[cur_index].w;
		kru_min_index = cur_index;


		//kruskal 시작
		//두 개의 정점 다시 받아오고
		vertex_1 = a[kru_min_index].u;
		vertex_2 = a[kru_min_index].v;

		//각 정점의 루트 노드 찾기
		//find
		//여기서 시간 에러가 뜨거나?
		p = vertex_1;
		while (1) {
			p = vertex[p];
			if (p == vertex[p])
				break;
		}
		q = vertex_2;
		while (1) {
			q = vertex[q];
			if (q == vertex[q])
				break;
		}
		//equl
		if (p != q) {
			//merge
			vertex[p] = vertex[p];
			vertex[q] = vertex[p];
			result_edge[edge_count] = a[kru_min_index].index;
			kru_sum += a[kru_min_index].w;
			edge_count++;
			cur_index++;
		}
		else if (p == q) {
			cur_index++;
			continue;
		}
	}
}

void reset() {
	for (i = 0; i < N; i++) {
		vertex[i] = 0;
	}
	for (i = 0; i < M; i++) {
		b[i].visit = 0;
	}
}

struct cmp {
	bool operator()(EDGE a, EDGE b) {
		if (a.w == b.w)
			return a.index > b.index;
		else
			return a.w > b.w;
	}
};

priority_queue<int, vector<EDGE>, cmp> PQ;

void prim(int start)
{
	int cur_sp; //현재 우선순위 큐에 넣는걸 비교하는 거;
	int print;
	int end_cnt;
	fprintf(out, "Tree edges by Prim algorithm with starting vertex %d: %d\n", start, kru_sum);

	end_cnt = 0;
	cur_sp = start;
	vertex[start] = 1; //제일 처음 스타트 지점은 슈퍼노드에 포함된다.
	while (1) {
		if (end_cnt == N - 1)
			break;
		for (i = 0; i < N - 1; i++) {//슈퍼노드에 해당되는 u v w 를 우선순위 큐에 넣는 연산
			if ((cur_sp == b[result_edge[i]].v && b[result_edge[i]].visit == 0)||
				(cur_sp == b[result_edge[i]].u && b[result_edge[i]].visit == 0)) {
				PQ.push(b[result_edge[i]]);
				b[result_edge[i]].visit = 1;
				/*cout << PQ.top().u << endl;
				cout << PQ.top().v << endl;
				cout << PQ.top().w << endl;
				cout << PQ.top().index << endl;*/
			}
		}
		vertex[cur_sp] = 1;
		
		//제일 작은값 출력
		print = PQ.top().index;
	/*	cout << PQ.top().v << endl;
		cout << PQ.top().u << endl;*/

		//슈퍼노드 바꾸기
		if (vertex[PQ.top().u] == 0)
			cur_sp = PQ.top().u;
		else if (vertex[PQ.top().v] == 0)
			cur_sp = PQ.top().v;
		PQ.pop();
		
		
		end_cnt++;
		fprintf(out, "%d\n", print);
		
	}
	
}

int main()
{
	kru_sum = 0;

	fscanf(in, "%d %d", &N, &M);


	//kruskal
	//각 노드들이 처음에는 자기자기신이 루트가리키도록
	//memset(vertex, -1, sizeof(vertex));
	for (i = 0; i < 10001; i++) {
		vertex[i] = -1;
	}

	for (i = 0; i < N; i++) {
		vertex[i] = i;
	}
	//엣지에 입력
	for (i = 0; i < M; i++) {
		fscanf(in, "%d %d %d", &a[i].u, &a[i].v, &a[i].w);
		a[i].index = i;
		b[i].u = a[i].u;
		b[i].v = a[i].v;
		b[i].w = a[i].w;
		b[i].index = i;
	}
	sort(a, a + M, cmp_edge);

	kruskal();
	reset();
	
	prim(0);
	reset();

	prim((N / 2));
	reset();

	prim(N - 1);

}