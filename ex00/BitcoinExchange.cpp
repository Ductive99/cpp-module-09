#include "BitcoinExchange.hpp"

Date parseDate(const std::string& dateStr) {
    Date d;
    char dash;
    std::stringstream ss(dateStr);
    
    ss >> d.year >> dash >> d.month >> dash >> d.day;
    return d;
}