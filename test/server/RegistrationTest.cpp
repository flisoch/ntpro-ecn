#include <string>

#include "gtest/gtest.h"
#include "Core.hpp"
#include "Server.hpp"
#include "Common.hpp"

class RegistrationTest : public ::testing::Test
{
protected:
    Core core;
    std::string status;
};

TEST_F(RegistrationTest, UsernameIdGenerated)
{

    auto id = core.RegisterNewUser("testname", status);
    ASSERT_EQ(id, 0);
}

TEST_F(RegistrationTest, EmptyUsernameNotRegistered)
{

    auto id = core.RegisterNewUser("", status);
    ASSERT_NE(id, 0);
}

TEST_F(RegistrationTest, EmptyUsernameReturnsNoIdAndStatus)
{

    auto id = core.RegisterNewUser("", status);
    ASSERT_EQ(status, StatusCodes::EmptyUsernameForm);
}

TEST_F(RegistrationTest, AlreadyUsedUsernameReturnsNoIdAndStatus)
{

    core.RegisterNewUser("testname", status);
    auto id = core.RegisterNewUser("testname", status);
    ASSERT_EQ(status, StatusCodes::UsernameAlreadyTaken);
}
