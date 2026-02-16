#include "BitcoinExchange.hpp"

Date parseDate(const std::string& dateStr) {
    Date d;
    char dash;
    std::stringstream ss(dateStr);
    
    ss >> d.year >> dash >> d.month >> dash >> d.day;
    return d;
}

std::vector<ExchangeRecord> readCSV(const std::string& filename) {
    std::vector<ExchangeRecord> records;
    std::ifstream file(filename.c_str());
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return records;
    }
    
    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string dateStr;
        
        if (std::getline(ss, dateStr, ',')) {
            double rateVal;
            ss >> rateVal;

            ExchangeRecord record;
            record.date = parseDate(dateStr);
            record.rate = rateVal;
            
            records.push_back(record);
        }
    }
    
    file.close();
    return records;
}