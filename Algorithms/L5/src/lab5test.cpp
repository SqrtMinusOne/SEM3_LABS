#include "prefix.h"
#include "kmp.h"
#include "gtest/gtest.h"

typedef struct PrefixTestType{
    char* input;
    vector<int> output;
}PrefixTestType;

PrefixTestType PrefixTest1 = {"abab", vector<int> {0, 0, 1, 2}};

class PrefixTest : public ::testing::TestWithParam<PrefixTestType>{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }

};

INSTANTIATE_TEST_CASE_P(PrefixTestInstantiation, PrefixTest, ::testing::Values(PrefixTest1));

TEST_P(PrefixTest, PrefixTestTrue)
{
    ASSERT_TRUE(prefix(GetParam().input) == GetParam().output);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
