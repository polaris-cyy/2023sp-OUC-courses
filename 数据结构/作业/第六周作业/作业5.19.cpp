#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdarg.h>

using namespace std;

#define Status int
#define OK 1
#define ERROR -1
#define UNDERFLOW -2
#define Elemtype int
#define MAX_ARRAY_DIM 8

int off, result;
va_list ap;

typedef struct {
	Elemtype *base;
	int dim;
	int *bounds;
	int *constants;
}Array;

Status InitArray(Array &A, int dim, ...);

Status DestroyArray(Array &A);

Status Value(Array A, Elemtype &e, ...);

Status Assign(Array &A, Elemtype e, ...);

Status InitArray(Array &A, int dim, ...) {
	if (dim < 1 || dim > MAX_ARRAY_DIM) return ERROR;
	A.dim = dim;
	if (!(A.bounds = (int*)malloc(sizeof(int)))) return ERROR;
	int elemtotal = 1;
	
	va_start(ap, dim);
	
	for (int i = 0; i < dim; ++i) {
		A.bounds[i] = va_arg(ap, int);
		if (A.bounds[i] < 0) return ERROR;
		elemtotal *= A.bounds[i];
	}
	va_end(ap);
	A.base = (Elemtype*)malloc(dim * sizeof(Elemtype));
	if (!A.base) return ERROR;
	A.constants = (int*)malloc(dim * sizeof(int));
	if (!A.constants) return ERROR;
	A.constants[dim-1] = 1;
	for (int i = dim - 2; i >= 0; --i) {
		A.constants[i] = A.bounds[i+1] * A.constants[i+1];
	}
	return OK;
}

Status DestroyArray(Array &A) {
	if (!A.base) return ERROR;
	free(A.base);	A.base = NULL;
	if (!A.bounds) return ERROR;
	free(A.bounds);	A.bounds = NULL;
	if (!A.constants) return ERROR;
	free(A.constants);	A.constants = NULL;
	return OK;
}

Status Locate(Array A, va_list ap, int &off) {
	off = 0;
	for (int i = 0; i < A.dim; ++i) {
		int ind = va_arg(ap, int);
		if (ind < 0 || ind >= A.bounds[i]) return ERROR;
		off += A.constants[i] * ind;
	}
	return OK;
}

Status Value(Array A, Elemtype &e, ...) {
	va_start(ap, e);
	if ((result = Locate(A, ap, off)) <= 0) return result;
	e = *(A.base + off);
	return OK;
}

Status Assign(Array &A, Elemtype e, ...) {
	va_start(ap, e);
	if ((result = Locate(A, ap, off)) <= 0) return result;
	*(A.base + off) = e;
	return OK;
}

typedef struct {
	int x, y;
}Point;

Point* GetSaddlePoint(Matrix mat, int m, int n) {
	Point ans[m*n]; //马鞍点构成的数组 
	int row_min[m], col_max[n]; //存储每行最小值以及每列最大值 
	int temp;
	//每行最小值 
	for (int i = 0; i < m; ++i) {
		temp = mat[i][0];
		for (int j = 1; j < n; ++j)
			temp = min(temp, mat[i][j]);
		row_min[i] = temp;
	}
	//每列最大值 
	for (int j = 0; j < n; ++j) {
		temp = mat[0][j];
		for (int i = 1; i < m; ++i) 
			temp = max(temp, mat[i][j]);
		col_max[j] = temp;
	}
	
	//逐个检查 
	int k = 0;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (mat[i][j] == row_min[i] && mat[i][j] == col_max[j]) {
				ans[k].x = i;
				ans[k].y = j;
				k++;
			}
		}
	}
	
	return ans;
} 
