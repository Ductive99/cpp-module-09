#ifndef BITCOINEXCHANGE_HPP_
#define BITCOINEXCHANGE_HPP_

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

struct Date {
    int year;
    int month;
    int day;
};

struct ExchangeRecord {
    Date date;
    double rate;
};

Date parseDate(const std::string& dateStr);
std::vector<ExchangeRecord> readCSV(const std::string& filename);

#endif /* BITCOINEXCHANGE_HPP_ */