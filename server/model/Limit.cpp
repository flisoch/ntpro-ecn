
#include "Limit.hpp"

Limit::Limit(Order* order) {
    price = order->price;
    volume += order->amount;
    orders.emplace(order);
}
