#include "string_buffer.hpp"

void StringBuffer::PushString(const std::string &s) {
    std::unique_lock<std::mutex> lock(this->bufferMutex);
    this->bufferCondition.wait(lock,[this]{return this->isEmpty();});
    this->setBuffer(s);
    this->bufferCondition.notify_one();
}

std::string StringBuffer::PopString() {
    std::unique_lock<std::mutex> lock(this->bufferMutex);
    this->bufferCondition.wait(lock,[this]{return !this->isEmpty();});
    std::string s = this->getBuffer();
    this->clearBuffer();
    this->bufferCondition.notify_one();
    return s;
}

void StringBuffer::clearBuffer() {
    this->bufferString.clear();
}

bool StringBuffer::isEmpty() const {
    return (this->getBuffer().length() == 0);
}
