#include "transport.h"

#include <cctype>
#include <iostream>
#include <string>

namespace App::Types::Project {
void Transport::setUserAnswer(const char* message, ::std::string& field) {
    std::cout << message;
    std::getline(std::cin, field);
}

bool Transport::setUserAnswer(const char* message, int& field) {
    std::cout << message;
    
    ::std::string str;
    (::std::cin >> str).get();
    int i {};
    ::std::size_t size = str.size();
    while (i < size && ::std::isdigit(str[i++])) {}
    if (i == size) {
        field = stoi(str);
    } else {
        ::std::cout << "You need to write a number!" << ::std::endl;
        return false;
    }
    return true;
}

Transport::Transport() : model_(), yearOfRelease_() {}

Transport::Transport(const Transport& t) {
    model_ = t.model_;
    yearOfRelease_ = t.yearOfRelease_;
}

Transport::Transport(const std::string& model, int yearOfRelease) :
    model_(model),
    yearOfRelease_(yearOfRelease) {}

Transport::~Transport() noexcept {}

std::ostream& operator<<(std::ostream& os, const Transport& t) {
    os << "model: " << t.model_ << std::endl;
    os << "year_of_release: " << t.yearOfRelease_ << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, Transport& t) {
    Transport::setUserAnswer("Write the model: ", t.model_);
    while (!Transport::setUserAnswer("Write the year of release: ", t.yearOfRelease_)) {}

    return is;
}

std::ifstream& operator>>(std::ifstream& is, Transport& t) {
    t.setDataFromLine(is, t.model_);
    t.setDataFromLine(is, t.yearOfRelease_);

    return is;
}
} // namespace App::Types::Project
