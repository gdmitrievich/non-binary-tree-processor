#include "car.h"

namespace App::Types::Project {
Car::Car() : GroundTransport(), trunkCapacity_() {}

Car::Car(const Car& t) : GroundTransport(t) {
    trunkCapacity_ = t.trunkCapacity_;
}

Car::Car(const std::string& model, int yearOfRelease, int amountOfWheels,
         int trunkСapacity) :
    GroundTransport(model, yearOfRelease, amountOfWheels),
    trunkCapacity_(trunkСapacity) {}

void Car::start() const noexcept {
    std::cout << "The car started its engines!" << std::endl;
}

void Car::stop() const noexcept {
    std::cout << "The car turned off its engines!" << std::endl;
}

void Car::ride() const noexcept {
    std::cout << "The car in the road!" << std::endl;
}

void Car::car() const noexcept {
    std::cout << "You're on the car!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Car& t) {
    os << (GroundTransport&) t;
    os << "trunk_capacity: " << t.trunkCapacity_ << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, Car& t) {
    is >> (GroundTransport&) t;
    while (!t.setUserAnswer("Write the trunk capacity: ",
                                     t.trunkCapacity_)) {}

    return is;
}

std::ifstream& operator>>(std::ifstream& is, Car& t) {
    is >> (GroundTransport&) t;
    t.setDataFromLine(is, t.trunkCapacity_);

    return is;
}
} // namespace App::Types::Project
