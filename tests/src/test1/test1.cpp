#include<gtest/gtest.h>
#include<diff.hpp>
using namespace mg;
using namespace std;

TEST(Test_data_path, _1){
#ifndef TEST_DATA_PATH
    cout << "未定义宏 TEST_DATA_PATH" << endl;
    ASSERT_TRUE(false);
#else
    ASSERT_TRUE(true);
#endif
}
std::string data_dir = TEST_DATA_PATH;

TEST(TestSuit, _1){
    auto befor = read(data_dir + "/1_befor.txt");
    auto after = read(data_dir +  "/1_after.txt");

    Text txt(befor, after);

    txt.showDiff();
}

TEST(TestSuit, _2){
    auto befor = read(data_dir + "/2_befor.txt");
    auto after = read(data_dir +  "/2_after.txt");

    Text txt(befor, after);

    txt.showDiff();
}
