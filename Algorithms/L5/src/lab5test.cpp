#include "prefix.h"
#include "kmp.h"
#include "gtest/gtest.h"

typedef struct PrefixTestType{
    const char* input;
    vector<int> output;
}PrefixTestType;

typedef struct KMPTestType{
    const char* P;
    const char* T;
    vector<int> res;
    unsigned int multiplier;
}KMPTestType;

PrefixTestType PrefixTest1 = {"abab", vector<int> {0, 0, 1, 2}};
PrefixTestType PrefixTest2 = {"abcdabscabcdabia",
    vector<int> {0, 0, 0, 0, 1, 2, 0, 0, 1, 2, 3, 4, 5, 6, 0, 1}};
PrefixTestType PrefixTest3 = {"abcdabcabcdabcdab",
    vector<int> {0, 0, 0, 0, 1, 2, 3, 1, 2, 3, 4, 5, 6, 7, 4, 5, 6}};
PrefixTestType PrefixTest4 = {"abcd", vector<int> {0, 0, 0, 0}};

KMPTestType KMPTest1 = {"ab", "abab", vector<int> {0, 2}, 1};
KMPTestType KMPTest2 = {"ab", "cdef", vector<int> {}, 1};

KMPTestType KMPShiftTest={"abcdef", "defabc", vector<int> {3}, 2};
KMPTestType KMPShiftTest2={"abababab", "babababa", vector<int> {1, 3, 5, 7}, 2};


class PrefixTest : public ::testing::TestWithParam<PrefixTestType>{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }

};

class KMPTest : public ::testing::TestWithParam<KMPTestType>{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }
};

class NaiveTest : public ::testing::TestWithParam<KMPTestType>{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }
};

INSTANTIATE_TEST_CASE_P(PrefixTestInstantiation, PrefixTest, ::testing::Values(PrefixTest1,
    PrefixTest2, PrefixTest3, PrefixTest4));

INSTANTIATE_TEST_CASE_P(KMPTestInstantiation, KMPTest, ::testing::Values(KMPTest1, KMPTest2));

INSTANTIATE_TEST_CASE_P(NaiveTestInstantiation, NaiveTest, ::testing::Values(KMPTest1, KMPTest2));

INSTANTIATE_TEST_CASE_P(KMPShiftTestInstantiation, KMPTest, ::testing::Values(KMPShiftTest, KMPShiftTest2));

TEST_P(PrefixTest, PrefixTestTrue)
{
    ASSERT_TRUE(prefix(GetParam().input) == GetParam().output);
}

TEST_P(KMPTest, KMPTestTrue){
    ASSERT_TRUE(kmp(GetParam().P, GetParam().T, GetParam().multiplier) == GetParam().res);
}

TEST_P(NaiveTest, NaiveTestTrue){
    ASSERT_TRUE(naive(GetParam().P, GetParam().T) == GetParam().res);

}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
