#ifndef CLIENSERVERECN_COMMON_HPP
#define CLIENSERVERECN_COMMON_HPP

#include <string>

static short port = 5555;

namespace Requests
{
    static std::string Registration = "Reg";
    static std::string Authorization = "Auth";
    static std::string Hello = "Hel";
    static std::string NewOrder = "NOrd";
    static std::string Balance = "Baln";
    static std::string ActiveOrders = "AOrd";
    static std::string Transactions = "Tran";
}

namespace StatusCodes
{
    static std::string UserNotFound = "UserNotFound";
    static std::string EmptyUsernameForm = "EmptUsname";
    static std::string UsernameAlreadyTaken = "UsernameTaken";
    static std::string OK = "OK";
    static std::string AuthenticationFailed = "AuthFailed";
    static std::string UnknownError = "UnknownError";
}
#endif //CLIENSERVERECN_COMMON_HPP
