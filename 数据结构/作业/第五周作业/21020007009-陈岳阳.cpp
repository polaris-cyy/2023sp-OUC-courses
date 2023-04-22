#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct{
	char *ch;
	int length;
}HString;//struct HString. Length counts the number of elements ch contains

void Assign(HString &T, char *c){
	int i=0;
	while(c[i++]);
	T.ch = (char*)malloc(i * sizeof(char));
	i = 0;
	while(T.ch[i] = c[i]){
		i++;
	}
	T.length = i;
}//Assign T with char *c

int Index(HString S, HString T, int pos){
	if(T.length + pos >= S.length) return -1;// return -1 when T.ch is too long
	//get T's next array first
	int next[T.length];
	next[0] = -1;
	int i = 0, j = -1;
	while(i < T.length){
		if(j == -1 || T.ch[i] == T.ch[j]){
			i++; j++;
			if(T.ch[i] != T.ch[j]){
				next[i] = j;
			}else{
				next[i] = next[j];
			}
		}
		else{
			j = next[j];
		}
	}
    //create next array
	i = pos; j = 0;
	while(i + T.length <= S.length){
		if(T.ch[j] != S.ch[i+j]){
			i += j - next[j];
			j = next[j];
			if(j == -1){
			j++;
			}
		}else{
			j++;
			if(j == T.length){
				return i;
			}
		}
		//T.ch first appears in S[i]
	}
	return -1;//cant find such an array T.ch
}//Index the first T in S after the pos th element

int main(){
	char a[] = "to";
	char b[] = "be or not to be is a question ";
	HString A, B;
	Assign(A, a);
	Assign(B, b);
	int i = Index(B, A, 0);
	printf("%d", i);
	return 0;
}
