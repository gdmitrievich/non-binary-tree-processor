#ifndef METRO_H
#define METRO_H

#include "underground_transport.h"

namespace App::Types::Project {
/// @brief Класс поезда.
class Metro : public UndergroundTransport {
   protected:
    /// @brief Кол-во вагонов.
    int numberOfWagons_;

   public:
	/// @brief Конструктор по умолчанию.
    Metro();
	/// @brief Конструктор копирования.
    Metro(const Metro& t);
	/// @brief Конструктор, инициализирующий все поля объекта.
    Metro(const std::string& model, int yearOfRelease, int amountOfWheelsets,
          int numberOfWagons);

    /// @return Кол-во вагонов.
    int getNumberOfWagons() const noexcept;

	/// @brief Переопределенный виртуальный метод, реализующий логику старта поезда.
    virtual void start() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику остановки поезда.
    virtual void stop() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику езды поезда.
    virtual void slide() const noexcept override;

	/// @brief Метод, определенный для поездов.
    void metro() const noexcept;

    /// @brief Дружественная функция для вывода данных о поезде на консоль.
    /// @param os Поток для вывода данных на консоль.
    /// @param t Константная ссылка на объект поезда.
    /// @return Ссылку на поток для вывода данных.
    friend std::ostream& operator<<(std::ostream& os, const Metro& t);
    /// @brief Дружественная функция для записи данных о поезде с консоли.
    /// @param is Поток для записи данных с консоли.
    /// @param t Ссылка на объект поезда для записи.
    /// @return Ссылку на поток для записи данных.
    friend std::istream& operator>>(std::istream& is, Metro& t);
    /// @brief Дружественная функция для записи данных о поезде из файла.
    /// @param is Файловый поток для записи данных.
    /// @param t Ссылка на объект поезда для записи.
    /// @return Ссылку на файловый поток для записи.
    friend std::ifstream& operator>>(std::ifstream& is, Metro& t);
};
} // namespace App::Types::Project

#include "metro.ipp"

#endif // METRO_H
