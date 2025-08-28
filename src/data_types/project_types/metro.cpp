#include "metro.h"

namespace App::Types::Project {
Metro::Metro() : UndergroundTransport(), numberOfWagons_() {}

Metro::Metro(const Metro& t) : UndergroundTransport(t) {
    numberOfWagons_ = t.numberOfWagons_;
}

Metro::Metro(const std::string& model, int yearOfRelease, int amountOfWheelsets,
             int numberOfWagons) :
    UndergroundTransport(model, yearOfRelease, amountOfWheelsets),
    numberOfWagons_(numberOfWagons) {}

void Metro::start() const noexcept {
    std::cout << "The train started its engines!" << std::endl;
}

void Metro::stop() const noexcept {
    std::cout << "The train turned off its engines!" << std::endl;
}

void Metro::slide() const noexcept {
    std::cout << "The train started moving!" << std::endl;
}

void Metro::metro() const noexcept {
    std::cout << "You're on the train!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Metro& t) {
    os << (UndergroundTransport&) t;
    os << "number_of_wagons: " << t.numberOfWagons_ << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, Metro& t) {
    is >> (UndergroundTransport&) t;
    while (!t.setUserAnswer("Write the number of wagons: ",
                                     t.numberOfWagons_)) {}

    return is;
}

std::ifstream& operator>>(std::ifstream& is, Metro& t) {
    is >> (UndergroundTransport&) t;
    t.setDataFromLine(is, t.numberOfWagons_);

    return is;
}
} // namespace App::Types::Project
