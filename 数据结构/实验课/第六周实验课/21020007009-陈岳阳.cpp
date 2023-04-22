#include <iostream>
#include <cstdio> 
#include <cmath>
#include <cstring>
#include <cstdlib>
#define MAXSIZE 100
#define INCREMENT 10
#define Elemtype int
#define Error -1
#define OK 1
#define Status int
using namespace std;

bool Labyrinth();
bool SolveLabyrinth(int, int, int, int, int, int, char**);
bool InitLabyrinth(int, int, int&, int&, int&, int&, char**);
void ShowLabyrinth(int, int, int, int, int, int, char**);

typedef struct Queue{
	Elemtype *elem;
	int front, rear;
	int size;
	int counter;
}Q; 

void Init(Q &q, int);

bool IsEmpty(Q q);

Status Front(Q q, Elemtype &x);

Status Push(Q &q, Elemtype x);

Status Pop(Q &q, Elemtype &x);

int Length(Q q);

void Init(Q &q, int size=MAXSIZE+1) {
	q.elem = (Elemtype*)malloc(size * sizeof(Elemtype));
	q.front = q.rear = 0;
	q.size = size;
}

bool IsEmpty(Q q) {
	return q.front == q.rear;
}

int Length(Q q) {
	int length = q.rear - q.front;
	return (length >= 0) ? length : length+q.size;
}

Status Front(Q q, Elemtype &x) {
	if (IsEmpty(q)) return Error;
	x = q.elem[q.front];
}

Status Push(Q &q, Elemtype x) {
	if (Length(q)+1 == q.size) return Error; //满 
	q.elem[q.rear++] = x;
	q.rear %= q.size;
	return OK;
}

Status Pop(Q &q, Elemtype &x) {
	if (IsEmpty(q)) return Error;
	x = q.elem[q.front++];
	q.front %= q.size;
	return OK;
}

bool Labyrinth() {
	int H, W, start_x, start_y, end_x, end_y;
	printf("输入迷宫高度和宽度:");
	cin >> H >> W;
	char**lab;
	lab = (char**)malloc(H*sizeof(char*));
	for (int i = 0; i < W; ++i) lab[i] = (char*)malloc(W*sizeof(char));
	if (!InitLabyrinth(H, W, start_x, start_y, end_x, end_y, lab)) {
		printf("迷宫初始化错误");
		return false;
	} else {
		ShowLabyrinth(H, W, start_x, start_y, end_x, end_y, lab);
	}
	return SolveLabyrinth(H, W, start_x, start_y, end_x, end_y, lab);
}

bool InitLabyrinth(int H, int W, int &start_x, int &start_y, int &end_x, int &end_y, char**lab) {
	/***
		H, W: 迷宫的高度和宽度
		start_x, start_y: 起点坐标 
		end_x, end_y: 终点坐标 
		lab: 迷宫 
		return: 成功初始化迷宫，且迷宫格式正确，返回true，否则返回false 
	***/
	printf("输入迷宫起点横纵坐标:");
	cin >> start_x >> start_y;
	printf("输入迷宫终点横纵坐标:");
	cin >> end_x >> end_y;
	//起点与终点相同 
	if (start_x == end_x && start_y == end_y) return false;
	//起点或终点在迷宫之外 
	if (start_x < 0 || start_x>= H) return false;
	if (start_y < 0 || start_y>= W) return false;
	if (end_x < 0 || end_y>= H) return false;
	if (end_y < 0 || end_y>= W) return false;
	printf("输入迷宫(#为墙壁, -可通过):\n");
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			cin >> lab[i][j];
			//错误输入 
			if (lab[i][j] != '#' && lab[i][j] != '-') {
				return false;
			}
		}
	}
	//起点或终点不可通过 
	if(lab[start_x][start_y] == '#') return false;
	if(lab[end_x][end_y] == '#') return false;
	return true;
} 

void ShowLabyrinth(int H, int W, int start_x, int start_y, int end_x, int end_y, char**lab) {
	/***
		以特定格式打印出整个迷宫：
			可以走的地方：-
			不可以走的地方：#
			起点：@
			终点：O 
	***/
	cout << "迷宫样式:\n";
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (i == start_x && j == start_y){
				cout << "@ ";
			} else if (i == end_x && j == end_y) {
				cout << "O ";
			} else {
				cout << lab[i][j] << ' ';
			}
		}
		cout << endl;
	}
}

bool SolveLabyrinth(int H, int W, int start_x, int start_y, int end_x, int end_y, char**lab) {
	//当前位置 
	int cur_x, cur_y, steps;
	cur_x = start_x;
	cur_y = start_y;
	steps = 0;
	//方向 
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};
	//当前方向 
	int d = 0;
	Q cur_x_q, cur_y_q, steps_q;
	Init(cur_x_q);	//当前位置 
	Init(cur_y_q);
	Init(steps_q);//走到cur时，已经走的步数
	
	//记录每个点的最短路径 
	int**vis = (int**)malloc(H*sizeof(int*));
	int**pre_x = (int**)malloc(H*sizeof(int*));
	int**pre_y = (int**)malloc(H*sizeof(int*));
	for (int i = 0; i < W; ++i) {
		vis[i] = (int*)malloc(W*sizeof(int));
		pre_x[i] = (int*)malloc(W*sizeof(int));
		pre_y[i] = (int*)malloc(W*sizeof(int));
	}
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < H; ++j) {
			if (lab[i][j] == '#') {
				vis[i][j] = 0;
			} else {
				vis[i][j] = 0x7fffffff;
			}
			pre_x[i][j] = 0;
			pre_y[i][j] = 0;
		}
	}
	vis[start_x][start_y] = 0;
	Push(cur_x_q, start_x);
	Push(cur_y_q, start_y);
	
	while (cur_x != end_x || cur_y != end_y) {
		if (IsEmpty(cur_x_q)) {
			printf("迷宫无解!\n");
			return false;
		}
		Pop(cur_x_q, cur_x);
		Pop(cur_y_q, cur_y);
		Pop(steps_q, steps);
		steps++;
		for (d = 0; d < 4; ++d) {
			int x = cur_x+dx[d], y = cur_y+dy[d];
			if (vis[x][y] > steps) {
				vis[x][y] = steps;
				pre_x[x][y] = cur_x;
				pre_y[x][y] = cur_y;
				Push(cur_x_q, x);
				Push(cur_y_q, y);
				Push(steps_q, steps);
			}
		}
	}
	cur_x = end_x, cur_y = end_y;
	while (cur_x != start_x || cur_y != start_y) {
		cout << "(" << cur_x << "," << cur_y << ") <- ";
		int x = cur_x, y = cur_y;
		cur_x = pre_x[x][y];
		cur_y = pre_y[x][y]; 
	}
	cout  << "(" << cur_x << "," << cur_y << ")" << endl;
	return true;
}

int main() {
	Labyrinth();
	return 0;
}
