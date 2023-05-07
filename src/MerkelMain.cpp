#include "MerkelMain.h"
#include "CSVReader.h"
#include "OrderBook.h"
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
    int userOption{0};
    std::string line;
    std::cout << "Enter option, type 1-6" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userOption = std::stoi(line);
    }
    catch (const std::exception &e)
    {
    }
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
    menu[3] = &MerkelMain::enterAsk;
    menu[4] = &MerkelMain::enterBid;
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

void MerkelMain::enterAsk()
{
    std::vector<std::string> tokens;
    bool inputValid = false;

    while (!inputValid)
    {
        std::cout << "Make a ask - enter the amount: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
        std::string input;
        std::getline(std::cin, input);
        std::cout << "Your ask: " << input << std::endl;
        tokens = checkAskBidInput(input);
        inputValid = tokens.size() == 3; // Check if the input is valid
    }
    OrderBookEntry ask = CSVReader::stringsToOBE(currentTime, tokens[0], OrderBookType::ask, tokens[1], tokens[2]);
    orderBook.insertOrder(ask);
}

void MerkelMain::enterBid()
{
    std::vector<std::string> tokens;
    bool inputValid = false;

    while (!inputValid)
    {
        std::cout << "Make a bid - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
        std::string input;
        std::getline(std::cin, input);
        std::cout << "Your bid: " << input << std::endl;
        tokens = checkAskBidInput(input);
        inputValid = tokens.size() == 3; // Check if the input is valid
    }
    OrderBookEntry bid = CSVReader::stringsToOBE(currentTime, tokens[0], OrderBookType::bid, tokens[1], tokens[2]);
    orderBook.insertOrder(bid);
}

std::vector<std::string> MerkelMain::checkAskBidInput(std::string input)
{
    std::string product;
    double price;
    double amount;
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    if (tokens.size() != 3)
    {
        std::cout << "Bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            price = std::stod(tokens[1]);
            amount = std::stod(tokens[2]);
        }
        catch (const std::exception &e)
        {
            std::cout << "Price is incorrect! " << price << std::endl;
            std::cout << "Amount is incorrect! " << amount << std::endl;
        }
    }

    return tokens;
}