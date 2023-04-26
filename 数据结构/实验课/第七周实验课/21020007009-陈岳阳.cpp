#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

FILE*fp;

const int N = 9;

//KMP模板，无法使用，因为主串太长，无法一次读取 
int KMP(char M[], char T[], int pos = 0) {
	int len_M = strlen(M), len_T = strlen(T);
	if (pos + len_T > len_M) return -1;
	
	int next[len_T];
	next[0] = -1;
	int i = 0, j = 1;
	while (j < len_T) {
		if (T[j] == T[i]) {
			next[j] = next[i];
		} else {
			next[j] = i;
			while (i >= 0 && T[i] != T[j]) {
				i = next[i];
			}
		}
		i++;
		j++;
	}
	
	
	i = 0, j = pos;
	while (j + len_T <= len_M) {
		if (M[i+j] == T[i]) {
			if (++i == len_T) return j; 
		} else {
			j += i - next[i];
			i = next[i]; 
			if (i < 0) i++;
		}
	}
	return -1;
}

int BirthInPi(char Birth[], char path[], int pos = 0) {
	int NumberOfDigits = 2e8;
	char PI[N+1];
	if (!(fp = fopen(path, "r"))) {
		cout << "No such file in path ";
		for (int i = 0; i < strlen(path); ++i) {
			cout << path[i];
		}
		exit(0);
	}
	
	int next[strlen(Birth)];
	next[0] = -1;
	int i = 0, j = 1;
	while (j < strlen(Birth)) {
		if (Birth[i] == Birth[j]) {
			next[j] = next[i];
		} else {
			next[j] = i;
			while (i >= 0 && Birth[i] != Birth[j]) {
				i = next[i];
			}
		}
		i++;
		j++;
	}
	
	for (int i = 0; i < N; ++i) {
		PI[i] = fgetc(fp);
	}
	
	i = 0, j = pos;
	int prev = j;
	int len_B = strlen(Birth);
	while (j + len_B < NumberOfDigits) {
		if (PI[(j+i)%N] == Birth[i]) {
			if (++i == len_B) return j+1;
		} else {
			j += i - next[i];
			i = next[i];
			if (i < 0) i++;
			while (prev < j) {
				PI[prev%N] = fgetc(fp);
				prev++;
			}
		}
	}
	
	
	
	return -1;
}

void Decorator(char Birth[], char path[]) {
	int len = strlen(Birth);
	cout << "你的生日:";
	for (int i = 0; i < len; ++i) {
		cout << Birth[i];
	}
	cout << " 在圆周率中的位数为: " << BirthInPi(Birth, path) << endl; 
}


int main() {
	char MyBirth[10] = "20030213";
	char HerBirth[10]= "20030820";
	char path[1000] = "C:\\Users\\86139\\Desktop\\PI.txt";
	Decorator(MyBirth, path);
	Decorator(HerBirth, path);
	return 0;
}
