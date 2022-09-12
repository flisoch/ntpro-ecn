#include "gtest/gtest.h"
#include "Core.hpp"

class CoreTest : public ::testing::Test
{
protected:
    Core core;
};

TEST_F(CoreTest, SizetToStringSuccess)
{
    size_t number = 1;
    std::string numStr = core.SizetToString(number);
    ASSERT_EQ(numStr, "1");
}
