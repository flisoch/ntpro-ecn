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

private:
    // <UserId, UserName>
    std::map<size_t, std::string> mUsers;
};

#endif //CORE_HPP