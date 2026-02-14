#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main(int ac, char **av)
{
    std::ifstream file("data.csv");
    std::vector<ExchangeRecord> records;

    if (ac != 2)
    {
        std::cout << "Invalid Arguments!" << std::endl;
        std::cout << "Usage: " << av[0] << " <input_file>" << std::endl;
        return (1);
    }
    if (!file.is_open()) {
        std::cout << "Error: can't open file" << std::endl;
        return (2);
    }

    // Read Data.csv


    // Read input file

    // Check for value stored in records
}