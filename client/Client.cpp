#include "Client.hpp"
#include "json.hpp"
#include "Common.hpp"
#include <iostream>

Client::Client(boost::asio::io_service &io_service)
    : io_service(io_service),
      socket(io_service)
{
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(tcp::v4(), "127.0.0.1", std::to_string(port));
    tcp::resolver::iterator iterator = resolver.resolve(query);

    socket.connect(*iterator);
}

void Client::StartUi()
{
    bool isAuthenticated = Authenticate();
    while (!isAuthenticated)
    {
        isAuthenticated = Authenticate();
    }
    ShowMenu();
}

bool Client::Authenticate()
{
    bool isAuthenticated = false;
    std::cout << "Sign up or sign in:\n"
                 "1) Sign up\n"
                 "2) Sign in\n"
                 "3) Exit\n"
              << std::endl;

    short menu_option_num;
    std::cin >> menu_option_num;
    switch (menu_option_num)
    {
    case 1:
    {
        ProcessRegistrationForm();
        ProcessRegistration();
        isAuthenticated = true;
        break;
    }
    case 2:
    {
        std::cout << "Not supported yet\n";
        break;
    }
    case 3:
    {
        exit(0);
        break;
    }
    default:
    {
        std::cout << "Unknown menu option\n"
                  << std::endl;
    }
    }
    return isAuthenticated;
}

void Client::ShowMenu()
{
    while (true)
    {
        // Тут реализовано "бесконечное" меню.
        std::cout << "Menu:\n"
                     "1) Hello Request\n"
                     "2) Exit\n"
                  << std::endl;

        short menu_option_num;
        std::cin >> menu_option_num;
        switch (menu_option_num)
        {
        case 1:
        {
            // Для примера того, как может выглядить взаимодействие с сервером
            // реализован один единственный метод - Hello.
            // Этот метод получает от сервера приветствие с именем клиента,
            // отправляя серверу id, полученный при регистрации.
            SendMessage(std::to_string(user.id), Requests::Hello, "");
            std::cout << ReadMessage();
            break;
        }
        case 2:
        {
            exit(0);
            break;
        }
        default:
        {
            std::cout << "Unknown menu option\n"
                      << std::endl;
        }
        }
    }
}

// Отправка сообщения на сервер по шаблону.
void Client::SendMessage(
    const std::string &aId,
    const std::string &aRequestType,
    const std::string &aMessage)
{
    nlohmann::json req;
    req["UserId"] = aId;
    req["ReqType"] = aRequestType;
    req["Message"] = aMessage;

    std::string request = req.dump();
    boost::asio::write(socket, boost::asio::buffer(request, request.size()));
}

// Возвращает строку с ответом сервера на последний запрос.
std::string Client::ReadMessage()
{
    boost::asio::streambuf b;
    boost::asio::read_until(socket, b, "\0");
    std::istream is(&b);
    std::string line(std::istreambuf_iterator<char>(is), {});
    return line;
}

// "Создаём" пользователя, получаем его ID.
void Client::ProcessRegistration()
{

    // Для регистрации Id не нужен, заполним его нулём
    SendMessage("0", Requests::Registration, user.username);

    std::string id = ReadMessage();
    user.id = std::stoi(id);
}

void Client::ProcessRegistrationForm()
{
    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;
    user.id = -1;
    user.username = username;
}
