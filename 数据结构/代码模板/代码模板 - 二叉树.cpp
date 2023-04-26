#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#define DataType char

using namespace std;

FILE *fp;

typedef struct Node{
	struct Node *lch;
	DataType data;
	struct Node *rch;
}*BT;


void InitBT(BT &T);
void DestroyBT(BT &T);
void CreateBT(BT &T, char s[], int);
void ClearBT(BT &T);
bool BTEmpty(BT &T);
int  BTDepth(BT &T);
int CountLeaf(BT &T);
void KthNode(BT T, int k);
void Counting(BT T, int k, int &n);

void PreOrderTraverse(BT T);
void InOrderTraverse(BT T);
void PostOrderTraverse(BT T);

void InitBT(BT &T) {
	T = (BT)malloc(sizeof(Node));
	T->lch = T->rch = NULL;
	T->data = 0;
}

void DestroyBT(BT &T) {
	if (T == NULL) return;
	DestroyBT(T->lch);
	DestroyBT(T->rch);
	free(T);
	T = NULL;
}

void CreateBT(BT &T, char s[], int cnt=0) {
	int len = strlen(s);
	if (cnt >= strlen(s) || s[cnt] == ' ') {
		T = NULL;
	} else {
		InitBT(T);
		T->data = (s[cnt]);
		CreateBT(T->lch, s, cnt*2+1);
		CreateBT(T->rch, s, cnt*2+2);
	}
}

void ClearBT(BT &T) {
	DestroyBT(T->lch);
	DestroyBT(T->rch);
	T->data = '\0';
}


bool BTEmpty(BT &T) {return T == NULL;}

int BTDepth(BT &T) {
	if (!T) return 0;
	int ld, rd;
	ld = BTDepth(T->lch);
	rd = BTDepth(T->rch);
	return ld > rd ? ld+1 : rd+1;
}

//习题6.42 
int CountLeaf(BT &T) {
	if (!T) return 0;
	if (!T->lch && !T->rch) return 1;
	return CountLeaf(T->lch) + CountLeaf(T->rch);
}

int CountNode(BT &T) {
	if (!T) return 0;
	return CountNode(T->lch) + CountNode(T->rch) + 1;
}

void PreOrderTraverse(BT T) {
	if (!T) return;
	cout << T->data;
	PreOrderTraverse(T->lch);
	PreOrderTraverse(T->rch);
}

void InOrderTraverse(BT T) {
	if (!T) return;
	InOrderTraverse(T->lch);
	cout << T->data;
	InOrderTraverse(T->rch);
}

void PostOrderTraverse(BT T) {
	if (!T) return;
	PostOrderTraverse(T->lch);
	PostOrderTraverse(T->rch);
	cout << T->data;
}

//习题6.36 
bool SimilarBT(BT T1, BT T2) {
	if (!T1 && !T2) return true;
	if (!T1 || !T2) return false;
	return SimilarBT(T1->lch, T2->lch) && SimilarBT(T1->rch, T2->rch);
}

//习题6.41 
void KthNode(BT T, int k) {
	if (CountNode(T) < k) cout << "结点数不足" << k << "个"<< endl;
	else {
		int n = 1;
		Counting(T, k, n);
	}  
}

void Counting(BT T, int k, int &n) {
	if (!T) return;
	if (n == k) {
		cout << "前序遍历第" << k << "个元素: " << T->data << endl; 
	}
	n++;
	Counting(T->lch, k, n);
	Counting(T->rch, k, n);
	
}

//习题6.43 
void SwapBT(BT &T) {
	if (!T) return;
	BT temp = T->lch;
	T->lch = T->rch;
	T->rch = temp;
	SwapBT(T->lch);
	SwapBT(T->rch);
}

void Test() {
	char s[20] = "abcd efgh    k";
	char s1[20]= "ab cd";
	char s2[20]= "ac bd";
	BT T, T1, T2;
	InitBT(T);
	InitBT(T1);
	InitBT(T2);
	CreateBT(T, s);
	CreateBT(T1, s1);
	CreateBT(T2, s2);
//	cout << SimilarBT(T1, T2) << endl;
//	cout << BTDepth(T) << endl;
//	cout << CountLeaf(T) << endl;
//	cout << CountNode(T) << endl;
	cout << "前序遍历: "; 
	PreOrderTraverse(T);
	cout << endl << "中序遍历: ";
	InOrderTraverse(T);
	SwapBT(T);
	cout << endl << "交换后\n前序遍历: "; 
	PreOrderTraverse(T);
	cout << endl << "中序遍历: ";
	InOrderTraverse(T);
//	cout << endl;
//	for (int i = 0; i < CountNode(T); ++i) {
//		KthNode(T, i+1);
//	}
}

int main() {
	Test();
	return 0;
} 
