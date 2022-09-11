#include "Core.hpp"
#include "Common.hpp"
#include "MemoryTraderDao.hpp"
#include <sstream>

Core::Core()
{
    traderDao = std::make_unique<MemoryTraderDao>();
}
// "Регистрирует" нового пользователя и возвращает его ID.
std::string Core::RegisterNewUser(const std::string &aUserName, std::string &status)
{
    status = ValidateUsername(aUserName);
    if (status != StatusCodes::OK)
    {
        return "";
    }

    size_t id = traderDao->CreateTrader(aUserName);
    return std::to_string(id);
}

Trader *Core::GetTrader(const std::string &traderId)
{
    return traderDao->GetTrader(StringToSizet(traderId));
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

    auto trader = traderDao->GetTraderByUsername(username);
    if (trader != nullptr)
    {
        return StatusCodes::UsernameAlreadyTaken;
    }

    return StatusCodes::OK;
}

void Core::NewOrder(OrderDTO dto, std::string &status)
{
    Order* order = new Order(dto.traderId, Order::Direction::BUY, dto.price, dto.amount);
    orderBook.Limit(order);
    auto trader = traderDao->GetTrader(order->traderId);
    // trader->orders.emplace(orderBook.orders.end());
    // traders[order.traderId].orders.push_back(orderBook.orders.end());
}

Core &Core::GetCore()
{
    static Core core;
    return core;
}

std::string Core::SizetToString(size_t num)
{
    char str[256];
    snprintf(str, sizeof str, "%zu", num);
    return std::string(str);
}

size_t Core::StringToSizet(std::string str)
{
    std::stringstream sstream(str);
    size_t result;
    sstream >> result;
    return result;
}