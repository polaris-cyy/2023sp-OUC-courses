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
	if (Length(q)+1 == q.size) return Error; //满 
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
	Init(q, 3);
	int test_result;
	while (1) {
		int c;
		printf("1.入队 2.出队 3.首元 4.长度 5.空\n");
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
				if (Front(q, c) != Error) printf("首元：%d\n", c);
				else printf("当前为空\n");
				break;
			case 4:
				printf("长度：%d\n", Length(q));
				break;
			case 5:
				printf("是否为空：%d\n", IsEmpty(q));
				break;
		}
	}
}

void Fibonacci(int k, int max) {
	Q fib;
	Init(fib, k+1);
	Push(fib, 1);
	printf("第0项：1\n");
	int sum = 1, i = 1;
	while (i < k){
		Push(fib, sum);
		printf("第%d项：%d\n", i++, sum);
		sum <<= 1;
	}
	while (sum <= max) {
		int front;
		Pop(fib, front);
		Push(fib, sum);
		printf("第%d项：%d\n", i++, sum);
		sum = 2 * sum - front;
	}
} 

int main() {
	int k, max;
	printf("输入k，max：");
	scanf("%d %d", &k, &max);
	Fibonacci(k, max);
	return 0;
}
