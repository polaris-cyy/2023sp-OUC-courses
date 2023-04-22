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
	//�������ʽp���Լ�������name 
	//����ʽ��ӡ������ʽp 
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
	/*	p1, p2: ���ϲ�����ʽ
		p: �ϲ����
		p/p1/p2ÿ�������������	
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
			//������ͬ���ϲ�ϵ���� 
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
	
	//p1��p2����ȫ���ϲ��� 
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
	//��ʼ������ʽp��ÿ������һ��Ĵ�����ϵ����������������ʱ�Զ���ֹ�� 
	//�벻Ҫ����0��Ϊϵ�� 
	p = (Node*)malloc(sizeof(Node));
	int d;
	double t;
	Poly p1 = p;
	printf("��������ÿ��Ĵ�����ϵ��(����ȷ��ϵ����Ϊ0�Ҵ����ϸ����������Ϊ����ֹ):");
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
	//����p��q���ϲ�����Ϊr
	Poly p, q, r;
	Init(p);
	Print(p, 'P');
	Init(q);
	Print(q, 'Q');
	Combine(p, q, r);
	Print(r, 'R');
	return 0;
}
