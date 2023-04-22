#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAXSIZE 32768

int arr[MAXSIZE];
int temp[MAXSIZE];
int i, j, k;

void BubbleSort(int a[], int n)
{
	int i, j, temp;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}

void QuickSort(int a[], int left, int right)
{
	if (left >= right)   return;
	int i = left, j = right, key = a[left];
	while (i < j) {
		while (i < j && key <= a[j]) j--;
		a[i] = a[j];
		while (i < j && key >= a[i]) i++;
		a[j] = a[i];
	}
	a[i] = key;
	QuickSort(a, left, i - 1);
	QuickSort(a, i + 1, right);
}

void BubbleTimer(int a[], int n) {
	clock_t start, end;
	for (i = 0; i < MAXSIZE; ++i) {
		temp[i] = a[i];
	}
	start = clock();
	BubbleSort(temp, n);
	end = clock();
	printf("冒泡排序时间: %dms\n", end-start);
	printf("排序结果: ");
	for (i = 0; i < MAXSIZE; ++i) {
		printf("%d ", temp[i]);
	} 
	printf("\n");
}

void QSTimer(int a[], int left, int right) {
	clock_t start, end;
	for (i = 0; i < MAXSIZE; ++i) {
		temp[i] = a[i];
	}
	start = clock();
	QuickSort(temp, left, right);
	end = clock();
	printf("快速排序时间: %dms\n", end-start);
	printf("排序结果: ");
	for (i = 0; i < MAXSIZE; ++i) {
		printf("%d ", temp[i]);
	} 
	printf("\n");
}

int main() {
	srand((unsigned)time(NULL));
	for (i = 0; i < MAXSIZE; ++i) {
		arr[i] = rand();
	}
	QSTimer(arr, 0, MAXSIZE - 1);
	BubbleTimer(arr, MAXSIZE);
	return 0;
}
