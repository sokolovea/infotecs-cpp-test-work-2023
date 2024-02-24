#pragma once
#include <string>
#include <algorithm>

class StringHandler
{
    public:
        static bool isStringCorrect (const std::string s);
        static void sortStringInDesc(std::string &s);
        static void replaceEvenNumbers(std::string &s);
        static int charToInt(char symbol);
        static int sumDigits(const std::string &s);

    private:
        StringHandler();
        static bool isLengthCorrect(const std::string s, long long unsigned int maxLength);
        static bool isOnlyDigit(const std::string s);
        static const long long unsigned int maxLength = 64;
};
