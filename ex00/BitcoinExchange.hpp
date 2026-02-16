#ifndef BITCOINEXCHANGE_HPP_
#define BITCOINEXCHANGE_HPP_

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

struct Date
{
    int year;
    int month;
    int day;
};

struct ExchangeRecord
{
    int date;
    double rate;
};

std::vector<ExchangeRecord> readCSV(const std::string &filename);
void parseInputFile(const std::string &filename, const std::vector<ExchangeRecord> &database);

#endif /* BITCOINEXCHANGE_HPP_ */