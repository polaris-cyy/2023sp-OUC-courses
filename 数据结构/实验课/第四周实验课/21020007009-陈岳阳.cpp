#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#define MAXSIZE 100
#define INCREMENT 10
#define Elemtype int
using namespace std;

typedef struct Stack {
	Elemtype* base;
	Elemtype* top;
	int size;
}Stack;

bool IsEmpty(Stack s);
bool Labyrinth();
bool SolveLabyrinth(int, int, int, int, int, int, char**);
bool InitLabyrinth(int, int, int&, int&, int&, int&, char**);
void ShowLabyrinth(int, int, int, int, int, int, char**);

void Init(Stack& s) {
	s.base = (Elemtype*)malloc(MAXSIZE * sizeof(Elemtype));
	s.size = MAXSIZE;
	s.top = s.base;
}

void Push(Stack& s, Elemtype x) {
	if (s.top - s.base == s.size ) {
		s.base = (Elemtype*)calloc(s.size + INCREMENT, sizeof(Elemtype));
		s.top = s.base + s.size;
		s.size += INCREMENT;
	}
	*s.top++ = x;
}

void Pop(Stack& s, Elemtype& x) {
	if (IsEmpty(s)) return;
	x = *--s.top;
}

void GetTop(Stack s, Elemtype& x) {
	if (IsEmpty(s)) return;
	x = *(s.top-1);
}

bool IsEmpty(Stack s) {
	return s.top == s.base;
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
	int cur_x, cur_y;
	cur_x = start_x;
	cur_y = start_y;
	//方向 
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};
	//当前方向 
	int d = 0;
	//栈，存储方向以及位置 
	Stack dir_s, x_s, y_s;
	Init(dir_s);
	Init(x_s);
	Init(y_s);
	//将当前所在的位置标注为不可达 
	lab[cur_x][cur_y] = '#';
	while ( (cur_x != end_x) || (cur_y != end_y)){
		//按方向d移动 
		int next_x = cur_x + dx[d], next_y = cur_y + dy[d];
		//可按d方向移动 
		if (next_x >= 0 && next_x < H && next_y >= 0 && next_y < W && (lab[next_x][next_y] == '-')) {
			//入栈当前状态 
			Push(dir_s, d);
			Push(x_s, cur_x);
			Push(y_s, cur_y);
			//移动 
			cur_x = next_x;
			cur_y = next_y;
			lab[cur_x][cur_y] = '#';
			d = 0;
		} else {
			//向下一个方向移动 
			d++;
			//所有方向均不可通行 
			if (d == 4) {
				//死在起点 
				if ( (cur_x == start_x) && (cur_y == start_y)) {
					printf("迷宫无解!\n");
					return false;
				} else {
					//回到上一个位置以及状态 
					Pop(x_s, cur_x);
					Pop(y_s, cur_y);
					Pop(dir_s, d);
				}
			}
		}
	}
	int x, y;
	Stack ans_x, ans_y;
	Init(ans_x);
	Init(ans_y);
	cout << "迷宫可解！\n";
	while (!IsEmpty(x_s)) {
		Pop(x_s, x);
		Pop(y_s, y);
		Push(ans_x, x);
		Push(ans_y, y);
	}	
	while (!IsEmpty(ans_x)) {
		Pop(ans_x, x);
		Pop(ans_y, y);
		cout << x << " " << y << endl;
	}
	cout << end_x << " " << end_y << endl;
	return true;
}

int main() {
	Labyrinth();
	return 0;
}
