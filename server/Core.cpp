#include "Core.hpp"
#include "Common.hpp"

// "Регистрирует" нового пользователя и возвращает его ID.
std::string Core::RegisterNewUser(const std::string &aUserName)
{   
    std::string status = ValidateUsername(aUserName);
    if (status != StatusCodes::OK) {
        return status;
    }

    size_t newUserId = mUsers.size();
    mUsers[newUserId] = aUserName;

    return std::to_string(newUserId);
}

// Запрос имени клиента по ID
std::string Core::GetUserName(const std::string &aUserId)
{
    const auto userIt = mUsers.find(std::stoi(aUserId));
    if (userIt == mUsers.cend())
    {
        return "Error! Unknown User";
    }
    else
    {
        return userIt->second;
    }
}

std::string Core::ValidateUsername(const std::string &aUserName) {
    if (aUserName.empty()) {
        return StatusCodes::EmptyUsernameForm;
    }
    
    for (auto& it: mUsers) {
        if (it.second == aUserName) {
            return StatusCodes::UsernameAlreadyTaken;
        }
    }
    return StatusCodes::OK;
}

Core& Core::GetCore() {
    static Core core;
    return core;
}
