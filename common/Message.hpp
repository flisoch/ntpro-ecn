#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#pragma once

#include "Common.hpp"
#include "json.hpp"

class Message
{
public:
    std::string statusCode;
    std::string body;
    
    Message();
    Message(std::string statusCode, std::string body);

    nlohmann::json toJson();
    static Message fromJson(nlohmann::json json);
};

#endif // MESSAGE_HPP
