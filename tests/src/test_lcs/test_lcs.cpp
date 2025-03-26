#include<iostream>
#include<omp.h>
using namespace std;

int main() {
    #pragma omp parallel for
    for (int i = 0; i < 20; i++) {
        // 循环体，例如打印 i 的值
        printf("Iteration %d\n", i);
    }
    return 0;
}