#include "color.h"
//#include "shape.h"
#include "point.h"
#include "vector.hpp"
#include "gtest/gtest.h"

TEST(PointTest, PointTest1){
    Point p1(1,2);
    ASSERT_EQ(p1.GetX(), 1);
    ASSERT_EQ(p1.GetY(), 2);
    Point p2 = p1; Point p3(p2);
    ASSERT_TRUE((p1 == p2) && (p1 == p3) && (p2 == p3));
    p1 = p1 * 2;
    ASSERT_TRUE(p1 == Point(2, 4));
    p1 = p1 + Point (2,2);
    ASSERT_TRUE(p1 == Point(4,6));
    p1 = p1 / 2;
    ASSERT_TRUE(p1 == Point(2,3));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}