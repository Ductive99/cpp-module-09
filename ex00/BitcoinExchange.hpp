#ifndef BITCOINEXCHANGE_HPP_
#define BITCOINEXCHANGE_HPP_

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>

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

std::map<int, double> &readCSV(std::map<int, double>& records, const std::string &filename);
void parseInputFile(const std::string &filename, const std::map<int, double> &database);

#endif /* BITCOINEXCHANGE_HPP_ */
