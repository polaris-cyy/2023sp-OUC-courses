#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define MAXSIZE 100
#define INCREMENT 10
#define Elemtype char
#define Status int
#define OK 1
#define Error -1

typedef struct Stack {
	Elemtype* base;
	Elemtype* top;
	int size;
}Stack;

bool IsEmpty(Stack s);

void Init(Stack& s) {
	s.base = (Elemtype*)malloc(MAXSIZE * sizeof(Elemtype));
	s.size = MAXSIZE;
	s.top = s.base;
}


void Push(Stack& s, Elemtype x) {
	if (s.top - s.base == s.size ) {
		s.base = (Elemtype*)calloc(s.size + INCREMENT, sizeof(Elemtype));
		s.top = s.base + s.size;
		s.size += INCREMENT;
	}
	*s.top++ = x;
}

void Pop(Stack& s, Elemtype& x) {
	if (IsEmpty(s)) return;
	x = *--s.top;
}

void GetTop(Stack s, Elemtype& x) {
	if (IsEmpty(s)) return;
	x = *(s.top-1);
}

bool IsEmpty(Stack s) {
	return s.top == s.base;
}

bool InOp(char c) {
	return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
}

//运算符优先级 
int Precedence(char op1, char op2) {
	if ((op1 == '+') || (op1 == '-')) {
		if ((op2 == '+') || (op2 == '-')) {
			return 0;
		} else {
			return -1;
		}
	} else {
		if ((op2 == '*' || op2 == '/')) {
			return 0;
		} else {
			return 1;
		}
	}
}

Status Poland(Stack &s) {
	printf("输入一个正常表达式，以@结尾外，只出现字母和四则运算符：");
	Stack op, result;
	Init(op);
	Init(result);
	char c = '\0', top;
	int counter = 0;
	while (c != '@') {
		scanf("%c", &c);
		if (c == '@') break;
		if (isalpha(c)) {
			Push(result, c);
			counter++;
		} else if(InOp(c)) {
			GetTop(op, top);
			while (!IsEmpty(op) and Precedence(c, top) <= 0) {
				Pop(op, top);
				Push(result, top);
				GetTop(op, top);
			}
			counter--;
			Push(op, c);
		} else {
			return Error;
		}
		if (counter != 0 && counter != 1) return Error;
	}
	if (counter != 1) return Error; 
	while (!IsEmpty(op)) {
		Pop(op, top);
		Push(result, top);
	}
	while (!IsEmpty(result)) {
		Pop(result, c);
		Push(s, c);
	}
	return OK;
}

Status PrintPoland() {
	Stack s;
	Init(s);
	int result = Poland(s);
	if (result == OK) {
		while (!IsEmpty(s)) {
			char c;
			Pop(s, c);
			printf("%c ", c);
		}
	} else {
		printf("非正常表达式，可能原因：\n\t1.存在数字\n\t2.未以@结尾\n\t3.表达式形式不正确\n");
	}
	return result;
}

int main() {
	PrintPoland();
	return 0;
}
