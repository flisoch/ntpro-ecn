#ifndef CORE_HPP
#define CORE_HPP
#pragma once


#include <string>
#include <map>

class Core
{
public:
    // "Регистрирует" нового пользователя и возвращает его ID.
    std::string RegisterNewUser(const std::string& aUserName);
   

    // Запрос имени клиента по ID
    std::string GetUserName(const std::string& aUserId);
    static Core& GetCore();

private:

    std::string ValidateUsername(const std::string &aUserName);

    // <UserId, UserName>
    std::map<size_t, std::string> mUsers;
};

#endif //CORE_HPP