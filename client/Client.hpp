#ifndef CLIENT_HPP
#define CLIENT_HPP
#pragma once

#include <boost/asio.hpp>
#include "model/User.hpp"

using boost::asio::ip::tcp;

class Client
{
public:
    Client(boost::asio::io_service &io_service);
    void StartUi();

private:
    void SendMessage(
        const std::string &aId,
        const std::string &aRequestType,
        const std::string &aMessage);

    std::string ReadMessage();
    
    void ProcessRegistration();
    void ProcessRegistrationForm();

    void ShowMenu();
    bool Authenticate();

    tcp::socket socket;
    boost::asio::io_service &io_service;
    User user;
};


#endif // CLIENT_HPP
