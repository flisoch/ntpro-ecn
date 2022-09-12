#ifndef USER_H
#define USER_H
#pragma once

#include <string>
#include <vector>
#include "json.hpp"


class User
{
    class Balance
    {
    public:
        long rub = 0;
        long usd = 0;
    };

public:
    User() = default;
    User(std::string username);
    User(size_t id, std::string username);
    nlohmann::json toJson();

    size_t id;
    std::string username;
    Balance balance;
};

#endif  //TRADER_HPP
