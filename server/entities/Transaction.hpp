#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#pragma once

#include "Order.hpp"

class Transaction {
    Transaction(Order& buyOrder, Order& sellOrder);
    Order buyOrder;
    Order sellOrder;
private:
    void FillOrders();
};

#endif  //TRANSACTION_HPP