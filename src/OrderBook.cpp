#include "OrderBook.h"
#include <map>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    /** This will result in a data structure mapping a unique set of product names to
true values, e.g.:
key -> value
===============
ETH/BTC -> true
BTC/USDT -> true */
    std::map<std::string, bool> prodMap;
    for (const OrderBookEntry &e : orders)
    {
        prodMap[e.product] = true;
    }

    // iterate over the keys in the map and store them out to a vector of strings
    std::vector<std::string> products;
    for (const auto &e : prodMap)
    {
        products.push_back(e.first);
    }
    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp)
{
    std::vector<OrderBookEntry> results;
    for (const OrderBookEntry &e : orders)
    {
        if (e.type == type && e.product == product && e.timestamp == timestamp)
        {
            results.push_back(e);
        }
    }
    return results;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double high{0};
    for (const OrderBookEntry &e : orders)
    {
        if (e.price > high)
        {
            high = e.price;
        }
    }
    return high;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    double low{0};
    for (const OrderBookEntry &e : orders)
    {
        if (e.price < low)
        {
            low = e.price;
        }
    }
    return low;
}

double OrderBook::getAveragePrice(std::vector<OrderBookEntry> &orders)
{
    double sum{0};
    unsigned int count{0};
    for (const OrderBookEntry &e : orders){
        sum = sum  + e.price;
        count++;
    }
    return sum/count;
}

std::string OrderBook::getEarliestTime()
{
    OrderBookEntry earliest = orders[0];
    for (const OrderBookEntry &e : orders)
    {
        if (e.timestamp < earliest.timestamp)
        {
            earliest = e;
        }
    }
    return earliest.timestamp;
}

std::string OrderBook::getNextTime(const std::string &timestamp)
{
    std::string nextTime{""};
    for (OrderBookEntry e : orders)
    {
        if (e.timestamp > timestamp)
        {
            nextTime = e.timestamp;
            break;
        }
    }
    if (nextTime == "")
    {
        nextTime = orders[0].timestamp;
    }
    return nextTime;
}
