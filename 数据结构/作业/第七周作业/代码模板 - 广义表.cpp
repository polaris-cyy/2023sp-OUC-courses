#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctype.h>

#define AtomType char

using namespace std;

typedef enum {ATOM, LIST} ElemTag;

typedef struct GLNode{
	ElemTag tag;
	union {
		AtomType atom;
		struct {
			struct GLNode *hp, *tp;
		}ptr;
	};
}*GList;

bool InitGList(GList& L);	//ok
char* ReadFirst(GList& L, char s[]);//ok
char* ReadRest(GList& L, char s[]);	//ok
bool DestroyGList(GList& L);	//ok
void CopyGList(GList& L, GList T);	//ok
int  GListLength(GList L);	//ok
int  GListDepth(GList L);	//ok
bool GListEmpty(GList L);	//ditto GLL
GList GetHead(GList L);	//ok
GList GetTail(GList L);	//ok
bool ShowGList(GList L);//ok
void Test();	//测试代码 

bool InitGList(GList& L) {
	L = NULL;
}

char* ReadFirst(GList& L, char s[]) {
	//默认首次传入的s合法 
	while (*s == ' ' or *s == ',') s++;
	if (*s)
	{
		char first = *s;
		s++;
		//如果是 '(' 开头，说明即将生成子表 
		if (first == '(') {
			s = ReadRest(L, s);
		} else if (isalpha(first)) {
			//如果是atom开头，说明这是一个ATOM，且ReadFirst被ReadRest调用 
			L->tag = ATOM;
			L->atom = first;
		}
	}
	return s;
}

char* ReadRest(GList& L, char s[]) {
	while (*s == ' ' or *s == ',') s++;
	if (*s == ')') {
		//表结束 
		s++;
		L = NULL;
	} else {
		L = (GList)malloc(sizeof(GLNode));
		L->tag = LIST;
		L->ptr.hp = (GList)malloc(sizeof(GLNode));
		L->ptr.tp = (GList)malloc(sizeof(GLNode));
		//首先找到代表hp的一段(开头只能是atom或'(' )，剩下的是tp 
		s = ReadFirst(L->ptr.hp, s);
		//这个函数应该叫ReadTail更合适 
		s = ReadRest(L->ptr.tp, s);
	}
	return s;
}

bool DestroyGList(GList& L) {
	if (L) {
		if (L->tag == LIST){
			if (L->ptr.hp) DestroyGList(L->ptr.hp);
			if (L->ptr.tp) DestroyGList(L->ptr.tp);
		}
		free(L);
		L = NULL;
	}
	return true;
}

void CopyGList(GList& L, GList T) {
	if (!T) {
		L = NULL;
		return;
	}
	if (L) DestroyGList(L);	
	L = (GList)malloc(sizeof(GLNode));
	
	if (T->tag == ATOM) {
		L->tag = ATOM;
		L->atom = T->atom;
	} else {
		L->tag = LIST;
		L->ptr.hp = (GList)malloc(sizeof(GLNode));
		L->ptr.tp = (GList)malloc(sizeof(GLNode));
		CopyGList(L->ptr.hp, T->ptr.hp);
		CopyGList(L->ptr.tp, T->ptr.tp);
	}
}

int GListLength(GList L) {
	if (!L || (L->tag == ATOM)) return 0;  
	int l = 0;
	GList cur;
	for (l = 0, cur = L; cur; cur = cur->ptr.tp, ++l);
	return l;
}

//习题5.30 
int GListDepth(GList L) {
	if (!L) return 1;	//空表 
	if (L->tag == ATOM) return 0;	//atom类型 
	int m = 0;
	GList cur;
	/***
	E.g. L = (a, (b, c), (d, (e, f)))
	第一次, depth = GListDepth(a) = 0, cur = ((b, c), (d, (e, f)));
	第二次, depth = GListDepth((b, c)), cur = ((d, (e, f)))
	第三次, depth = GListDepth((d, (e, f))), cur = NULL
	可以看出, 该循环依次取出L中每一项, 计算depth, 取最大值 
	***/
	for (cur = L, m = 0; cur != NULL; cur = cur->ptr.tp) {
		int depth = GListDepth(cur->ptr.hp);
		m = depth > m ? depth : m;
	}
	return m + 1;
}

bool GListEmpty(GList L) {
	return GListLength(L) == 0;
}

GList GetHead(GList L) {
	if (!L || L->tag == ATOM) return NULL;
	return L->ptr.hp;
}

GList GetTail(GList L) {
	if (!L || L->tag == ATOM) return NULL;
	return L->ptr.tp;
}

bool ShowGList(GList L) {
	if (!L)  {
		cout << "()";
		return false;
	}
	if (L->tag == ATOM) {
		cout << L->atom;
		return true;
	}
	GList tp;
	cout << "(";
	for (tp = L; tp; ) {
		ShowGList(tp->ptr.hp);
		tp = tp->ptr.tp;
		if (tp) cout << ",";
	}
	cout << ")";
	return true;
}

//习题5.32 
bool Equal(GList L1, GList L2) {
	if (!L1 && !L2) return true;	//都为空 
	if (!L1 || !L2) return false;
	//都不空
	//类型不同 
	if (L1->tag != L2->tag) return false;
	//都是ATOM 
	if (L1->tag == ATOM && L2->tag == ATOM) return L1->atom == L2->atom;
	//都是LIST 
	return Equal(GetHead(L1), GetHead(L2)) && Equal(GetTail(L1), GetTail(L2));
}

//习题5.33 
void Traverse(GList L, int depth=0) {
	if (!L) return;
	if (L->tag == ATOM) {
		cout << L->atom << ":" << depth << endl;
	} else {
		GList tp;
		for (tp = L; tp; tp = tp->ptr.tp) {
			Traverse(tp->ptr.hp, depth+1);
		}
	}
}

//习题5.37 
void TraverseDelete(GList& L, AtomType x) {
	if (!L) return;
	GList tp;
	for (tp = L; tp; tp = tp->ptr.tp) {
		GList hp = tp->ptr.hp;
		if (!hp) continue;
		if (hp->tag == ATOM) {
			if (hp->atom == x) {
				free(tp->ptr.hp);
				tp->ptr.hp = NULL;
			}
		} else {
			TraverseDelete(hp, x);
		}
	}
}
//习题5.38 
void TheLthLayerAtom(GList L, int l, int dep=1) {
	if (!L) return;
	GList tp;
	for (tp = L; tp; tp = tp->ptr.tp) {
		if (!tp->ptr.hp) continue;
		if (tp->ptr.hp->tag == ATOM) {
			if (dep == l) {
				cout << tp->ptr.hp->atom;
			}
		} else {
			TheLthLayerAtom(tp->ptr.hp, l, dep+1);
		}
	}
}


void Test() {
	//char str[50] = "(a,(b,c),(d,(e,f)))";
	char str[50] = "(a,(b,c),(c,(c,d,c,(c,c),d)), ())";
	GList L;
	InitGList(L);
	ReadFirst(L, str);
	cout << "Depth: " << GListDepth(L) << endl;
	TheLthLayerAtom(L, 3);
}

int main() {
	Test();
	return 0;
}
