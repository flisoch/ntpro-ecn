#include "Core.hpp"
#include "Common.hpp"

// "Регистрирует" нового пользователя и возвращает его ID.
std::string Core::RegisterNewUser(const std::string &aUserName, std::string &status)
{
    status = ValidateUsername(aUserName);
    if (status != StatusCodes::OK)
    {
        return "";
    }

    size_t newUserId = traders.size();
    traders.push_back(Trader(newUserId, aUserName));
    return std::to_string(newUserId);
}

Trader *Core::GetTrader(const std::string &traderId)
{
    long id = std::stol(traderId);
    if (id >= traders.size())
    {
        return nullptr;
    }
    else
    {
        return &traders[id];
    }
}

std::string Core::GetTraderBalance(const std::string &traderId, std::string &status)
{
    Trader *trader = GetTrader(traderId);
    std::string balanceString;
    if (trader == nullptr)
    {
        status = StatusCodes::UserNotFound;
    }
    else
    {
        status = StatusCodes::OK;
        balanceString = "USD:" + std::to_string(trader->balance.usd) + ", RUB:" + std::to_string(trader->balance.rub);
    }

    return balanceString;
}

std::string Core::ValidateUsername(const std::string &username)
{
    if (username.empty())
    {
        return StatusCodes::EmptyUsernameForm;
    }

    for (const auto &trader : traders)
    {
        if (trader.username == username)
        {
            return StatusCodes::UsernameAlreadyTaken;
        }
    }
    return StatusCodes::OK;
}

Core &Core::GetCore()
{
    static Core core;
    return core;
}
