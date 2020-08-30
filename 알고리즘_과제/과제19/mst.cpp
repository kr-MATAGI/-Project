#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <vector>

//������ ������? ũ�罺Į�� ������???

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

//�Է¹迭
EDGE a[100001];
EDGE b[100001];

//��� �迭
int result_edge[10001];

//���� �迭
int vertex[10001];

int N, M; //������ EDGE
int kru_sum, kru_min_edge, kru_min_index;
int re_end;

void kruskal()
{
	int edge_count; //n-1���� ������ ã���� �����ϵ���
	int vertex_1, vertex_2;
	int p, q;
	int cur_index; //���ĵ� a�� ���� �ε���
	int different_start; //����ġ�� ���ĵ� ����ü�� �ٽ� �ε����� ����
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
		
		//�ּҰ��� edge ã��
		kru_min_edge = a[cur_index].w;
		kru_min_index = cur_index;


		//kruskal ����
		//�� ���� ���� �ٽ� �޾ƿ���
		vertex_1 = a[kru_min_index].u;
		vertex_2 = a[kru_min_index].v;

		//�� ������ ��Ʈ ��� ã��
		//find
		//���⼭ �ð� ������ �߰ų�?
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
	int cur_sp; //���� �켱���� ť�� �ִ°� ���ϴ� ��;
	int print;
	int end_cnt;
	fprintf(out, "Tree edges by Prim algorithm with starting vertex %d: %d\n", start, kru_sum);

	end_cnt = 0;
	cur_sp = start;
	vertex[start] = 1; //���� ó�� ��ŸƮ ������ ���۳�忡 ���Եȴ�.
	while (1) {
		if (end_cnt == N - 1)
			break;
		for (i = 0; i < N - 1; i++) {//���۳�忡 �ش�Ǵ� u v w �� �켱���� ť�� �ִ� ����
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
		
		//���� ������ ���
		print = PQ.top().index;
	/*	cout << PQ.top().v << endl;
		cout << PQ.top().u << endl;*/

		//���۳�� �ٲٱ�
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
	//�� ������ ó������ �ڱ��ڱ���� ��Ʈ����Ű����
	//memset(vertex, -1, sizeof(vertex));
	for (i = 0; i < 10001; i++) {
		vertex[i] = -1;
	}

	for (i = 0; i < N; i++) {
		vertex[i] = i;
	}
	//������ �Է�
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