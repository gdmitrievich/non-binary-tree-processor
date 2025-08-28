#ifndef CHILD_H
#define CHILD_H

#include <string>

namespace App::Types::DataTypes {
/// @brief Представляет отдельный элемент контейнера Parent<T>.
template <typename T>
class Child {
   private:
	/// @brief Ключ, идентифицирующий текущий объект.
	::std::string key_;
	/// @brief Поле, хранящее указатель на объект.
    T* child_;

   public:
    /// @brief Конструктор копирования.
    Child(const Child<T>& child);
    /// @brief Конструктор.
    Child(const ::std::string& key, const T* child);

	/// @brief Возвращает константный указатель на хранимый объект.
	/// @return Константный указатель на хранимый объект.
    T* getChild() const noexcept;

	/// @brief Возвращает ключ.
	/// @return Возвращает строку, представляющую ключ.
    ::std::string getKey() const noexcept;
};
} // namespace App::Types::DataTypes

#include "child.ipp"

#endif // CHILD_H