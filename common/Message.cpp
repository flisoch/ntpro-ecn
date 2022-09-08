#include "Message.hpp"

Message::Message(std::string statusCode, std::string body)
    : statusCode(statusCode),
      body(body)
{
}

Message::Message()
{
}

nlohmann::json Message::toJson()
{
    nlohmann::json message;
    message["StatusCode"] = statusCode;
    message["Body"] = body;
    return message;
}

Message Message::fromJson(nlohmann::json json)
{
    return Message(json["StatusCode"], json["Body"]);
}