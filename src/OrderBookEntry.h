#pragma once
#include <string>

enum class OrderBookType
{
    ask,
    bid
};

class OrderBookEntry
{
public:
    OrderBookEntry(std::string _timestamp,
                   std::string _product,
                   OrderBookType _type,
                   double _price,
                   double _amount);

    std::string timestamp;
    std::string product;
    OrderBookType type;
    double price;
    double amount;
};