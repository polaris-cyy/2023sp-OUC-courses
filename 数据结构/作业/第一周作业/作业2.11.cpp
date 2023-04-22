#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Elemtype int
#define Status
#define OK 1
#define True 1
#define False 0 
#define Error 0
#define MAXSIZE 100
#define SIZE_INCREMENT 10

typedef struct{
	Elemtype* elem;
	int length;
	int size;
}SqList;


void Init(SqList &l) {
	l.elem = (Elemtype*)malloc(MAXSIZE * sizeof(int));
	l.length = 0;
	l.size = MAXSIZE;
}

Status NewSpace(SqList &l) {
	l.elem = (Elemtype*)calloc((l.size + SIZE_INCREMENT), sizeof(Elemtype));
	l.size += SIZE_INCREMENT;
	return OK;
}

void Insert(SqList &l, Elemtype x) {
	if (l.size == l.length) NewSpace(l);
	int i;
	i = l.length;
	while (i && l.elem[i-1] >= x) {
		l.elem[i] = l.elem[i-1];
		i--;
	}
	l.elem[i] = x;
	l.length++;
}

int Compare(SqList &a, SqList &b) {
	//如果表a大于表b，返回1；两表相等，返回0；否则返回-1 
	int i;
	i = 0;
	if (!a.length && !b.length) return 0; //都是空表 
	while (i < a.length && i < b.length && a.elem[i] == b.elem[i]) i++; //去重复前缀 
	if (a.length == b.length) {
		if (i == a.length) return 0; //两表完全相同 
		if (a.elem[i] < b.elem[i]) return -1; //a < b 
		return 1; //a > b
	} else {
		if (i == a.length) return -1; //a是b的前缀 
		if (i == b.length) return  1; //b是a的前缀 
		if (a.elem[i] < b.elem[i]) return -1; //a < b 
		if (a.elem[i] > b.elem[i]) return  1; //a > b
	}
}

void Print(SqList& l) {
	int i;
	i = 0;
	while (i < l.length) printf("%d ", l.elem[i++]);
	printf("\n");
}

int main() {
	SqList l1, l2;
	Init(l1);
	Init(l2);
	Insert(l1, 10);
	Insert(l2, 20);
	Insert(l1, 20);
	Insert(l2, 5);
	Insert(l1, 5);
	Insert(l2, 10);
	Insert(l1, 7);
	Insert(l1, 3);
	Insert(l1, 100);
	Insert(l1, 11);
	int result = Compare(l1, l2);
	Print(l1);
	Print(l2);
	printf("%d", result);
	return 0;
}
