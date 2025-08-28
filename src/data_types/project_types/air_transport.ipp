#include "air_transport.h"

namespace App::Types::Project {
inline int AirTransport::getMaxHeight() const noexcept {
    return maxHeight_;
}

inline int AirTransport::getAmountOfPropellers() const noexcept {
    return amountOfPropellers_;
}
}