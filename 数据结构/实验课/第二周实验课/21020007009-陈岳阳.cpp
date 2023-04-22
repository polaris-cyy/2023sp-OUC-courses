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

typedef struct Node{
	double term;
	int degree;
	struct Node* next;
}*Poly, Node;

void Print(Poly p, char name) {
	//输入多项式p，以及其名称name 
	//按格式打印出多项式p 
	printf("%c(x):", name);
	p = p->next;
	while (p) {
		if (p->degree == 0) {
			printf("%.2lf", p->term);
		} else if (p->degree == 1) {
			printf("%.2lfx", p->term);
		} else {
			printf("%.2lfx^%d", p->term, p->degree);
		}
		p = p->next;
		if (p && p->term > 0) printf("+");
	}
	printf("\n");
}

void Combine(Poly p1, Poly p2, Poly& p) {
	/*	p1, p2: 待合并多项式
		p: 合并结果
		p/p1/p2每项按次数递增排序。	
	*/ 
	p1 = p1->next;
	p2 = p2->next;
	int d1, d2;
	p = (Node*)malloc(sizeof(Node));
	Poly p3;
	p3 = p;
	while (p1 && p2) {
		d1 = p1->degree;
		d2 = p2->degree;
		if (d1 < d2) {
			p3->next = (Node*)malloc(sizeof(Node));
			p3 = p3->next;
			p3->term = p1->term;
			p3->degree = d1;
			p3->next = NULL;
			p1 = p1->next;
		} else if (d1 > d2) {
			p3->next = (Node*)malloc(sizeof(Node));
			p3 = p3->next;
			p3->term = p2->term;
			p3->degree = d2;
			p3->next = NULL;
			p2 = p2->next;
		} else {
			//次数相同，合并系数。 
			if (p1->term + p2->term != 0) {
				p3->next = (Node*)malloc(sizeof(Node));
				p3 = p3->next;
				p3->term = p1->term + p2->term;
				p3->degree = p1->degree;
				p3->next = NULL;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	
	//p1或p2已完全被合并。 
	while (p1) {
		p3->next = (Node*)malloc(sizeof(Node));
		p3 = p3->next;
		p3->term = p1->term;
		p3->degree = p1->degree;
		p3->next = NULL;
		p1 = p1->next;
	}
	
	while (p2) {
		p3->next = (Node*)malloc(sizeof(Node));
		p3 = p3->next;
		p3->term = p2->term;
		p3->degree = p2->degree;
		p3->next = NULL;
		p2 = p2->next;
	}
}

void Init(Poly& p) {
	//初始化多项式p。每次输入一项的次数和系数。当次数不递增时自动终止。 
	//请不要输入0作为系数 
	p = (Node*)malloc(sizeof(Node));
	int d;
	double t;
	Poly p1 = p;
	printf("依次输入每项的次数和系数(自行确保系数不为0且次数严格递增，次数为负终止):");
	scanf("%d %lf", &d, &t);
	while (d > -1) {
		p1->next = (Node*)malloc(sizeof(Node));
		p1 = p1->next;
		p1->degree = d;
		p1->term = t;
		p1->next = NULL;
		scanf("%d %lf", &d, &t);
	}
}

int main() {
	//输入p、q，合并后结果为r
	Poly p, q, r;
	Init(p);
	Print(p, 'P');
	Init(q);
	Print(q, 'Q');
	Combine(p, q, r);
	Print(r, 'R');
	return 0;
}
