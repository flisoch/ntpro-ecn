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

TEST_F(RegistrationTest, UsernameIdGenerated) {

    std::string id = core.RegisterNewUser("testname", status);
    ASSERT_EQ(id, "0");
}

TEST_F(RegistrationTest, EmptyUsernameNotRegistered) {

    std::string id = core.RegisterNewUser("", status);
    ASSERT_NE(id, "0");
}

TEST_F(RegistrationTest, EmptyUsernameReturnsNoIdAndStatus) {

    std::string id = core.RegisterNewUser("", status);
    ASSERT_EQ(status, StatusCodes::EmptyUsernameForm);
    ASSERT_EQ(id, "");

}

TEST_F(RegistrationTest, AlreadyUsedUsernameReturnsNoIdAndStatus) {

    core.RegisterNewUser("testname", status);
    std::string id = core.RegisterNewUser("testname", status);
    ASSERT_EQ(status, StatusCodes::UsernameAlreadyTaken);
    ASSERT_EQ(id, "");
}
