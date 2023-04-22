#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 100
#define INCREMENT 10
#define Elemtype char
#define Status int
#define Error -1
#define OK 1

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

void Clear(Stack& s) {
	if (s.base) free(s.base);
	if (s.top) free(s.top);
}

void Push(Stack& s, Elemtype x) {
	if (s.top - s.base == s.size ) {
		s.base = (Elemtype*)calloc(s.size + INCREMENT, sizeof(Elemtype));
		s.top = s.base + s.size;
		s.size += INCREMENT;
	}
	*s.top++ = x;
}

Status Pop(Stack& s, Elemtype& x) {
	if (IsEmpty(s)) return Error;
	x = *--s.top;
	return OK;
}

Status GetTop(Stack s, Elemtype& x) {
	if (IsEmpty(s)) return Error;
	x = *(s.top-1);
	return OK;
}

bool IsEmpty(Stack s) {
	return s.top == s.base;
}

//ื๗าต3.17 
bool IsInverse() {
	Stack s;
	Init(s);
	char c;
	scanf("%c", &c);
	while (c != '&') {
		Push(s, c);
		scanf("%c", &c);
	}
	scanf("%c", &c);
	while (c != '@') {
		char n;
		if (IsEmpty(s)) return false;
		Pop(s, n);
		if (n != c) return false;
		scanf("%c", &c);
	}
	return true;
}

bool In(Elemtype* set, Elemtype c, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		if (set[i] == c) return true;
	}
	return false;
}

bool Partition(char a, char b) {
	if (a == '(')
		return b == ')';
	if (a == '[')
		return b == ']';
	if (a == '{')
		return b == '}';
	return false;
}

bool BracketPartition() {
	char c;
	char brackets[10] = "()[]{}";
	char left_brackets[5] = "([{";
	scanf("%c", &c);
	Stack s;
	Init(s);
	while (In(brackets, c, 6)) {
		if (In(left_brackets, c, 3)) {
			Push(s, c);
		} else {
			if (IsEmpty(s)) return false;
			char top;
			Pop(s, top);
			if (!Partition(top, c)) return false;
		}
		scanf("%c", &c);
	}
	return IsEmpty(s);
}

int main() {
	Stack s;
	Init(s);
	bool result = BracketPartition();
	printf("%d\n", result);
	result = BracketPartition();
	printf("%d\n", result);
	return 0;
}
