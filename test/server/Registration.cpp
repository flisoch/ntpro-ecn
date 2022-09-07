#include <string>

#include "gtest/gtest.h"
#include "Core.hpp"
#include "Server.hpp"
#include "Common.hpp"

class RegistrationTest : public ::testing::Test
{
protected:
	Core core;
};

TEST_F(RegistrationTest, UsernameIdGenerated) {

    std::string id = core.RegisterNewUser("testname");
    ASSERT_EQ(id, "0");
}

TEST_F(RegistrationTest, EmptyUsernameNotRegistered) {

    std::string id = core.RegisterNewUser("");
    ASSERT_NE(id, "0");
}

TEST_F(RegistrationTest, EmptyUsernameReurnsStatusNotId) {

    std::string id = core.RegisterNewUser("");
    ASSERT_EQ(id, StatusCodes::EmptyUsernameForm);
}


TEST_F(RegistrationTest, AlreadyUsedUsernameReturnsStatusNotId) {

    core.RegisterNewUser("testname");
    std::string id = core.RegisterNewUser("testname");
    ASSERT_EQ(id, StatusCodes::UsernameAlreadyTaken);
}
