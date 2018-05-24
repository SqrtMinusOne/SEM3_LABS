#include <vector>
#include "bohr.h"
#include "ahocorasick.h"
#include "gtest/gtest.h"

typedef struct AHTestType{
    string T;
    vector<string> P;
    ACres res;
}AHTestType;

typedef struct AHJokerTestType{
    string T;
    string P;
    char J;
    ACres res;
}AHJokerTestType;

AHTestType AHTest1 = {"abcdabcdabcd", {"a", "ab", "abc", "abcd"},
    {{1,1}, {1,2}, {1, 3}, {1,4}, {5,1}, {5,2}, {5,3}, {5,4}, {9,1}, {9,2}, {9,3}, {9,4}}};

AHTestType AHTest2 = {"CCCA", {"CC"},
    {{1,1}, {2,1}}};

AHTestType AHTest3 = {"AAAA", {"A", "AA"},
    {{1,1}, {1,2}, {2,1}, {2,2}, {3,1}, {3,2}, {4,1}}};

AHJokerTestType AHJokerTest1 = {"ACT", "A$", '$', {{1,1}}};

AHJokerTestType AHJokerTest2 = {"xabvccbababcax", "ab??c?", '?', {{2,1}, {8,1}}};

AHJokerTestType AHJokerTest3 = {"abacadaeaf", "a?", '?', {{1,1}, {3,1}, {5,1}, {7,1}, {9,1}}};

AHJokerTestType AHJokerTest4 = {"abacadaeaf", "aqaqaq", 'q', {{1,1}, {3,1}, {5,1}}};

AHJokerTestType AHJokerTest5 = {"qwerqwwrqqqrr", "###r", '#', {{1,1}, {5,1}, {9,1}, {10,1}}};

class AHTest : public ::testing::TestWithParam<AHTestType>{
    public:
        virtual void SetUp() {}
        virtual void TearDown() {}
};

class AHJokerTest : public ::testing::TestWithParam<AHJokerTestType>{
    public:
        virtual void SetUp() {}
        virtual void TearDown() {}
};

INSTANTIATE_TEST_CASE_P(AHJokerTestInstantiation, AHJokerTest,
    ::testing::Values(AHJokerTest1, AHJokerTest2, AHJokerTest3, AHJokerTest4, AHJokerTest5));

INSTANTIATE_TEST_CASE_P(AHTestInstantiation, AHTest,
    ::testing::Values(AHTest1, AHTest2, AHTest3));


TEST_P(AHTest, AHTestTrue){
    ACres res = doAhoCorasick(GetParam().T, GetParam().P);
    ASSERT_TRUE(CMP(GetParam().res, res));
}

TEST_P(AHJokerTest, AHJokerTestTrue){
    ACres res = doAhoCorasick(GetParam().T, vector<string>{GetParam().P}, GetParam().J);
    ASSERT_TRUE(CMP(GetParam().res, res));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
