#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MerkelMain
{
public:
    MerkelMain() = default;
    /** Call this to start the application */
    void init();

private:
    void printMenu();
    void printHelp();
    void printExchangeStats();
    void placeAsk();
    void placeBid();
    void printWallet();
    void continueProgram();
    void invalidChoice();
    void processUserOption();
    int getUserOption();
    OrderBook orderBook{"src/tradingData.csv"};
    std::string currentTime;
    void gotoNextTimeframe();

    // A vector is a sequence container that can dynamically grow or shrink in size.
    // It's similar to an array, but with the ability to resize itself automatically as elements are inserted or removed.
    // The vector class is defined in the <vector> header file.
    // std::vector<OrderBookEntry> orders;
};