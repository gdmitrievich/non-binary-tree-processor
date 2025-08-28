#include "utility.h"

#include <fstream>
#include <QMessageBox>

namespace App::Utility {
namespace FileManagment {
template <typename T>
void Load(const QString& path, T& data) {
    std::ifstream iStream(path.toStdString());

    if (!iStream.is_open()) {
        iStream.close();
        return;
    }

    iStream >> data;
    iStream.close();
}

template <typename T>
void Save(const QString& path, const T& data){
    std::ofstream oStream(path.toStdString());

    if (!oStream.is_open()) {
        oStream.close();
        return;
    }

    oStream << data;
    oStream.close();
}
}
}
