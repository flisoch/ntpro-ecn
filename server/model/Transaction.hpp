#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#pragma once

#include "Order.hpp"

class Transaction {
    Transaction(unsigned long buyOrderId, unsigned long sellOrderId);
    unsigned long buyOrderId;
    unsigned long sellOrderId;
private:
    void FillOrders();
};

#endif  //TRANSACTION_HPP
