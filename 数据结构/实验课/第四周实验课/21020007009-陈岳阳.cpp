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
	printf("�����Թ��߶ȺͿ��:");
	cin >> H >> W;
	char**lab;
	lab = (char**)malloc(H*sizeof(char*));
	for (int i = 0; i < W; ++i) lab[i] = (char*)malloc(W*sizeof(char));
	if (!InitLabyrinth(H, W, start_x, start_y, end_x, end_y, lab)) {
		printf("�Թ���ʼ������");
		return false;
	} else {
		ShowLabyrinth(H, W, start_x, start_y, end_x, end_y, lab);
	}
	return SolveLabyrinth(H, W, start_x, start_y, end_x, end_y, lab);
}

bool InitLabyrinth(int H, int W, int &start_x, int &start_y, int &end_x, int &end_y, char**lab) {
	/***
		H, W: �Թ��ĸ߶ȺͿ��
		start_x, start_y: ������� 
		end_x, end_y: �յ����� 
		lab: �Թ� 
		return: �ɹ���ʼ���Թ������Թ���ʽ��ȷ������true�����򷵻�false 
	***/
	printf("�����Թ�����������:");
	cin >> start_x >> start_y;
	printf("�����Թ��յ��������:");
	cin >> end_x >> end_y;
	//������յ���ͬ 
	if (start_x == end_x && start_y == end_y) return false;
	//�����յ����Թ�֮�� 
	if (start_x < 0 || start_x>= H) return false;
	if (start_y < 0 || start_y>= W) return false;
	if (end_x < 0 || end_y>= H) return false;
	if (end_y < 0 || end_y>= W) return false;
	printf("�����Թ�(#Ϊǽ��, -��ͨ��):\n");
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			cin >> lab[i][j];
			//�������� 
			if (lab[i][j] != '#' && lab[i][j] != '-') {
				return false;
			}
		}
	}
	//�����յ㲻��ͨ�� 
	if(lab[start_x][start_y] == '#') return false;
	if(lab[end_x][end_y] == '#') return false;
	return true;
} 

void ShowLabyrinth(int H, int W, int start_x, int start_y, int end_x, int end_y, char**lab) {
	/***
		���ض���ʽ��ӡ�������Թ���
			�����ߵĵط���-
			�������ߵĵط���#
			��㣺@
			�յ㣺O 
	***/
	cout << "�Թ���ʽ:\n";
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
	//��ǰλ�� 
	int cur_x, cur_y;
	cur_x = start_x;
	cur_y = start_y;
	//���� 
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};
	//��ǰ���� 
	int d = 0;
	//ջ���洢�����Լ�λ�� 
	Stack dir_s, x_s, y_s;
	Init(dir_s);
	Init(x_s);
	Init(y_s);
	//����ǰ���ڵ�λ�ñ�עΪ���ɴ� 
	lab[cur_x][cur_y] = '#';
	while ( (cur_x != end_x) || (cur_y != end_y)){
		//������d�ƶ� 
		int next_x = cur_x + dx[d], next_y = cur_y + dy[d];
		//�ɰ�d�����ƶ� 
		if (next_x >= 0 && next_x < H && next_y >= 0 && next_y < W && (lab[next_x][next_y] == '-')) {
			//��ջ��ǰ״̬ 
			Push(dir_s, d);
			Push(x_s, cur_x);
			Push(y_s, cur_y);
			//�ƶ� 
			cur_x = next_x;
			cur_y = next_y;
			lab[cur_x][cur_y] = '#';
			d = 0;
		} else {
			//����һ�������ƶ� 
			d++;
			//���з��������ͨ�� 
			if (d == 4) {
				//������� 
				if ( (cur_x == start_x) && (cur_y == start_y)) {
					printf("�Թ��޽�!\n");
					return false;
				} else {
					//�ص���һ��λ���Լ�״̬ 
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
	cout << "�Թ��ɽ⣡\n";
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
