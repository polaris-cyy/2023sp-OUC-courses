#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int KMP_Partition() {
	return 0;
}

int KMP(char* s, char* m, int len_s, int len_m) {
	int* next;
	next = (int*)malloc(len_s * sizeof(int));
	
	next[0] = -1;
	int i, j;
	i = 0, j = 1;
	while (j < len_s) {
		if (s[i] != s[j]) next[j] = i;
		else next[j] = next[i];
		while (i != -1 && s[i] != s[j]) i = next[i];
		i++; j++;
	}
	
	i = 0, j = 0;
	while (i + len_s <= len_m) {
		if (s[j] == m[i+j]) {
			if (++j == len_s) {
				free(next);
				return i;
			}
		} else {
			i = i + j - next[j];
			j = next[j] < 0 ? 0 : next[j];
		}
	}
}

int main() {
	char* s = (char*)malloc(100 * sizeof(char));
	s = "baaabaacbaab";
	char* m = (char*)malloc(10 * sizeof(char));
	m = "acbaa";
	printf("%d", KMP(m, s, 3, 10));
}
