#include "prefix.h"
#include "kmp.h"
#include "gtest/gtest.h"

TEST(PrefixTests1, PositiveNos) { 
    ASSERT_TRUE((vector<int> {0, 0, 0, 0}) == prefix("abcd"));
    ASSERT_TRUE((vector<int> {0, 0, 1, 2}) == prefix("abab"));
}
 
TEST(PrefixTests2, PositiveNos) {
    ASSERT_TRUE((vector<int> {0, 0, 0, 0, 1, 2, 0, 0, 1, 2, 3, 4, 5, 6, 0, 1}) == prefix("abcdabscabcdabia"));
}

TEST(KMPTests, PositiveNos) {
    ASSERT_TRUE((vector<int> {0, 2}) == kmp("ab", "abab"));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
