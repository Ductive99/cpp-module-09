#include "PmergeMe.hpp"

static bool readUnsignedInt(unsigned int& result, char *input);
static bool printError(char *input, char *endptr, const char *message);

int populateVector(std::vector<unsigned>& vec, int ac, char **av)
{
    vec.reserve(ac);

    for (int i = 0; i < ac; i++)
    {
        unsigned int value;
        if (!readUnsignedInt(value, av[i]))
            return 0;
        vec.push_back(value);
    }
    return 1;

}

static bool readUnsignedInt(unsigned int& result, char *input) {
    char* endPtr;
    errno = 0;

    unsigned long val = std::strtoul(input, &endPtr, 10);

    if (errno == ERANGE)
        return (printError(input, 0, "Math result not representable"));
    if (val > UINT_MAX)
        return printError(input, &input[static_cast<std::string>(input).find('-')], "Negative value.");

    if (endPtr == input)
        return (printError(input, 0, "Invalid Input"));

    while (*endPtr != '\0') {
        if (!isspace(*endPtr)) return printError(input, endPtr, "Invalid Value.");
        endPtr++;
    }

    if (static_cast<std::string>(input).find('-') != std::string::npos) {
        return printError(0, 0, "Negative value.");
    }

    result = static_cast<unsigned int>(val);
    return true;
}

static bool printError(char *input, char *endptr, const char *message) {
    std::cerr << "Error: ";
    if (message)
        std::cerr << message;
    std::cerr << std::endl;

    if (input)
        std::cerr << input << std::endl;

    if (endptr) {
        for (int i = 0; i < endptr - input; i++)
            std::cerr << " ";
        std::cerr << "^-- right here." << std::endl;
    }

    return false;
}
