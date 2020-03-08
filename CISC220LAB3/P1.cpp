#include <iostream>
#include <stdlib.h>
using namespace std;

void func(char arr[], int len);
int main(char s[]) {
    char* f;
    f = new char[sizeof(f)];
	func(f,sizeof(f));
	for (int i = 1; i< sizeof(f); i+=2) {
		cout << f[i];
	}
	cout << endl;
	return 0;
}

void func(char arr[], int len) {
	for(int i = 0; i < len; i++) {
		int m = i;
		for (int j = i+1; j < len; j++) {
			if (arr[j] < arr[m]) {
				m = j;
			}
		}
		char tmp = arr[m];
		arr[m] = arr[i];
		arr[i] = tmp;
	}
}
