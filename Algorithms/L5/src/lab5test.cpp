#include "prefix.h"
#include "kmp.h"
#include "gtest/gtest.h"

typedef struct PrefixTestType{
    const char* input;
    vector<int> output;
}PrefixTestType;

PrefixTestType PrefixTest1 = {"abab", vector<int> {0, 0, 1, 2}};
PrefixTestType PrefixTest2 = {"abcdabscabcdabia", 
    vector<int> {0, 0, 0, 0, 1, 2, 0, 0, 1, 2, 3, 4, 5, 6, 0, 1}};
PrefixTestType PrefixTest3 = {"abcdabcabcdabcdab", 
    vector<int> {0, 0, 0, 0, 1, 2, 3, 1, 2, 3, 4, 5, 6, 7, 4, 5, 6}};
PrefixTestType PrefixTest4 = {"abcd", vector<int> {0, 0, 0, 0}};


class PrefixTest : public ::testing::TestWithParam<PrefixTestType>{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }

};

INSTANTIATE_TEST_CASE_P(PrefixTestInstantiation, PrefixTest, ::testing::Values(PrefixTest1, 
    PrefixTest2, PrefixTest3, PrefixTest4));

TEST_P(PrefixTest, PrefixTestTrue)
{
    ASSERT_TRUE(prefix(GetParam().input) == GetParam().output);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
