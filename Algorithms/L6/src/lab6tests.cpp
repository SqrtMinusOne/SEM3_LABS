#include "bohr.h"
#include "ahocorasick.h"
#include "gtest/gtesh.h"

typedef struct AHTestType{
    string T;
    vector<string> P;
    ACresEl res;
}

class AHTest : public ::testing::TestWithParam<AHTestType>{
    public:
        virtual void SetUp()
        virtual void TearDown();
};

INSTANTIATE_TEST_CAPE_P(AHTestInstantiation, AHTest,
    ::testing::Values(AHTest1));

TEST_P(AHTest, AHTestTrue){
    Node* bohr = new Node;
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}