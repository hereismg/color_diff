#include<string>
#include<iostream>
#include<omp.h>
#include<ctime>
#include<diff.hpp>
using namespace std;
using namespace mg;

std::string data_dir = TEST_DATA_PATH;

int main(){
    {
        std::string befor_path = "/1_after.txt";
        std::string after_path = "/1_befor.txt";
        
        auto befor = read(data_dir + befor_path);
        auto after = read(data_dir + after_path);

        Text txt(befor, after);

        clock_t start = clock();
        int res = txt.calc_dp_mul();
        clock_t end = clock();

        printf("并发：%.5lf s\n", (double)(end - start) / CLOCKS_PER_SEC);
        printf("res = %d\n", res);
    }
    {
        std::string befor_path = "/1_after.txt";
        std::string after_path = "/1_befor.txt";
        
        auto befor = read(data_dir + befor_path);
        auto after = read(data_dir + after_path);

        Text txt(befor, after);

        clock_t start = clock();
        int res = txt.calc_dp();
        clock_t end = clock();

        printf("经典：%.5lf s\n", (double)(end - start) / CLOCKS_PER_SEC);
        printf("res = %d\n", res);
    }

    return 0;
}