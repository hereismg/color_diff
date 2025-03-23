#include <iostream>
#include "diff.hpp"
using namespace mg;
using namespace std;

int main(){
    auto befor = read("befor.txt");
    auto after = read("after.txt");

    Text txt(befor, after);

    int res = txt.calc_diff();

    cout << res << endl;

    // // 红色前景 + 黄色背景 + 加粗
    // std::cout << "\033[1;31;43m红字黄底加粗文本\033[0m" << std::endl;

    // // 青色前景 + 下划线
    // std::cout << "\033[4;36m青色下划线文本\033[0m" << std::endl;

    return 0;
}
