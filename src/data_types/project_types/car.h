#ifndef CAR_H
#define CAR_H

#include "ground_transport.h"

namespace App::Types::Project {
/// @brief Класс машины.
class Car : public GroundTransport {
   protected:
    /// @brief Вместимость багажа.
    int trunkCapacity_;

   public:
	/// @brief Конструктор по умолчанию.
    Car();
	/// @brief Конструктор копирования.
    Car(const Car& t);
	/// @brief Конструктор, инициализирующий все поля объекта.
    Car(const std::string& model, int yearOfRelease, int amountOfWheels,
               int trunkСapacity);

    /// @return Вместимость багажа.
    int getTrunkCapacity() const noexcept;

    /// @brief Переопределенный виртуальный метод, реализующий логику старта машины.
    virtual void start() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику остановки машины.
    virtual void stop() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику езды машины.
    virtual void ride() const noexcept override;

	/// @brief Метод, определенный для машин.
    void car() const noexcept;

    /// @brief Дружественная функция для вывода данных о машине на консоль.
    /// @param os Поток для вывода данных на консоль.
    /// @param t Константная ссылка на объект машины.
    /// @return Ссылку на поток для вывода данных.
    friend std::ostream& operator<<(std::ostream& os, const Car& t);
    /// @brief Дружественная функция для записи данных о машине с консоли.
    /// @param is Поток для записи данных с консоли.
    /// @param t Ссылка на объект машины для записи.
    /// @return Ссылку на поток для записи данных.
    friend std::istream& operator>>(std::istream& is, Car& t);
    /// @brief Дружественная функция для записи данных о машине из файла.
    /// @param is Файловый поток для записи данных.
    /// @param t Ссылка на объект машины для записи.
    /// @return Ссылку на файловый поток для записи.
    friend std::ifstream& operator>>(std::ifstream& is, Car& t);
};
} // namespace App::Types::Project

#include "car.ipp"

#endif // CAR_H
