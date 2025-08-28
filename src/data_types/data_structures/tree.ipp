#include "tree.h"

#include "parent.h"
#include "child.h"
#include "list/node.h"

#include "src/data_types/project_types/bus.h"
#include "src/data_types/project_types/car.h"
#include "src/data_types/project_types/airplane.h"
#include "src/data_types/project_types/helicopter.h"
#include "src/data_types/project_types/metro.h"

namespace {
using ::App::Types::DataTypes::DoublyLinkedListList::Node;
using ::App::Types::Project::Transport;
using ::App::Types::Project::Enum::TransportType;
} // namespace

namespace App::Types::DataTypes {
template <typename T>
void Tree::saveTransportData(std::ofstream& os, const Parent<::App::Types::Project::Transport>* parent, std::string&& trTypeName) const {
    using std::endl;

    os << trTypeName << endl;
    for (const auto& child : *parent) {
        os << child->getKey() << endl;
        os << dynamic_cast<const T&>(*child->getChild());
    }
}

template <typename T>
void Tree::loadTransportData(std::ifstream& is, ::App::Types::Project::Enum::TransportType trType, Tree& t) const {
    std::string line;
    do {
        getline(is, line);
        T* transport = new T;
        is >> *transport;
        t.add(line, transport, trType);
        is.get();
    } while (is.peek() != '\n' && !is.eof());
    if (!is.eof())
        is.get();
}

inline Tree::Tree() : parents_(), count_() {}
} // namespace App::Types::DataTypes
