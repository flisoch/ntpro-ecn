#ifndef SERVER_HPP
#define SERVER_HPP
#pragma once

#include <boost/asio.hpp>

using boost::asio::ip::tcp;


class session
{
public:
    session(boost::asio::io_service &io_service);

    tcp::socket &socket();

    void start();

    // Обработка полученного сообщения.
    void handle_read(const boost::system::error_code &error,
                     size_t bytes_transferred);

    void handle_write(const boost::system::error_code &error);

private:
    tcp::socket socket_;
    enum
    {
        max_length = 1024
    };
    char data_[max_length];
};

class server
{
public:
    server(boost::asio::io_service &io_service);

    void handle_accept(session *new_session,
                       const boost::system::error_code &error);
    void run();
private:
    boost::asio::io_service &io_service_;
    tcp::acceptor acceptor_;
};

#endif //SERVER_HPP