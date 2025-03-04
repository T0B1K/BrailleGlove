#include <gtest/gtest.h>
#include "foo.h" // Include your header files

TEST(FooTest, HandlesPositiveInput) {
    EXPECT_EQ(foo(1), 2);
}

TEST(FooTest, HandlesNegativeInput) {
    EXPECT_EQ(foo(-1), 0);
}
