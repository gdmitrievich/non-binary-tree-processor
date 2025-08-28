#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include "src/data_types/project_types/transport_type.h"

namespace App::Utility {
namespace FileManagment {
template <typename T>
void Load(const QString& path, T& data);

template <typename T>
void Save(const QString& path, const T& data);
}

namespace TransportType {
::App::Types::Project::Enum::TransportType strToTransportType(QString str);
QString transportTypeToStr(::App::Types::Project::Enum::TransportType trType);
}
}

#include "src/utility/utility.ipp"

#endif // UTILITY_H
