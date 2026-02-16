#include "BitcoinExchange.hpp"
#include <stdlib.h>

Date parseDate(const std::string &dateStr)
{
    Date d;
    char dash;
    std::stringstream ss(dateStr);

    ss >> d.year >> dash >> d.month >> dash >> d.day;
    return d;
}

std::string trim(const std::string &str)
{
    size_t start = 0;
    size_t end = str.length();

    while (start < end && std::isspace(str[start]))
    {
        start++;
    }

    while (end > start && std::isspace(str[end - 1]))
    {
        end--;
    }

    return str.substr(start, end - start);
}

std::vector<ExchangeRecord> readCSV(const std::string &filename)
{
    std::vector<ExchangeRecord> records;
    std::ifstream file(filename.c_str());

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
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
            record.date = parseDate(dateStr);
            record.rate = rateVal;

            records.push_back(record);
        }
    }

    file.close();
    return records;
}

bool isValidDate(const Date &d)
{
    if (d.year < 0 || d.month < 1 || d.month > 12 || d.day < 1 || d.day > 31)
    {
        return false;
    }

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (d.month == 2 && d.year % 4 == 0 && (d.year % 100 != 0 || d.year % 400 == 0))
    {
        if (d.day > 29)
            return false;
    }
    else if (d.day > daysInMonth[d.month - 1])
    {
        return false;
    }

    return true;
}

bool findExchangeRate(const std::vector<ExchangeRecord>& database, const Date& date, double& rate) {
    int targetDateInt = date.toInt();
    int closestDateInt = -1;
    double closestRate = 0.0;
    bool found = false;
    
    for (size_t i = 0; i < database.size(); ++i) {
        int dbDateInt = database[i].date.toInt();
        
        if (dbDateInt <= targetDateInt) {
            if (!found || dbDateInt > closestDateInt) {
                closestDateInt = dbDateInt;
                closestRate = database[i].rate;
                found = true;
            }
        }
    }
    
    if (found) {
        rate = closestRate;
        std::cout << closestDateInt;
        return true;
    }
    
    return false;
}

void parseInputFile(const std::string &filename, const std::vector<ExchangeRecord> &database)
{
    std::ifstream file(filename.c_str());

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string dateStr = trim(line.substr(0, pipePos));
        std::string valueStr = trim(line.substr(pipePos + 1));

        Date date = parseDate(dateStr);
        if (!isValidDate(date))
        {
            std::cerr << "Error: invalid date => " << dateStr << std::endl;
            continue;
        }

        char *endptr;
        double value = std::strtod(valueStr.c_str(), &endptr);

        if (*endptr != '\0' && !std::isspace(*endptr))
        {
            std::cerr << "Error: invalid value => " << valueStr << std::endl;
            continue;
        }

        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
    
        double exchangeRate;
        if (findExchangeRate(database, date, exchangeRate)) {
            std::cout << " >" << exchangeRate << "< ";
            double result = value * exchangeRate;
            std::cout << dateStr << " => " << value << " = " << result << std::endl;
        } else {
            std::cerr << "Error: no exchange rate available for date => " << dateStr << std::endl;
        }
    }

    file.close();
}

