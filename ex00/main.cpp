#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    std::map<int, double> records;

    if (ac != 2)
    {
        std::cout << "Invalid Arguments!" << std::endl;
        std::cout << "Usage: " << av[0] << " <input_file>" << std::endl;
        return 1;
    }

    readCSV(records, "data.csv");
    if (records.size() == 0)
        return 2;

    std::cout << "Total records read: " << records.size() << std::endl;

    parseInputFile(av[1], records);

    return 0;
}
