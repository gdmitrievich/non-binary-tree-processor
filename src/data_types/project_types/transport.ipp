#include "transport.h"

namespace App::Types::Project {
inline ::std::string Transport::getModel() const noexcept {
    return model_;
}

inline int Transport::getYearOfRelease() const noexcept {
    return yearOfRelease_;
}

template <typename T>
void Transport::setDataFromLine(::std::ifstream& is, T& field) {
    while (is.get() != ' ');
    is >> field;
}
} // namespace App::Types::Project
