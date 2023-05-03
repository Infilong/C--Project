#include "MerkelMain.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>
#include <map>

void MerkelMain::init()
{
    currentTime = orderBook.getEarliestTime();
    while (true)
    {
        printMenu();
        processUserOption();
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
    std::cout << "Current time: " << currentTime << std::endl;

    for (const std::string &p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << "Average ask: " << OrderBook::getAveragePrice(entries) << std::endl;
    }
    currentTime = orderBook.getNextTime(currentTime);
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

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Goto next timeframe" << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
}