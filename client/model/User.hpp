#ifndef USER_H
#define USER_H
#pragma once

#include <string>
#include <vector>


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
    User(unsigned long id, std::string username);

    unsigned long id;
    std::string username;
    Balance balance;
};

#endif  //TRADER_HPP
