#include <iostream>
#include <string>
#include <vector>
#include <map>

void pirntMenu()
{
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
}

int getUserOption()
{
    int userOption;
    std::cin >> userOption;
    return userOption;
}

void printHelp()
{
    std::cout << "You selected 'Print help'" << std::endl;
}

void printExchangeStats()
{
    std::cout << "You selected 'Print exchange stats'" << std::endl;
}

void placeAsk()
{
    std::cout << "You selected 'Place an ask'" << std::endl;
}

void placeBid()
{
    std::cout << "You selected 'Place a bid'" << std::endl;
}

void printWallet()
{
    std::cout << "You selected 'Print wallet'" << std::endl;
}

void continueProgram()
{
    std::cout << "You selected 'Continue'" << std::endl;
}

void invalidChoice()
{
    std::cout << "Invalid choice" << std::endl;
}

void userChoice()
{
    std::map<int, void (*)()> menu;
    menu[1] = printHelp;
    menu[2] = printExchangeStats;
    menu[3] = placeAsk;
    menu[4] = placeBid;
    menu[5] = printWallet;
    menu[6] = continueProgram;

    int userOption = getUserOption();
    if (userOption >= 1 && userOption <= 6)
    {
        menu[userOption]();
    }
    else
    {
        invalidChoice();
    }
}

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
                   double _amount) : timestamp(_timestamp), product(_product), type(_type), price(_price), amount(_amount)
    {
    }
    double price; // Define price as a non-static data member
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType type;
};

double computeAveragePrice(std::vector<OrderBookEntry> &entries)
{
    double sum{};
    for (auto &entry : entries)
    {
        double sum = sum + entry.price;
    }
    return sum / entries.size();
}

double computeLowPrice(std::vector<OrderBookEntry> &entries)
{
    double lowestPrice{entries[0].price};
    for (auto &entry : entries)
    {
        if (lowestPrice > entry.price)
        {
            lowestPrice = entry.price;
        }
    }
}

double computeHighPrice(std::vector<OrderBookEntry> &entries)
{
    double highestPrice{entries[0].price};
    for (auto &entry : entries)
    {
        if (highestPrice < entry.price)
        {
            highestPrice = entry.price;
        }
    }
}

double computePriceSpread(std::vector<OrderBookEntry> &entries)
{
    double priceSpread{computeHighPrice(entries) - computeLowPrice(entries)};
}

int main()
{
    OrderBookEntry obe1("2020/03/17 17:01:24", "ETH/BTC", OrderBookType::bid, 0.02187308, 0.44564869);
    OrderBookEntry obe2("2020/03/17 17:01:24", "ETH/BTC", OrderBookType::ask, 0.02189308, 0.44564869);

    // A vector is a sequence container that can dynamically grow or shrink in size.
    // It's similar to an array, but with the ability to resize itself automatically as elements are inserted or removed.
    // The vector class is defined in the <vector> header file.
    std::vector<OrderBookEntry> entries;
    entries.push_back(obe1);
    entries.push_back(obe2);
    for (auto &entry : entries)
    {
        std::cout << entry.price << std::endl;
    }

    while (true)
    {
        pirntMenu();
        userChoice();
    }
    return 0;
}