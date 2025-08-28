#ifndef UNDERGROUND_TRANSPORT_H
#define UNDERGROUND_TRANSPORT_H

#include "transport.h"

namespace App::Types::Project {
/// @brief Абстрактный класс, хранящий общие данные и поведение о подземном транспорте.
class UndergroundTransport : public Transport {
   protected:
    /// @brief Кол-во колесных пар.
    int numberOfWheelsets_;

   public:
   	/// @brief Конструктор по умолчанию.
    UndergroundTransport();
	/// @brief Конструктор копирования.
    UndergroundTransport(const UndergroundTransport& t);
	/// @brief Конструктор, инициализирующий все поля объекта.
    UndergroundTransport(const std::string& model, int yearOfRelease,
                    int numberOfWheelsets);

	/// @return Кол-во колесных пар.
    int getNumberOfWheelsets() const noexcept;

	/// @brief Чистый виртуальный метод, выполняющий логику езды подземного транспорта.
    virtual void slide() const noexcept = 0;

    /// @brief Дружественная функция для вывода данных о подземном транспорте на консоль.
    /// @param os Поток для вывода данных на консоль.
    /// @param t Константная ссылка на объект подземного транспорта.
    /// @return Ссылку на поток для вывода данных.
    friend std::ostream& operator<<(std::ostream& os, const UndergroundTransport& t);
    /// @brief Дружественная функция для записи данных подземного транспорта с консоли.
    /// @param is Поток для записи данных с консоли.
    /// @param t Ссылка на объект подземного транспорта для записи.
    /// @return Ссылку на поток для записи данных.
    friend std::istream& operator>>(std::istream& is, UndergroundTransport& t);
    /// @brief Дружественная функция для записи данных подземного транспорта из файла.
    /// @param is Файловый поток для записи данных.
    /// @param t Ссылка на объект подземного транспорта для записи.
    /// @return Ссылку на файловый поток для записи.
    friend std::ifstream& operator>>(std::ifstream& is, UndergroundTransport& t);
};
} // namespace App::Types::Project

#include "underground_transport.ipp"

#endif // UNDERGROUND_TRANSPORT_H
