#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include "node.h"
#include <iterator>

namespace App::Types::DataTypes::DoublyLinkedListList {
// Предварительное объявление класса DoublyLinkedList.
template <typename T>
class DoublyLinkedList;

// Предварительные объявления для дружественных операторов, сравнивающих два итератора.
template <typename T>
bool operator== (const typename DoublyLinkedList<T>::ForwardIterator& a, const typename DoublyLinkedList<T>::ForwardIterator& b);
template <typename T>
bool operator!= (const typename DoublyLinkedList<T>::ForwardIterator& a, const typename DoublyLinkedList<T>::ForwardIterator& b);

/// @brief Класс-контейнер, основанный на двусвязном списке.
/// @tparam T Тип узлов, хранимых в данном контейнере, а также операций, выполняемых над ними.
template <typename T>
class DoublyLinkedList {
   private:
    Node<T>* front_; // Указатель на первый узел.
    Node<T>* back_; // Указатель на последний узел.

	/// @brief Возвращает указатель на узел по определенному индексу.
	/// @param index Индекс необходимого узла. Диапазон допустимых значений [0, n), n - кол-во элементов в списке.
	/// @return Указатель на первый узел, если индекс отрицательный. Указатель на узел, если index не больше (n - 1), где n - кол-во узлов в списке, в противном случае - nullptr.
	Node<T>* getAt(int index) const noexcept;

   public:
    /// @brief Двусторонний итератор для прохода по элементам списка.
    struct ForwardIterator
    {
        using ForwardIterator_category = std::forward_iterator_tag; // Категория итератора.
        using difference_type = std::ptrdiff_t; // Целочисленный тип со знаком, использующийся для определения расстояния между шагами итератора.
        using value_type = T; // Тип, по которому выполняется итератор.
        using pointer = value_type*; // Тип указателя.
        using reference = value_type&; // Ссылочный тип.

        /// @brief Конструктор, принимающий указатель на узел контейнера.
        /// @param ptr Указатель на узел контейнера.
        explicit ForwardIterator(Node<value_type>* ptr);

        /// @brief Оператор разыменования.
        /// @return Ссылку на объект, полученный из узла, на который указывает итератор.
        reference operator*() const;
        /// @brief Оператор членства по указателю.
        /// @return Указатель на объект, полученный из узла, на который указывает итератор.
        pointer operator->();

        /// @brief Оператор префиксного инкремента. Перемещает указатель итератора на следующий узел.
        /// @return Ссылку на итератор.
        ForwardIterator& operator++();
        /// @brief Оператор постфиксного инкремента. Создает копию текущего итератора и перемещает указатель оригинального итератора на следующий узел.
        /// @param Необходим компилятору для различия между префиксной и постфиксной версиями операторов.
        /// @return Копию временного итератора.
        ForwardIterator operator++(int);

        /// @brief Оператор префиксного декремента. Перемещает указатель итератора на предыдующий узел.
        /// @return Ссылку на итератор.
        ForwardIterator& operator--();
		/// @brief Оператор постфиксного декремента. Создает копию текущего итератора и перемещает указатель оригинального итератора на предыдующий узел.
        /// @param Необходим компилятору для различия между префиксной и постфиксной версиями операторов.
        /// @return Копию временного итератора.
        ForwardIterator operator--(int);

        /// @brief Возвращает копию n-го итератора.
        /// @param fi Итератор, представляющий текущую позицию.
        /// @param n Параметр по умолчанию = 1. Показывает, на сколько шагов необходимо продвинуться от текущей позиции.
        /// @return Копию итератора, указывающего на необходимую позицию.
        ForwardIterator next(ForwardIterator fi, std::size_t n = 1);

        /// @brief Оператор равенства. Проверяет равны ли итераторы.
        /// @param a Первый итератор.
        /// @param b Второй итератор.
        /// @return true - если равны, false - в противном случае.
        friend bool operator==(const ForwardIterator& a, const ForwardIterator& b) { return a.ptr_ == b.ptr_; };
		/// @brief Оператор неравенства. Проверяет не равны ли итераторы.
        /// @param a Первый итератор.
        /// @param b Второй итератор.
        /// @return true - если не равны, false - в противном случае.
        friend bool operator!=(const ForwardIterator& a, const ForwardIterator& b) { return a.ptr_ != b.ptr_; };

    private:
        Node<value_type>* ptr_; // Указатель на текущий узел списка.
    };

    /// @return Итератор на первый объект списка.
    ForwardIterator begin();
	/// @return Итератор на непроинициализированную область памяти.
    ForwardIterator end();
	/// @return Константный итератор на первый объект списка.
    ForwardIterator begin() const;
	/// @return Константный итератор на непроинициализированную область памяти.
    ForwardIterator end() const;

	/// @brief Проверяет, является ли список пустым или нет.
	/// @return true - если да, false - в противном случае.
	bool isEmpty() const noexcept;

    /// @brief Конструктор.
    DoublyLinkedList() noexcept;
    /// @brief Деструктор.
    ~DoublyLinkedList();

    /// @brief Добавляет объект data в начало списка.
    /// @param data Объект, добавляемый в список.
    void pushFront(const T& data);
	/// @brief Добавляет объект data в конец списка.
    /// @param data Объект, добавляемый в список.
    void pushBack(const T& data);
	/// @brief Вставляет объект data по определенному индексу. Причем возможны следующие ситуации:
	/// - Если индекс больше или равен кол-ву элементов в списке, вставляет в конец;
	/// - Если индекс отрицательный, вставляет в начало;
    /// @param index Индекс, по которому необходимо добавить элемент в список. Диапазон допустимых значений [0, n), n - кол-во элементов в списке.
    /// @param data Объект, добавляемый в список.
    void insert(int index, const T& data);

    /// @brief Удаляет первый элемент.
    void popFront() noexcept;
    /// @brief Удаляет последний элемент.
    void popBack() noexcept;
    /// @brief Удаляет элемент по определенному индексу. Причем, если индекс больше или равен кол-во существующих элементов, список не изменяется.
    /// @param index Индекс, по которому необходимо удалить элемент из списка. Диапазон допустимых значений [0, n), n - кол-во элементов в списке.
    void erase(::std::size_t index) noexcept;

    /// @brief Удаляет все элементы списка.
    void clear() noexcept;

    /// @brief Выполняет поиск элемента по определенному индексу.
    /// @param index Индекс, по которому необходимо найте элемент в списке. Диапазон допустимых значений [0, n), n - кол-во элементов в списке.
    /// @return Указатель на найденный элемент, nullptr - в противном случае.
    T* search(int index) const noexcept;
	/// @brief Оператор индексации. Выполняет поиск элемента по определенному индексу.
    /// @param index Индекс, по которому необходимо найте элемент в списке. Диапазон допустимых значений [0, n), n - кол-во элементов в списке.
    /// @return Указатель на найденный элемент, nullptr - в противном случае.
    T* operator[](int index) const noexcept;
};
} // namespace App::Types::DataTypes::DoublyLinkedListList

#include "doubly_linked_list.ipp"

#endif // DOUBLY_LINKED_LIST_H
