#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define Elemtype int
#define OK 1
#define True 1
#define False 0
#define Error 0
#define MAXSIZE 100
#define SIZE_INCREMENT 10

typedef struct LinkList{
	char elem;
	struct LinkList* next;
}*Head, Node;

void Init(Head& h) {
	h = (Node*)malloc(sizeof(Node));
	h->next = NULL;
	h->elem = 0;
}

void Circle(Head& h) {
	Head h1;
	h1 = h;
	while (h1->next) {
		h1 = h1->next;
	}	
	h1->next = h;
}

void Append(Head& h, Head& n) {
	Head h1;
	h1 = h;
	while (h1->next) h1 = h1->next;
	h1->next = n;
	n->next = NULL;
}

void Divide(Head h, Head& s1, Head& s2, Head& s3) {
	Init(s1);
	Init(s2);
	Init(s3);
	h = h->next;
	while (h) {
		Head h1;
		h1 = h->next;
		if (isdigit(h->elem)) {
			Append(s1, h);
		} else if (isalpha(h->elem)) {
			Append(s2, h);
		} else {
			Append(s3, h);
		}
		h = h1;
	}
	Circle(s1);
	Circle(s2);
	Circle(s3);
}

void Print(Head h) {
	Head h1;
	h1 = h->next;
	while (h1 && h1->elem) {
		printf("%c ", h1->elem);
		h1 = h1->next;
	}
	printf("\n");
}

int main() {
	Head h, h1, h2, h3, s1, s2, s3;
	Init(h);
	int i;
	for (i = 0; i < 10; ++i) {
		char elem;
		scanf("%c", &elem);
		Init(h1);
		h1->elem = elem;
		Append(h, h1);
	} 
	Print(h);
	Divide(h, s1, s2, s3);
	Print(s1);
	Print(s2);
	Print(s3);
	return 0;
}
