#include "bus.h"

namespace App::Types::Project {
Bus::Bus() : GroundTransport(), amountOfPassengers_() {}

Bus::Bus(const Bus& t) : GroundTransport(t) {
    amountOfPassengers_ = t.amountOfPassengers_;
}

Bus::Bus(const std::string& model, int yearOfRelease, int amountOfWheels,
         int amountOfPassengers) :
    GroundTransport(model, yearOfRelease, amountOfWheels),
    amountOfPassengers_(amountOfPassengers) {}

void Bus::start() const noexcept {
    std::cout << "The bus started its engines!" << std::endl;
}

void Bus::stop() const noexcept {
    std::cout << "The bus turned off its engines!" << std::endl;
}

void Bus::ride() const noexcept {
    std::cout << "The bus in the road!" << std::endl;
}

void Bus::bus() const noexcept {
    std::cout << "You're on the bus!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Bus& t) {
    os << (GroundTransport&) t;
    os << "amount_of_passengers: " << t.amountOfPassengers_ << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, Bus& t) {
    is >> (GroundTransport&) t;
    while (!t.setUserAnswer("Write the amountOfPassengers: ",
                                     t.amountOfPassengers_)) {}

    return is;
}

std::ifstream& operator>>(std::ifstream& is, Bus& t) {
    is >> (GroundTransport&) t;
    t.setDataFromLine(is, t.amountOfPassengers_);

    return is;
}
} // namespace App::Types::Project
