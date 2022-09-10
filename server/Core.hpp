#ifndef CORE_HPP
#define CORE_HPP
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "model/Trader.hpp"
#include "Message.hpp"

class Core
{
public:
    // "Регистрирует" нового пользователя и возвращает его ID.
    std::string RegisterNewUser(const std::string &aUserName, std::string &status);

    // Запрос имени клиента по ID
    Trader *GetTrader(const std::string &traderId);
    std::string GetTraderBalance(const std::string &traderId, std::string &status);

    static Core &GetCore();

private:
    std::string ValidateUsername(const std::string &aUserName);

    std::vector<Trader> traders;
};

#endif // CORE_HPP
