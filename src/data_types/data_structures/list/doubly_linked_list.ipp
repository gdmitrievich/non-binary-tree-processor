#include "doubly_linked_list.h"
#include "node.h"

namespace App::Types::DataTypes::DoublyLinkedListList {
template <typename T>
Node<T>* DoublyLinkedList<T>::getAt(int index) const noexcept {
	if (index < 0)
		return nullptr;

    Node<T>* ptr = front_;
    ::std::size_t n {};

    while (n != index) {
        if (!ptr)
            return ptr;
        ptr = ptr->next;
        n++;
    }

    return ptr;
}

template <typename T>
DoublyLinkedList<T>::ForwardIterator::ForwardIterator(Node<T>* ptr) : ptr_(ptr) {}

template <typename T>
typename DoublyLinkedList<T>::ForwardIterator::reference DoublyLinkedList<T>::ForwardIterator::operator*() const {return ptr_->value;}

template <typename T>
typename DoublyLinkedList<T>::ForwardIterator::pointer DoublyLinkedList<T>::ForwardIterator::operator->() {return &ptr_->value;}

template <typename T>
typename DoublyLinkedList<T>::ForwardIterator& DoublyLinkedList<T>::ForwardIterator::operator++() { ptr_ = ptr_->next; return *this; }
template <typename T>
typename DoublyLinkedList<T>::ForwardIterator DoublyLinkedList<T>::ForwardIterator::operator++(int) { auto tmp = *this; ptr_ = ptr_->next; return tmp; }

template <typename T>
typename DoublyLinkedList<T>::ForwardIterator& DoublyLinkedList<T>::ForwardIterator::operator--() { ptr_ = ptr_->prev; return *this; }
template <typename T>
typename DoublyLinkedList<T>::ForwardIterator DoublyLinkedList<T>::ForwardIterator::operator--(int) { auto tmp = *this; ptr_ = ptr_->prev; return tmp; }

template <typename T>
typename DoublyLinkedList<T>::ForwardIterator DoublyLinkedList<T>::ForwardIterator::next(ForwardIterator fi, std::size_t n) {
    std::size_t i {};
    while (fi.ptr_ != nullptr && i++ < n) {
        ++fi;
    }
    return fi;
}

template <typename T>
typename DoublyLinkedList<T>::ForwardIterator DoublyLinkedList<T>::begin() { return ForwardIterator(front_); }
template <typename T>
typename DoublyLinkedList<T>::ForwardIterator DoublyLinkedList<T>::end() { return ForwardIterator(nullptr); }
template <typename T>
typename DoublyLinkedList<T>::ForwardIterator DoublyLinkedList<T>::begin() const { return ForwardIterator(front_); }
template <typename T>
typename DoublyLinkedList<T>::ForwardIterator DoublyLinkedList<T>::end() const { return ForwardIterator(nullptr); }

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const noexcept {
    return front_ == nullptr && back_ == nullptr;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() noexcept :
    front_(nullptr),
    back_(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
void DoublyLinkedList<T>::pushFront(const T& data) {
    Node<T>* ptr = new Node<T>(data);

    ptr->next = front_;
    if (front_)
        front_->prev = ptr;
    if (!back_)
        back_ = ptr;
    front_ = ptr;
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T& data) {
    Node<T>* ptr = new Node<T>(data);

    ptr->prev = back_;
    if (back_)
        back_->next = ptr;
    if (!front_)
        front_ = ptr;
    back_ = ptr;
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, const T& data) {
    Node<T>* right = getAt(index);
    if (!right && index >= 0) {
        pushBack(data);
        return;
    }

    Node<T>* left = right ? right->prev : nullptr;
    if (!left) {
        pushFront(data);
        return;
    }

    Node<T>* ptr = new Node<T>(data);

    ptr->prev = left;
    ptr->next = right;
    left->next = ptr;
    right->prev = ptr;
}

template <typename T>
void DoublyLinkedList<T>::popFront() noexcept {
    if (isEmpty())
        return;

    Node<T>* ptr = front_->next;
    if (ptr)
        ptr->prev = nullptr;
    else
        back_ = nullptr;

    delete front_;
    front_ = ptr;
}

template <typename T>
void DoublyLinkedList<T>::popBack() noexcept {
    if (isEmpty())
        return;

    Node<T>* ptr = back_->prev;
    if (ptr)
        ptr->next = nullptr;
    else
        front_ = nullptr;

    delete back_;
    back_ = ptr;
}

template <typename T>
void DoublyLinkedList<T>::erase(::std::size_t index) noexcept {
    Node<T>* ptr = getAt(index);
    if (!ptr)
        return;

    if (!ptr->prev) {
        popFront();
        return;
    }

    if (!ptr->next) {
        popBack();
        return;
    }

    Node<T>* left = ptr->prev;
    Node<T>* right = ptr->next;
    left->next = right;
    right->prev = left;

    delete ptr;
}

template <typename T>
void DoublyLinkedList<T>::clear() noexcept {
    while (!isEmpty()) {
        popBack();
    }
}

template <typename T>
T* DoublyLinkedList<T>::search(int index) const noexcept {
	auto tmp = getAt(index);
	return tmp ? tmp->value : nullptr;
}

template <typename T>
T* DoublyLinkedList<T>::operator[](int index) const noexcept {
    return search(index);
}
} // namespace App::Types::DataTypes::DoublyLinkedListList
