#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <algorithm>

std::string trim(const std::string &str)
{
    size_t start = 0;
    size_t end = str.length();

    while (start < end && std::isspace(str[start])) {
        start++;
    }

    while (end > start && std::isspace(str[end - 1])) {
        end--;
    }

    return str.substr(start, end - start);
}

int parseDateToInt(const std::string& dateStr) {
    int year, month, day;
    char dash;
    std::stringstream ss(dateStr);
    
    ss >> year >> dash >> month >> dash >> day;
    
    return year * 10000 + month * 100 + day;
}

bool compareExchangeRecords(const ExchangeRecord& a, const ExchangeRecord& b) {
    return a.date < b.date;
}

bool compareRecordWithInt(const ExchangeRecord& rec, int targetDate) {
    return rec.date < targetDate;
}

std::vector<ExchangeRecord> readCSV(const std::string &filename)
{
    std::vector<ExchangeRecord> records;
    std::ifstream file(filename.c_str());

    if (!file.is_open()) {
        std::cerr << "Error: could not open database file." << std::endl;
        return records;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string dateStr;

        if (std::getline(ss, dateStr, ','))
        {
            double rateVal;
            ss >> rateVal;

            ExchangeRecord record;
            record.date = parseDateToInt(dateStr);
            record.rate = rateVal;

            records.push_back(record);
        }
    }
    file.close();

    std::sort(records.begin(), records.end(), compareExchangeRecords);

    return records;
}

bool isValidDate(int date)
{
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2) {
        bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (isLeap) {
            if (day > 29) return false;
        } else {
            if (day > 28) return false;
        }
    } else {
        if (day > daysInMonth[month - 1])
            return false;
    }

    return true;
}

bool findExchangeRate(const std::vector<ExchangeRecord>& database, int targetDate, double& rate) {
    std::vector<ExchangeRecord>::const_iterator it;

    it = std::lower_bound(database.begin(), database.end(), targetDate, compareRecordWithInt);

    if (it != database.end() && it->date == targetDate) {
        rate = it->rate;
        return true;
    }

    if (it != database.begin()) {
        --it;
        rate = it->rate;
        return true;
    }

    return false;
}

void parseInputFile(const std::string &filename, const std::vector<ExchangeRecord> &database)
{
    std::ifstream file(filename.c_str());

    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string dateStr = trim(line.substr(0, pipePos));
        std::string valueStr = trim(line.substr(pipePos + 1));

        int dateInt = parseDateToInt(dateStr);
        if (!isValidDate(dateInt)) {
            std::cerr << "Error: bad input => " << dateStr << std::endl;
            continue;
        }

        char *endptr;
        double value = std::strtod(valueStr.c_str(), &endptr);

        if (*endptr != '\0') {
            std::cerr << "Error: bad input => " << valueStr << std::endl;
            continue;
        }

        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
    
        double rate;
        if (findExchangeRate(database, dateInt, rate)) {
            double result = value * rate;
            std::cout << dateStr << " => " << value << " = " << result << std::endl;
        } else {
            std::cerr << "Error: no exchange rate available for date => " << dateStr << std::endl;
        }
    }

    file.close();
}