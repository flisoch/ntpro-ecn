#include <string>

#include "gtest/gtest.h"
#include "Core.hpp"
#include "Server.hpp"

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

    std::string id = Core::GetCore().RegisterNewUser("");
    ASSERT_NE(id, "0");
}
