#include "tree.h"

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
using fi_value_type = Parent<::App::Types::Project::Transport>*;
App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<fi_value_type>::ForwardIterator Tree::begin() {return parents_.begin();}
App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<fi_value_type>::ForwardIterator Tree::end() {return parents_.end();}
App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<fi_value_type>::ForwardIterator Tree::begin() const {return parents_.begin();}
App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<fi_value_type>::ForwardIterator Tree::end() const {return parents_.end();}

Parent<Transport>* Tree::getParentPtrByItsType(
    TransportType transportType) const noexcept {
    for (const auto& parentPtr : parents_) {
        if (parentPtr->getTransportType() == transportType)
            return parentPtr;
    }

    return nullptr;
}

inline Parent<::App::Types::Project::Transport>* Tree::getParentPtrByItsType(
    TransportType transportType, ::std::size_t& idx) const noexcept {
    for (const auto& parentPtr : parents_) {
        if (parentPtr->getTransportType() == transportType)
            return parentPtr;
        ++idx;
    }

    return nullptr;
}

Transport* Tree::search(const ::std::string& key,
                        TransportType transportType) const noexcept {
    Parent<Transport>* parentPtr = getParentPtrByItsType(transportType);
    if (!parentPtr)
        return nullptr;

    return parentPtr->search(key);
}

bool Tree::add(const ::std::string& key, const Transport* value,
               TransportType transportType, int idx) {
    Parent<Transport>* parentPtr = getParentPtrByItsType(transportType);
    if (!parentPtr) {
        parentPtr = new Parent<Transport>(transportType);
        bool isAdded = parentPtr->add(key, value);
        parents_.pushBack(parentPtr);
        ++count_;
        return isAdded;
    }

    return parentPtr->add(key, value, idx);
}

bool Tree::addParent(::App::Types::Project::Enum::TransportType transportType, int idx) noexcept {
    Parent<Transport>* parentPtr = getParentPtrByItsType(transportType);
    if (parentPtr)
        return false;

    if (idx == -1)
        parents_.pushBack(new Parent<Transport>(transportType));
    else
        parents_.insert(idx, new Parent<Transport>(transportType));

    ++count_;
    return true;
}

bool Tree::remove(const ::std::string& key,
                  TransportType transportType) noexcept {
    Parent<Transport>* parentPtr = getParentPtrByItsType(transportType);
    if (!parentPtr)
        return false;

    if (!parentPtr->remove(key))
        return false;

    if (parentPtr->count() == 0)
        removeParent(transportType);

    return true;
}

bool Tree::removeParent(TransportType transportType) noexcept {
    ::std::size_t idx {};
    Parent<Transport>* parentPtr = getParentPtrByItsType(transportType, idx);
    if (!parentPtr)
        return false;

    parentPtr->clear();
    parents_.erase(idx);
    --count_;
    return true;
}

void Tree::clear() noexcept {
    for (auto& parentPtr : *this) {
        if (parentPtr)
            parentPtr->clear();
    }
    parents_.clear();
    count_ = 0;
}

std::size_t Tree::count() const {
    return count_;
}

std::ofstream& operator<<(std::ofstream& os, const Tree& t) {
    namespace enumT = ::App::Types::Project::Enum;
    namespace projectT = ::App::Types::Project;

    for (auto itBegin = t.begin(); itBegin != t.end(); ++itBegin) {
        const auto& parent = *itBegin;
        switch (parent->getTransportType()) {
            case enumT::Bus:
                t.saveTransportData<projectT::Bus>(os, parent, "bus");
                break;
            case enumT::Car:
                t.saveTransportData<projectT::Car>(os, parent, "car");
                break;
            case enumT::Airplane:
                t.saveTransportData<projectT::Airplane>(os, parent, "airplane");
                break;
            case enumT::Helicopter:
                t.saveTransportData<projectT::Helicopter>(os, parent, "helicopter");
                break;
            case enumT::Metro:
                t.saveTransportData<projectT::Metro>(os, parent, "metro");
                break;
        }

        if (itBegin.next(itBegin) != t.end()) {
            os << std::endl;
        }
    }

    return os;
}

std::ifstream& operator>>(std::ifstream& is, Tree& t) {
    namespace enumT = ::App::Types::Project::Enum;
    namespace projectT = ::App::Types::Project;

    std::string line;
    while (!is.eof()) {
        getline(is, line);
        if (line == "bus") {
            t.loadTransportData<projectT::Bus>(is, enumT::Bus, t);
        } else if (line == "car") {
            t.loadTransportData<projectT::Car>(is, enumT::Car, t);
        } else if (line == "airplane") {
            t.loadTransportData<projectT::Airplane>(is, enumT::Airplane, t);
        } else if (line == "helicopter") {
            t.loadTransportData<projectT::Helicopter>(is, enumT::Helicopter, t);
        } else if (line == "metro") {
            t.loadTransportData<projectT::Metro>(is, enumT::Metro, t);
        }
    }

    return is;
}
} // namespace App::Types::DataTypes
