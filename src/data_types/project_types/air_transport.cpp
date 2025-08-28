#include "air_transport.h"

#include <iostream>

namespace App::Types::Project {
AirTransport::AirTransport() : Transport(), maxHeight_(), amountOfPropellers_() {}

AirTransport::AirTransport(const AirTransport& t) : Transport(t) {
    maxHeight_ = t.maxHeight_;
    amountOfPropellers_ = t.amountOfPropellers_;
}

AirTransport::AirTransport(const std::string& model, int yearOfRelease,
                           int maxHeight, int amountOfPropellers) :
    Transport(model, yearOfRelease),
    maxHeight_(maxHeight),
    amountOfPropellers_(amountOfPropellers) {}

std::ostream& operator<<(std::ostream& os, const AirTransport& t) {
    os << (Transport&) t;
    os << "max_height: " << t.maxHeight_ << std::endl;
    os << "amount_of_propellers: " << t.amountOfPropellers_ << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, AirTransport& t) {
    is >> (Transport&) t;
    t.setUserAnswer("Write the max height: ", t.maxHeight_);
    while (!t.setUserAnswer("Write the amount of propellers: ",
                                     t.amountOfPropellers_)) {}

    return is;
}

std::ifstream& operator>>(std::ifstream& is, AirTransport& t) {
    is >> (Transport&) t;
    t.setDataFromLine(is, t.maxHeight_);
    t.setDataFromLine(is, t.amountOfPropellers_);

    return is;
}
} // namespace App::Types::Project
