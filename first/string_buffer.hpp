#pragma once
#include <string>
#include <mutex>
// #include <memory>
#include <iostream>
#include <condition_variable>

class StringBuffer
{
    public:
        void PushString(const std::string &s);
        std::string PopString();
    private:
        std::string bufferString;
        mutable std::mutex bufferMutex;
        std::condition_variable bufferCondition;
        std::string getBuffer() const {return this->bufferString;}
        void setBuffer(const std::string &s) {this->bufferString = s;}
        void clearBuffer();
        bool isEmpty() const;
};