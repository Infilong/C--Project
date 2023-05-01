#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::string token;
    separator = ',';
    int start, end;

    start = csvLine.find_first_not_of(separator, 0);

    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
        {
            break;
        }

        if (end >= 0)
        {
            token = csvLine.substr(start, end - start);
        }
        else
        {
            token = csvLine.substr(start, csvLine.length() - start);
        }
        tokens.push_back(token);
        start = end + 1;
    } while (end != std::string::npos);
    return tokens;
}

int main()
{
    std::string csvFilename{"tradingData.csv"};
    std::ifstream csvFile{csvFilename};
    std::string line;

    std::string timeStamp;
    std::string tradingPair;
    std::string orderType;
    double price;
    double amount;

    int lineCount = 0;

    if (csvFile.is_open())
    {
        std::cout << "Opened file\n"
                  << csvFilename << std::endl;
    }
    else
    {
        std::cout << "Problem opening file\n"
                  << csvFilename << std::endl;
    }

    while (std::getline(csvFile, line))
    {
        // Check if line is empty
        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> tokens = tokenise(line, ',');
        // Check if line has 5 tokens
        if (tokens.size() != 5)
            continue;

        // Try to catch data errors
        try
        {
            timeStamp = tokens[0];
            tradingPair = tokens[1];
            orderType = tokens[2];
            price = std::stod(tokens[3]);
            amount = std::stod(tokens[4]);
        }
        catch (const std::exception &e)
        {
            continue;
        }
        lineCount++;

        std::cout << "Read " << tokens.size() << " tokens " << std::endl;
        std::cout << "Line " << lineCount << " : " << timeStamp << "\n"
                  << tradingPair << "\n"
                  << orderType << "\n"
                  << price << "\n"
                  << amount << std::endl;
    }
    csvFile.close();
    return 0;
}
