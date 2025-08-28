#include "ground_transport.h"

#include <iostream>

namespace App::Types::Project {
GroundTransport::GroundTransport() : Transport(), amountOfWheels_() {}

GroundTransport::GroundTransport(const GroundTransport& t) : Transport(t) {
    amountOfWheels_ = t.amountOfWheels_;
}

GroundTransport::GroundTransport(const std::string& model, int yearOfRelease,
                                 int amountOfWheels) :
    Transport(model, yearOfRelease),
    amountOfWheels_(amountOfWheels) {}

std::ostream& operator<<(std::ostream& os, const GroundTransport& t) {
    os << (Transport&) t;
    os << "amount_of_wheels: " << t.amountOfWheels_ << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, GroundTransport& t) {
    is >> (Transport&) t;
    while (!t.setUserAnswer("Write the amount of wheels: ",
                                     t.amountOfWheels_)) {}

    return is;
}

std::ifstream& operator>>(std::ifstream& is, GroundTransport& t) {
    is >> (Transport&) t;
    t.setDataFromLine(is, t.amountOfWheels_);

    return is;
}
} // namespace App::Types::Project
