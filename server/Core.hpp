#ifndef CORE_HPP
#define CORE_HPP
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "dao/TraderDao.hpp"
#include "OrderDTO.hpp"
#include "Message.hpp"
#include "model/LimitOrderBook.hpp"

class Core
{
public:
    Core();
    // "Регистрирует" нового пользователя и возвращает его ID.
    std::string RegisterNewUser(const std::string &aUserName, std::string &status);

    // Запрос имени клиента по ID
    Trader *GetTrader(const std::string &traderId);
    std::string GetTraderBalance(const std::string &traderId, std::string &status);
    void NewOrder(OrderDTO order, std::string &status);
    static Core &GetCore();
    std::string SizetToString(size_t num);
    size_t StringToSizet(std::string str);

private:
    std::string ValidateUsername(const std::string &aUserName);
    LimitOrderBook orderBook;
    std::unique_ptr<TraderDao> traderDao;
};

#endif // CORE_HPP
