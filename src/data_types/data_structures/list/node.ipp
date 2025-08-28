#include "node.h"

namespace App::Types::DataTypes::DoublyLinkedListList {
template <typename T>
Node<T>::Node(const T& value) : value(value), next(nullptr), prev(nullptr) {}
}