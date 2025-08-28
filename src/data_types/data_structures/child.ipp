#include "child.h"

#include <string>

namespace App::Types::DataTypes {
template <typename T>
inline Child<T>::Child(const Child<T>& child) :
    key_(child.key_),
    child_(child.child_) {}

template <typename T>
inline Child<T>::Child(const ::std::string& key, const T* child) :
    key_(key),
    child_(const_cast<T*>(child)) {}

template <typename T>
inline T* Child<T>::getChild() const noexcept {
    return child_;
}

template <typename T>
inline ::std::string Child<T>::getKey() const noexcept {
    return key_;
}
} // namespace App::Types::DataTypes