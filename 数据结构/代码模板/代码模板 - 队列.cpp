#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 100
#define INCREMENT 10
#define Elemtype int
#define Status int
#define Error -1
#define OK 1

typedef struct Queue{
	Elemtype *elem;
	int front, rear;
	int size;
	int counter;
}Q; 

void Init(Q &q, int);

bool IsEmpty(Q q);

Status Front(Q q, Elemtype &x);

Status Push(Q &q, Elemtype x);

Status Pop(Q &q, Elemtype &x);

int Length(Q q);

void Init(Q &q, int size=MAXSIZE+1) {
	q.elem = (Elemtype*)malloc(size * sizeof(Elemtype));
	q.front = q.rear = 0;
	q.size = size;
}

bool IsEmpty(Q q) {
	return q.front == q.rear;
}

int Length(Q q) {
	int length = q.rear - q.front;
	return (length >= 0) ? length : length+q.size;
}

Status Front(Q q, Elemtype &x) {
	if (IsEmpty(q)) return Error;
	x = q.elem[q.front];
}

Status Push(Q &q, Elemtype x) {
	if (Length(q)+1 == q.size) return Error; //�� 
	q.elem[q.rear++] = x;
	q.rear %= q.size;
	return OK;
}

Status Pop(Q &q, Elemtype &x) {
	if (IsEmpty(q)) return Error;
	x = q.elem[q.front++];
	q.front %= q.size;
	return OK;
}

void Test() {
	Q q;
	Init(q, 10);
	int test_result;
	while (1) {
		int c;
		printf("1.��� 2.���� 3.��Ԫ 4.���� 5.��\n");
		scanf("%d", &c);
		switch(c){
			case 1:
				scanf("%d", &c);
				Push(q, c);
				break;
			case 2:
				Pop(q, c);
				break;
			case 3:
				if (Front(q, c) != Error) printf("��Ԫ��%d\n", c);
				else printf("��ǰΪ��\n");
				break;
			case 4:
				printf("���ȣ�%d\n", Length(q));
				break;
			case 5:
				printf("�Ƿ�Ϊ�գ�%d\n", IsEmpty(q));
				break;
		}
	}
}

int main() {
	Test();
	return 0;
}
