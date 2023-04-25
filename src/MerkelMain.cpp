#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <map>

void MerkelMain::init()
{
    loadOrderBook();
    int input;
    while (true)
    {
        printMenu();

        processUserOption();
    }
}
/** load up some dummy data for now */
void MerkelMain::loadOrderBook()
{
    OrderBookEntry obe1("2020/03/17 17:01:24", "ETH/BTC", OrderBookType::bid, 0.02187308, 0.44564869);
    OrderBookEntry obe2("2020/03/17 17:01:24", "ETH/BTC", OrderBookType::ask, 0.02189308, 0.44564869);

    orders.push_back(obe1);
    orders.push_back(obe2);
    for (auto &entry : orders)
    {
        std::cout << entry.price << std::endl;
    }
}

void MerkelMain::printMenu()
{
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
}

int MerkelMain::getUserOption()
{
    int userOption;
    std::cin >> userOption;
    return userOption;
}

void MerkelMain::printHelp()
{
    std::cout << "You selected 'Print help'" << std::endl;
}

void MerkelMain::printExchangeStats()
{
    std::cout << "You selected 'Print exchange stats'" << std::endl;
}

void MerkelMain::placeAsk()
{
    std::cout << "You selected 'Place an ask'" << std::endl;
}

void MerkelMain::placeBid()
{
    std::cout << "You selected 'Place a bid'" << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << "You selected 'Print wallet'" << std::endl;
}

void MerkelMain::continueProgram()
{
    std::cout << "You selected 'Continue'" << std::endl;
}

void MerkelMain::invalidChoice()
{
    std::cout << "Invalid choice" << std::endl;
}

void MerkelMain::processUserOption()
{
    std::map<int, void (MerkelMain::*)()> menu;
    menu[1] = &MerkelMain::printHelp;
    menu[2] = &MerkelMain::printExchangeStats;
    menu[3] = &MerkelMain::placeAsk;
    menu[4] = &MerkelMain::placeBid;
    menu[5] = &MerkelMain::printWallet;
    menu[6] = &MerkelMain::continueProgram;

    int userOption = getUserOption();
    if (userOption >= 1 && userOption <= 6)
    {
        (this->*menu[userOption])();
    }
    else
    {
        invalidChoice();
    }
}

double MerkelMain::computeAveragePrice(std::vector<OrderBookEntry> &entries)
{
    double sum{};
    for (auto &entry : entries)
    {
        double sum = sum + entry.price;
    }
    return sum / entries.size();
}

double MerkelMain::computeLowPrice(std::vector<OrderBookEntry> &entries)
{
    double lowestPrice{entries[0].price};
    for (auto &entry : entries)
    {
        if (lowestPrice > entry.price)
        {
            lowestPrice = entry.price;
        }
    }
    return lowestPrice;
}

double MerkelMain::computeHighPrice(std::vector<OrderBookEntry> &entries)
{
    double highestPrice{entries[0].price};
    for (auto &entry : entries)
    {
        if (highestPrice < entry.price)
        {
            highestPrice = entry.price;
        }
    }
    return highestPrice;
}

double MerkelMain::computePriceSpread(std::vector<OrderBookEntry> &entries)
{
    double priceSpread{computeHighPrice(entries) - computeLowPrice(entries)};
    return priceSpread;
}