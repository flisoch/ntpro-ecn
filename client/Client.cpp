#include "Client.hpp"
#include "json.hpp"
#include "Common.hpp"
#include "OrderDTO.hpp"

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
    std::string status = Authenticate();
    while (status != StatusCodes::OK)
    {
        std::cout << status << "\n";
        status = Authenticate();
    }
    ShowMenu();
}

std::string Client::Authenticate()
{
    std::string status = StatusCodes::AuthenticationFailed;

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
        status = StatusCodes::OK;
        break;
    }
    case 2:
    {
        std::cout << "Not supported yet\n\n";
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
    return status;
}

void Client::ShowMenu()
{
    while (true)
    {
        // Тут реализовано "бесконечное" меню.
        std::cout << "Menu:\n"
                     "1) Show Balance\n"
                     "2) Show Active Orders\n"
                     "3) Create Order\n"
                     "4) Exit\n"
                  << std::endl;

        short menu_option_num;
        std::cin >> menu_option_num;
        switch (menu_option_num)
        {
        case 1:
        {
            SendMessage(user.id, Requests::Balance, nlohmann::json({}));
            break;
        }
        case 2:
        {
            SendMessage(user.id, Requests::ActiveOrders, nlohmann::json({}));
            break;
        }
        case 3:
        {
            OrderDTO order = InputOrder();
            SendMessage(user.id, Requests::NewOrder, order.toJson());
            break;
        }
        case 4:
        {
            exit(0);
            break;
        }
        default:
        {
            std::cout << "Unknown menu option\n\n"
                      << std::endl;
        }
        }
        Message message = ReadMessage();
        if (message.statusCode != StatusCodes::OK)
        {
            std::cout << "Error: " + message.statusCode;
        }
        std::cout << message.body << "\n\n";
    }
}

// Отправка сообщения на сервер по шаблону.
void Client::SendMessage(
    size_t aId,
    const std::string &aRequestType,
    const nlohmann::json &aMessage)
{
    nlohmann::json req;
    req["UserId"] = aId;
    req["ReqType"] = aRequestType;
    req["Message"] = aMessage;

    std::string request = req.dump();
    boost::asio::write(socket, boost::asio::buffer(request, request.size()));
}

// Возвращает строку с ответом сервера на последний запрос.
Message Client::ReadMessage()
{
    boost::asio::streambuf b;
    boost::asio::read_until(socket, b, "\0");
    std::istream is(&b);
    std::string line(std::istreambuf_iterator<char>(is), {});
    auto json = nlohmann::json::parse(line);
    return Message::fromJson(json);
}

// "Создаём" пользователя, получаем его ID.
std::string Client::ProcessRegistration()
{

    // Для регистрации Id не нужен, заполним его нулём
    SendMessage(0, Requests::Registration, user.toJson());

    Message response = ReadMessage();
    if (response.statusCode != StatusCodes::OK)
    {
    }
    user.id = std::stoi(response.body);

    return StatusCodes::OK;
}

void Client::ProcessRegistrationForm()
{
    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;
    user.id = -1;
    user.username = username;
}

OrderDTO Client::InputOrder()
{
    std::cout << "Enter direction, price and amount. Example: \n"
                 "sell 60 10\n"
                 "buy 61 20\n\n";

    std::string direction;
    double price;
    double amount;
    std::cin >> direction >> price >> amount;
    return OrderDTO(user.id, direction, price, amount);
}
