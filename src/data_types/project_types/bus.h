#ifndef BUS_H
#define BUS_H

#include "ground_transport.h"

namespace App::Types::Project {
/// @brief Класс автобуса.
class Bus : public GroundTransport {
   protected:
    /// @brief Кол-во пассажиров.
    int amountOfPassengers_;

   public:
	/// @brief Конструктор по умолчанию.
    Bus();
	/// @brief Конструктор копирования.
    Bus(const Bus& t);
	/// @brief Конструктор, инициализирующий все поля объекта.
    Bus(const std::string& model, int yearOfRelease, int amountOfWheels,
               int amountOfPassengers);

    /// @return Кол-во пассажиров.
    int getAmountOfPassengers() const noexcept;

    /// @brief Переопределенный виртуальный метод, реализующий логику старта автобуса.
    virtual void start() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику остановки автобуса.
    virtual void stop() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику езды автобуса.
    virtual void ride() const noexcept override;

	/// @brief Метод, определенный для автобусов.
    void bus() const noexcept;

    /// @brief Дружественная функция для вывода данных об автобусе на консоль.
    /// @param os Поток для вывода данных на консоль.
    /// @param t Константная ссылка на объект автобуса.
    /// @return Ссылку на поток для вывода данных.
    friend std::ostream& operator<<(std::ostream& os, const Bus& t);
    /// @brief Дружественная функция для записи данных об автобусе с консоли.
    /// @param is Поток для записи данных с консоли.
    /// @param t Ссылка на объект автобуса для записи.
    /// @return Ссылку на поток для записи данных.
    friend std::istream& operator>>(std::istream& is, Bus& t);
    /// @brief Дружественная функция для записи данных об автобусе из файла.
    /// @param is Файловый поток для записи данных.
    /// @param t Ссылка на объект автобуса для записи.
    /// @return Ссылку на файловый поток для записи.
    friend std::ifstream& operator>>(std::ifstream& is, Bus& t);
};
} // namespace App::Types::Project

#include "bus.ipp"

#endif // BUS_H
