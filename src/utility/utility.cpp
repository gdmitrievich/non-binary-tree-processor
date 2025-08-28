#include "utility.h"

namespace App::Utility {
namespace TransportType {
::App::Types::Project::Enum::TransportType strToTransportType(QString str) {
    using ::App::Types::Project::Enum::TransportType;

    if (str.toLower() == "bus") {
        return TransportType::Bus;
    } else if (str.toLower() == "car") {
        return TransportType::Car;
    } else if (str.toLower() == "airplane") {
        return TransportType::Airplane;
    } else if (str.toLower() == "helicopter") {
        return TransportType::Helicopter;
    } else if (str.toLower() == "metro") {
        return TransportType::Metro;
    } else {
        return TransportType::Default;
    }
}

QString transportTypeToStr(::App::Types::Project::Enum::TransportType trType) {
    using ::App::Types::Project::Enum::TransportType;

    switch (trType) {
        case TransportType::Bus:
            return QString("bus");
        case TransportType::Car:
            return QString("car");
        case TransportType::Airplane:
            return QString("airplane");
        case TransportType::Helicopter:
            return QString("helicopter");
        case TransportType::Metro:
            return QString("metro");
        default:
            return QString("default");
    }
}
}
}
