#ifndef BITCOINEXCHANGE_HPP_
#define BITCOINEXCHANGE_HPP_

#include <string>
#include <sstream>

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
void read_data(ExchangeRecord &records);

#endif /* BITCOINEXCHANGE_HPP_ */