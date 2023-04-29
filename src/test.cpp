#include <string>
#include <vector>
#include <iostream>

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
    } while (
        end > 0);
    return tokens;
}

int main()
{
    std::string s = "hello,I,have three tokens";
    std::vector<std::string> tokens = tokenise(s, ',');
    
    for (const std::string &t : tokens)
    {
        std::cout << t << std::endl;
    }
}
