#pragma once
#include <vector>
#include "OrderBookEntry.h"

class MerkelMain
{
public:
    MerkelMain() = default;
    /** Call this to start the application */
    void init();

private:
    void loadOrderBook();
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

    double computeAveragePrice(std::vector<OrderBookEntry> &entries);
    double computeLowPrice(std::vector<OrderBookEntry> &entries);
    double computeHighPrice(std::vector<OrderBookEntry> &entries);
    double computePriceSpread(std::vector<OrderBookEntry> &entries);

    // A vector is a sequence container that can dynamically grow or shrink in size.
    // It's similar to an array, but with the ability to resize itself automatically as elements are inserted or removed.
    // The vector class is defined in the <vector> header file.
    std::vector<OrderBookEntry> orders;
};