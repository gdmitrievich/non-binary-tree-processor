#include "parent.h"

#include <cstddef>

#include "child.h"
#include "list/node.h"

namespace {
namespace Project = ::App::Types::Project;
namespace DataTypes = ::App::Types::DataTypes;
using Project::Enum::TransportType;
using DataTypes::DoublyLinkedListList::Node;
}

namespace App::Types::DataTypes {
template <typename T>
typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Child<T>*>::ForwardIterator App::Types::DataTypes::Parent<T>::begin() {return children_.begin();}
template <typename T>
typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Child<T>*>::ForwardIterator App::Types::DataTypes::Parent<T>::end() {return children_.end();}
template <typename T>
typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Child<T>*>::ForwardIterator App::Types::DataTypes::Parent<T>::begin() const {return children_.begin();}
template <typename T>
typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Child<T>*>::ForwardIterator App::Types::DataTypes::Parent<T>::end() const {return children_.end();}

template <typename T>
T* Parent<T>::getChildByKey(const ::std::string& key) const noexcept {
    for (const auto& childPtr : children_) {
        if (childPtr->getKey() == key)
            return childPtr->getChild();
    }

    return nullptr;
}

template <typename T>
T* Parent<T>::getChildByKey(const ::std::string& key,
                            ::std::size_t& idx) const noexcept {
    for (const auto& childPtr : children_) {
        if (childPtr->getKey() == key)
            return childPtr->getChild();
        ++idx;
    }

    return nullptr;
}

template <typename T>
inline Parent<T>::Parent(TransportType transportType) : count_(),
    transportType_(transportType) {}

template <typename T>
T* Parent<T>::search(const ::std::string& key) const noexcept {
    return getChildByKey(key);
}

template <typename T>
bool Parent<T>::add(const ::std::string& key, const T* value, int idx) {
    if (getChildByKey(key))
        return false;

    if (idx == -1)
        children_.pushBack(new Child<T>(key, value));
    else
        children_.insert(idx, new Child<T>(key, value));

    ++count_;
    return true;
}

template <typename T>
bool Parent<T>::remove(const ::std::string& key) noexcept {
    ::std::size_t idx {};
    T* childPtr = getChildByKey(key, idx);
    if (!childPtr)
        return false;

    children_.erase(idx);
    --count_;
    return true;
}

template <typename T>
void Parent<T>::clear() noexcept {
    children_.clear();
    count_ = 0;
}

template <typename T>
inline TransportType Parent<T>::getTransportType()
    const noexcept {
    return transportType_;
}

template <typename T>
inline std::size_t Parent<T>::count() const noexcept {
    return count_;
}
} // namespace App::Types::DataTypes
