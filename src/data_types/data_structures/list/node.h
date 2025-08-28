#ifndef NODE_H
#define NODE_H

namespace App::Types::DataTypes::DoublyLinkedListList {
/// @brief Посредник, являющийся узлом двусвязного списка.
/// @tparam T Тип объекта, хранимый в данном узле.
template <typename T>
struct Node {
    T value; // Хранимый объект.
    Node<T> *next, *prev; // Указатели на следующий и предыдущий узлы.

    Node(const T& value); // Конструктор
};
} // namespace App::Types::DataTypes::List

#include "node.ipp"

#endif