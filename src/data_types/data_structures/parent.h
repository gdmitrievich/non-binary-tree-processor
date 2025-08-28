#ifndef PARENT_H
#define PARENT_H

#include <string>
#include <cstddef>

#include "list/doubly_linked_list.h"
#include "../project_types/transport_type.h"
#include "child.h"

namespace App::Types::DataTypes {
/// @brief Представляет собой отдельный элемент класса-контейнера Tree.
template <typename T>
class Parent {
   private:
   	/// @brief Перечислитель, устанавливающий принадлежность объекта класса к определенному типу транспорта.
    ::App::Types::Project::Enum::TransportType transportType_;
    /// @brief Список из дочерних узлов.
    DoublyLinkedListList::DoublyLinkedList<Child<T>*> children_;

    /// @brief Возвращает указатель на элемент типа T в случае его нахождения по ключу key.
    /// @param key Ключ, по которому выполняется поиск элемента.
    /// @return Указатель на элемент типа T в случае успешного поиска, иначе - nullptr.
    T* getChildByKey(const ::std::string& key) const noexcept;
	/// @brief Возвращает указатель на элемент типа T в случае его нахождения по ключу key.
	/// @param key Ключ, по которому выполняется поиск элемента.
	/// @param idx Индекс найденного элемента в списке, начиная с первого.
	/// @return Указатель на элемент типа T в случае успешного поиска, иначе - nullptr. А также индекс этого элемента в списке, начиная с первого, по ссылке.
	T* getChildByKey(const ::std::string& key,
                     ::std::size_t& idx) const noexcept;

    /// @brief Хранит кол-во узлов в списке.
    std::size_t count_;
   public:
    /// @brief Конструктор, устанавливающий, к какому типу транспорта принадлежит созданный объект.
	/// @param transportType Тип транспорта.
    Parent(::App::Types::Project::Enum::TransportType transportType);

    /// @return Итератор на первый объект списка.
    typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Child<T>*>::ForwardIterator begin();
    /// @return Итератор на непроинициализированную область памяти.
    typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Child<T>*>::ForwardIterator end();
    /// @return Константный итератор на первый объект списка.
    typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Child<T>*>::ForwardIterator begin() const;
    /// @return Константный итератор на непроинициализированную область памяти.
    typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Child<T>*>::ForwardIterator end() const;

    /// @brief Ищет элемент типа T по ключу key.
    /// @param key Ключ, по которому выполняется поиск элемента в списке.
    /// @return Возвращает указатель на найденный элемента в случае успешного поиска, иначе - nullptr.
    T* search(const ::std::string& key) const noexcept;

    /// @brief Добавляет элемент в список.
    /// @param key Ключ, по которому выполняется поиск элемента в списке.
    /// @param value Указатель на объект, помещаемый в список.
    /// @param idx Параметр по умолчанию = -1. Индекс, по которому помещается элемент в список. Если не указан - вставляет в конец списка.
    bool add(const ::std::string& key, const T* value, int idx = -1);

    /// @brief Удаляет элемент из списка по ключу.
    /// @param key Ключ, по которому выполняется поиск удаляемого элемента.
	/// @return true - если элемент с таким ключем существует, false - в противном случае.
    bool remove(const ::std::string& key) noexcept;

    /// @brief Удаляет все элемента списка.
    void clear() noexcept;

	/// @return Тип транспорта, к которому относится текущий объект класса.
    ::App::Types::Project::Enum::TransportType getTransportType()
        const noexcept;

    /// @return Возвращает кол-во элементов в списке.
    std::size_t count() const noexcept;
};
} // namespace App::Types::DataTypes


#include "parent.ipp"

#endif // PARENT_H
