#include <string>

#include "gtest/gtest.h"
#include "Message.hpp"


TEST(MessageTest, ToJsonSuccess) {

    Message m(StatusCodes::OK, "TestMessage");

    nlohmann::json json = m.toJson();

    ASSERT_EQ(json["StatusCode"], m.statusCode);
    ASSERT_EQ(json["Body"], m.body);
}

TEST(MessageTest, FromJsonSuccess) {

    auto json = "{ \"StatusCode\": \"OK\", \"Body\": \"0\" }"_json;
    auto message = Message::fromJson(json);

    ASSERT_EQ(message.statusCode, StatusCodes::OK);
    ASSERT_EQ(message.body, "0");
}