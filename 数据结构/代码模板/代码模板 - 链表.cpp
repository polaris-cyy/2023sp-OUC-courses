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

typedef struct LinkList{
	int elem;
	struct LinkList* next;
}*Head, Node;

void Init(Head& h) {
	h = (Node*)malloc(sizeof(Node));
	h->next = NULL;
	Head h1;
	h1 = h;
	int e;
	e = 0;
	scanf("%d", &e);
	while (e) {
		h1->next = (Node*)malloc(sizeof(Node));
		h1 = h1->next;
		h1->elem = e;
		h1->next = NULL;
		scanf("%d", &e);
	}
}

void RangeDelete(int mink, int maxk, Head& h) {
	Head h1, h2;
	h1 = h;
	h2 = h1->next;
	while (h2) {
		if (h2->elem > mink && h2->elem < maxk) {
			h1->next = h2->next;
			free(h2);
			h2 = h1->next;
		} else {
			h1 = h2;
			h2 = h2->next;
		}
	}
}

void Inverse(Head& h) {
	Head h1, h2, h3;
	h1 = h;
	h2 = h1->next;
	while (h2) {
		h3 = h2;
		h2 = h3->next;
		h3->next = h1;
		h1 = h3;
	}
	if (h->next) {
		h->next->next = NULL;
		h->next = h1;
	}
}

void Combine(Head a, Head b, Head& c) {
	c = (Node*)malloc(sizeof(Node));
	Head temp;
	temp = c;
	a = a->next;
	b = b->next;
	while (a && b) {
		if (a->elem < b->elem) {
			temp->next = a;
			a = a->next;
			temp = temp->next;
		} else {
			temp->next = b;
			b = b->next;
			temp = temp->next;
		}
	}
	if (a) {
		temp->next = a;
	}
	if (b) {
		temp->next = b;
	}
}

void InverseCombine(Head a, Head b, Head& c) {
	Combine(a, b, c);
	Inverse(c);
}

void Print(Head h) {
	h = h->next;
	while (h) {
		printf("%d ", h->elem);
		h = h->next;
	}
	printf("\n");
}

int main() {
	Head h;
	Init(h);
	Print(h);
//	RangeDelete(3, 7, h);	
//	Inverse(h);
	Head h1, h2;
	Init(h1);
	Init(h2);
	InverseCombine(h1, h2, h);
	Print(h);
	return 0;
}
