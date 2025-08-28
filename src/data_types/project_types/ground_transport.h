#ifndef GROUND_TRANSPORT_H
#define GROUND_TRANSPORT_H

#include "transport.h"

namespace App::Types::Project {
/// @brief Абстрактный класс, хранящий общие данные и поведение о наземном транспорте.
class GroundTransport : public Transport {
   protected:
    /// @brief Кол-во колес.
    int amountOfWheels_;

   public:
   	/// @brief Конструктор по умолчанию.
    GroundTransport();
	/// @brief Конструктор копирования.
    GroundTransport(const GroundTransport& t);
	/// @brief Конструктор, инициализирующий все поля объекта.
    GroundTransport(const std::string& model, int yearOfRelease,
                    int amountOfWheels);
	/// @return Кол-во колес транспорта.
    int getAmountOfWheels() const noexcept;

	/// @brief Чистый виртуальный метод, выполняющий логику езды наземного транспорта.
    virtual void ride() const noexcept = 0;

    /// @brief Дружественная функция для вывода данных о наземном транспорте на консоль.
    /// @param os Поток для вывода данных на консоль.
    /// @param t Константная ссылка на объект наземного транспорта.
    /// @return Ссылку на поток для вывода данных.
    friend std::ostream& operator<<(std::ostream& os, const GroundTransport& t);
	/// @brief Дружественная функция для записи данных наземного транспорта с консоли.
    /// @param is Поток для записи данных с консоли.
    /// @param t Ссылка на объект наземного транспорта для записи.
    /// @return Ссылку на поток для записи данных.
    friend std::istream& operator>>(std::istream& is, GroundTransport& t);
	/// @brief Дружественная функция для записи данных наземного транспорта из файла.
    /// @param is Файловый поток для записи данных.
    /// @param t Ссылка на объект наземного транспорта для записи.
    /// @return Ссылку на файловый поток для записи.
    friend std::ifstream& operator>>(std::ifstream& is, GroundTransport& t);
};
} // namespace App::Types::Project

#include "ground_transport.ipp"

#endif // GROUND_TRANSPORT_H
