#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 100
#define INCREMENT 10
#define Elemtype char

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

bool IsParlindrome() {
	int i, j;
	char s[100], c;
	Stack stack;
	Init(stack);
	scanf("%c", &c);
	while (c != '@') {
		s[i] = c;
		Push(stack, c);
		scanf("%c", &c);
		i++;
	}
	getchar();	//»Ø³µ 
	i = 0;
	while (!IsEmpty(stack)) {
		Pop(stack, c);
		if (c != s[i]) return false;
		i++;
	}
	return true;
} 

int main() {
	for(;;) {
		int result = IsParlindrome();
		printf("%d\n", result);
	}
	return 0;
}
