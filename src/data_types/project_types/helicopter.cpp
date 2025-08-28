#include "helicopter.h"

namespace App::Types::Project {
Helicopter::Helicopter() : AirTransport(), noseLength_() {}

Helicopter::Helicopter(const Helicopter& t) : AirTransport(t) {
    noseLength_ = t.noseLength_;
}

Helicopter::Helicopter(const std::string& model, int yearOfRelease, int maxHeight,
                   int amountOfPropellers, int noseLength) :
    AirTransport(model, yearOfRelease, maxHeight, amountOfPropellers),
    noseLength_(noseLength) {}

void Helicopter::start() const noexcept {
    std::cout << "The helicopter started its engines!" << std::endl;
}

void Helicopter::stop() const noexcept {
    std::cout << "The helicopter turned off its engines!" << std::endl;
}

void Helicopter::fly() const noexcept {
    std::cout << "Helicopter in the air!" << std::endl;
}

void Helicopter::helicopter() const noexcept {
    std::cout << "You are flying on an helicopter!" << std::endl;
}


std::ostream& operator<<(std::ostream& os, const Helicopter& t) {
    os << (AirTransport&) t;
    os << "nose_length: " << t.noseLength_ << std::endl;

	return os;
}
std::istream& operator>>(std::istream& is, Helicopter& t) {
    is >> (AirTransport&) t;
    while (!t.setUserAnswer("Write the noseLength: ", t.noseLength_)) {}

	return is;
}

std::ifstream& operator>>(std::ifstream& is, Helicopter& t) {
    is >> (AirTransport&) t;
    t.setDataFromLine(is, t.noseLength_);

    return is;
}
} // namespace App::Types::Project
