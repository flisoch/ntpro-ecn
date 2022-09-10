
#include "Limit.hpp"

Limit::Limit(Order* order) {
    price = order->price;
    volume += order->amount;
    orders.push_back(order);
}