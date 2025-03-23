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


class Test_showDiff: public testing::TestWithParam<std::tuple<std::string, std::string>>{};
TEST_P(Test_showDiff, _){
    auto [befor_path, after_path] = GetParam();
    
    auto befor = read(data_dir + befor_path);
    auto after = read(data_dir + after_path);

    Text txt(befor, after);

    txt.showDiff();
}

INSTANTIATE_TEST_SUITE_P(TestSuit, Test_showDiff, testing::Values(
    tuple<string, string>{"/1_befor.txt", "/1_after.txt"},
    tuple<string, string>{"/2_befor.txt", "/2_after.txt"},
    tuple<string, string>{"/3_befor.txt", "/3_after.txt"},
    tuple<string, string>{"/4_befor.txt", "/4_after.txt"},
    tuple<string, string>{"/5_befor.txt", "/5_after.txt"}
));
