#include <iostream>
#include <stdarg.h>
using namespace std;

int sum(int num, ...) {
	va_list ap;
	int cur = 0;
	int result = 0;
	va_start(ap, num);
	for (int i = 0; i < num; ++i)
		result += va_arg(ap, int);
	va_end(ap);
	return result;
} 

int main(){
	cout << "�˴����������Կɱ䳤����\n";
	return 0;
}
