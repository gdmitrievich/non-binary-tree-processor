#include "underground_transport.h"

#include <iostream>

namespace App::Types::Project {
UndergroundTransport::UndergroundTransport() : Transport(), numberOfWheelsets_() {}
UndergroundTransport::UndergroundTransport(const UndergroundTransport& t) :
    Transport(t) {
    numberOfWheelsets_ = t.numberOfWheelsets_;
}

UndergroundTransport::UndergroundTransport(const std::string& model, int yearOfRelease,
                                 int numberOfWheelsets) :
    Transport(model, yearOfRelease),
    numberOfWheelsets_(numberOfWheelsets) {}

std::ostream& operator<<(std::ostream& os, const UndergroundTransport& t) {
    os << (Transport&) t;
    os << "number_of_wheelsets: " << t.numberOfWheelsets_ << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, UndergroundTransport& t) {
    is >> (Transport&) t;
    while (!t.setUserAnswer("Write the number of wheelsets: ",
                                     t.numberOfWheelsets_)) {}

    return is;
}

std::ifstream& operator>>(std::ifstream& is, UndergroundTransport& t) {
    is >> (Transport&) t;
    t.setDataFromLine(is, t.numberOfWheelsets_);

    return is;
}
} // namespace App::Types::Project
