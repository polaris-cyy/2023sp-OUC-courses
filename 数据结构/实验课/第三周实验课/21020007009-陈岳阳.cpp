#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Node{
	int term;
	int degree;
	struct Node* next;
}*Poly, Node;

void Init(Poly &p);
void Append(Poly &p, int t, int d);
void Add(Poly &p1, Poly p2, int, int);
void Mul(Poly &p, Poly p1, Poly p2);
void Print(Poly p);
void Test();

void Print(Poly p) {
	//以多项式格式输出p 
	if (!p) return;
	p = p->next;
	while (p) {
		if ((p->term != -1 && p->term != 1) || !p->degree) printf("%d", p->term);
		if (p->term == -1) printf("-");
		if (p->degree) printf("x");
		if (p->degree && p->degree != 1 && p->degree != -1) printf("^%d", p->degree);
		p = p->next;
		if (p && p->term > 0)printf("+");
	}
	printf("\n");
}

void Init(Poly &p) {
	p = (Node*)malloc(sizeof(Node));
	p->term = 0;
	p->degree = 0;
	p->next = NULL;
}

void Clear(Poly &p) {
	while (p) {
		Poly p1;
		p1 = p->next;
		free(p);
		p = p1;
	}
}

void Append(Poly &p, int t, int d) {
	/***
	p: 待添加多项式
	t, d: 添加Node的term和degree 
	***/
	if (!t) return;
	if (!p) {
		Init(p);
		p->next = (Node*)malloc(sizeof(Node));
		p->next->term = 0;
		p->next->degree = 0;
	} else {
		Poly p1, p2;
		p1 = p;
		p2 = p1->next;
		while (p2 && p2->degree < d) {
			p1 = p2;
			p2 = p2->next;
		}
		if (p2 && p2->degree == d) {
			p2->term += t;
			if (!p2->term) {
				p1->next = p2->next;
				free(p2);
			}
		} else {
			p1->next = (Node*)malloc(sizeof(Node));
			p1 = p1->next;
			p1->degree = d;
			p1->term = t;
			p1->next = p2;
		}
	}
}

void Add(Poly &p1, Poly p2, int mul_d=0, int mul_t=1) {
	/***
	p1, p2: 被加数，加数
	mul_d, mul_t: 用于乘法的系数，默认情况表示正常相加
	结果为 p1 += p2 
	***/
	if (!p2) return;
	if (!p1) Init(p1);
	Poly ptr1, ptr2;
	ptr1 = p1;
	ptr2 = ptr1->next;
	p2 = p2->next;
	while(p2) {
		int t, d;
		t = p2->term * mul_t;
		d = p2->degree + mul_d;
		while (ptr2 && ptr2->degree < d) {
			ptr1 = ptr2;
			ptr2 = ptr2->next;
		}
		if (ptr2 && ptr2->degree == d) {
			ptr2->term += t;
			if (!ptr2->term) {
				ptr1->next = ptr2->next;
				free(ptr2);
			}
		} else {
			ptr1->next = (Node*)malloc(sizeof(Node));
			ptr1 = ptr1->next;
			ptr1->degree = d;
			ptr1->term = t;
			ptr1->next = ptr2;
		}
		p2 = p2->next;
	}	
}

void Mul(Poly &p, Poly p1, Poly p2) {
	/***
	p1, p2: 被乘数，乘数
	p储存结果。 
	***/
	Init(p);
	p1 = p1->next;
	while (p1) {
		Add(p, p2, p1->degree, p1->term);
		p1 = p1->next;
	}
}

void Test() {
	Poly p, p1, p2;
	Init(p);
	Init(p1);
	Init(p2);
	int t, d;
	t = 0, d = 0;
	printf("输入多项式P(x)的系数与次数(输入-1 -1以终止)：");
	while (d >= 0) {
		scanf("%d %d", &t, &d);
		if (d >= 0)Append(p1, t, d);
	}
	t = 0, d = 0;
	printf("输入多项式Q(x)的系数与次数(输入-1 -1以终止)：");
	while (d >= 0) {
		scanf("%d %d", &t, &d);
		if (d >= 0) Append(p2, t, d);
	}
	Mul(p, p1, p2);
	printf("P(x)=");
	Print(p1);
	printf("Q(x)=");
	Print(p2);
	printf("P*Q(x)=");
	Print(p);
}

int main() {
	Test();
	return 0;
}
