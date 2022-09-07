#include <iostream>
#include "Client.hpp"

int main()
{
   try
    {
        boost::asio::io_service io_service;
        Client client(io_service);
        client.StartUi();
        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}