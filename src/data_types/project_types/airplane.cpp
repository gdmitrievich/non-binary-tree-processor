#include "airplane.h"

namespace App::Types::Project {
Airplane::Airplane() : AirTransport(), wingspan_() {}

Airplane::Airplane(const Airplane& t) : AirTransport(t) {
    wingspan_ = t.wingspan_;
}

Airplane::Airplane(const std::string& model, int yearOfRelease, int maxHeight,
                   int amountOfPropellers, int wingspan) :
    AirTransport(model, yearOfRelease, maxHeight, amountOfPropellers),
    wingspan_(wingspan) {}

void Airplane::start() const noexcept {
    std::cout << "The airplane started its engines!" << std::endl;
}

void Airplane::stop() const noexcept {
    std::cout << "The airplane turned off its engines!" << std::endl;
}

void Airplane::fly() const noexcept {
    std::cout << "Airplane in the air!" << std::endl;
}

void Airplane::airplane() const noexcept {
    std::cout << "You are flying on an airplane!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Airplane& t) {
    os << (AirTransport&) t;
    os << "wingspan: " << t.wingspan_ << std::endl;

	return os;
}
std::istream& operator>>(std::istream& is, Airplane& t) {
    is >> (AirTransport&) t;
    while (!t.setUserAnswer("Write the wingspan: ", t.wingspan_)) {}

	return is;
}

std::ifstream& operator>>(std::ifstream& is, Airplane& t) {
    is >> (AirTransport&) t;
    t.setDataFromLine(is, t.wingspan_);

    return is;
}
} // namespace App::Types::Project
