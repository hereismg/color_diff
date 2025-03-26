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


class Test_showDiff: public testing::TestWithParam<std::tuple<std::string, std::string, int>>{};
TEST_P(Test_showDiff, _){
    auto [befor_path, after_path, expected_res] = GetParam();
    
    auto befor = read(data_dir + befor_path);
    auto after = read(data_dir + after_path);

    Text txt(befor, after);

    txt.showDiff();
    // txt.calc_dp_mul();
    EXPECT_EQ(txt.m_dp[txt.m_befor.size()][txt.m_after.size()], expected_res);
}

INSTANTIATE_TEST_SUITE_P(TestSuit, Test_showDiff, testing::Values(
    tuple<string, string, int>{"/1_befor.txt", "/1_after.txt", 6},
    tuple<string, string, int>{"/2_befor.txt", "/2_after.txt", 1},
    tuple<string, string, int>{"/3_befor.txt", "/3_after.txt", 0},
    tuple<string, string, int>{"/4_befor.txt", "/4_after.txt", 3},
    tuple<string, string, int>{"/5_befor.txt", "/5_after.txt", 6},
    tuple<string, string, int>{"/6_befor.txt", "/6_after.txt", 0}
));

TEST(TestOpenML, _){
    #pragma omp parallel for
    for (int i=1; i<=10; i++){
        // cout << i << endl;  // 如果是用 cout 这种办法打印，会出现奇怪的情况！
        printf("%d\n", i);
    }
}