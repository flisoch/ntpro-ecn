#include "MemoryTraderDao.hpp"

size_t MemoryTraderDao::CreateTrader(std::string username)
{
    size_t newUserId = traders.size();
    traders.push_back(Trader(newUserId, username));
    return newUserId;
}

Trader *MemoryTraderDao::GetTrader(size_t traderId)
{
    if (traderId >= traders.size())
    {
        return nullptr;
    }
    else
    {
        return &traders[traderId];
    }
}

Trader *MemoryTraderDao::GetTraderByUsername(std::string username)
{
    for (auto &trader : traders)
    {
        if (trader.username == username)
        {
            return &trader;
        }
    }
    return nullptr;
}

Trader::Balance *MemoryTraderDao::GetTraderBalance(size_t traderId)
{
    Trader *trader = GetTrader(traderId);
    if (trader == nullptr)
    {
        return nullptr;
    }
    else
    {
        return &trader->balance;
    }
}

Trader::Balance *MemoryTraderDao::UpdateBalance(size_t traderId, int usd, int rub)
{
    Trader *trader = GetTrader(traderId);
    trader->balance.rub = rub;
    trader->balance.usd = usd;
    return &trader->balance;
}

size_t MemoryTraderDao::Size() const
{
    return traders.size();
}