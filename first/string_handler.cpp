#include "string_handler.hpp"

bool StringHandler::isLengthCorrect(const std::string s, long long unsigned int maxLength)
{
    if (s.length() <= maxLength && s.length() != 0) {
        return true;
    }
    return false;
}

bool StringHandler::isOnlyDigit(const std::string s)
{
    for (char const c: s) {
        if (not isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool StringHandler::isStringCorrect(const std::string s)
{
    if (StringHandler::isLengthCorrect(s, StringHandler::maxLength) and StringHandler::isOnlyDigit(s)) {
        return true;
    }
    return false;
}

void StringHandler::sortStringInDesc(std::string &s)
{
    std::sort(s.rbegin(), s.rend());
}

void StringHandler::replaceEvenNumbers(std::string &s)
{
    std::string newString;
    newString.reserve(s.length() + 1);
    for (char each : s) {
        if ((each - '0') % 2 == 0) {
            newString.append("KB");
        }
        else {
            newString += each;
        }
    }
    s = newString;
}

int StringHandler::charToInt(char symbol) {
    return symbol - '0';
}

int StringHandler::sumDigits(const std::string &s) {
    int sum = 0;
    for (char each : s) {
        if (isdigit(each)) {
            sum += StringHandler::charToInt(each);
        }
    }
    return sum;
}
