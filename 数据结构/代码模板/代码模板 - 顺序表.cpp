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

void Inverse(SqList& s) {
	int i, j, temp;
	i = 0;
	j = s.length - 1;
	while (i < j) {
		temp = s.elem[i];
		s.elem[i] = s.elem[j];
		s.elem[j] = temp;
		i++;
		j--;
	}
} 

void Print(SqList s) {
	int i;
	i = 0;
	while (i < s.length) printf("%d ", s.elem[i++]);
}

int main() {
	int i;
	i = 0;
	SqList s;
	Init(s);
	for (i = 0; i < 10; ++i) {
		Push(s, i);
	}
	Inverse(s);
	Print(s);
	return 0;
}
