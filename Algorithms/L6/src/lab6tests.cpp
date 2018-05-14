#include <vector>
#include "bohr.h"
#include "ahocorasick.h"
#include "gtest/gtest.h"

typedef struct AHTestType{
    string T;
    vector<string> P;
    ACres res;
}AHTestType;

AHTestType AHTest1 = {"abcdabcdabcd", {"a", "ab", "abc", "abcd"},
    {{1,1}, {1,2}, {1, 3}, {1,4}, {5,1}, {5,2}, {5,3}, {5,4}, {9,1}, {9,2}, {9,3}, {9,4}}};

class AHTest : public ::testing::TestWithParam<AHTestType>{
    public:
        virtual void SetUp() {}
        virtual void TearDown() {}
};

INSTANTIATE_TEST_CASE_P(AHTestInstantiation, AHTest,
    ::testing::Values(AHTest1));

TEST_P(AHTest, AHTestTrue){
    ACres res = doAhoCorasick(GetParam().T, GetParam().P);
    ASSERT_TRUE(CMP(GetParam().res, res));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}