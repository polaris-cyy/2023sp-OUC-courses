#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Elemtype int
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

void Init(SqList& s) {
	s.length = 0;
	s.size = MAXSIZE;
	s.elem = (Elemtype*)malloc(MAXSIZE * sizeof(Elemtype));
}

void Push(SqList& s, Elemtype x) {
	if (s.length == s.size) {
		s.size += SIZE_INCREMENT;
		s.elem = (Elemtype*)calloc(s.size, sizeof(Elemtype));
	}
	s.elem[s.length++] = x;
}

void Print(SqList s) {
	int i;
	i = 0;
	while (i < s.length) printf("%d ", s.elem[i++]);
}

int SqMaxElem(SqList L, int k, int m) {
	if (k == 0) m = L.elem[0];
	if (L.length == k + 1) {
		return m;
	} else {
		m = m > L.elem[k] ? m : L.elem[k];
		return SqMaxElem(L, k+1, m);
	}
} 

int SqSum(SqList L, int k, int sum) {
	if (k == 0) sum = 0;
	sum += L.elem[k];
	if (L.length == k + 1)
		return sum;
	return SqSum(L, k+1, sum);
}


int main() {
	SqList L;
	Init(L);
	Push(L, 1);
	Push(L, 2);
	Push(L, 7);
	Push(L, 3);
	Push(L, 6);
	Print(L);
	printf("\nMax: %d", SqMaxElem(L, 0, 0));
	printf("\nSum: %d", SqSum(L, 0, 0));
}
