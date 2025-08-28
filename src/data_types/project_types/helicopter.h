#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "air_transport.h"

namespace App::Types::Project {
/// @brief Класс вертолета.
class Helicopter : public AirTransport {
   protected:
    /// @brief Длина носовой части.
    int noseLength_;

   public:
   	/// @brief Конструктор по умолчанию.
    Helicopter();
	/// @brief Конструктор копирования.
    Helicopter(const Helicopter& t);
	/// @brief Конструктор, инициализирующий все поля объекта.
    Helicopter(const std::string& model, int yearOfRelease, int maxHeight,
               int amountOfPropellers, int noseLength);

	/// @return Длину носовой части.
    int getNoseLength() const noexcept;

	/// @brief Переопределенный виртуальный метод, реализующий логику старта вертолета.
    virtual void start() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику остановки вертолета.
    virtual void stop() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику полета вертолета.
    virtual void fly() const noexcept override;

	/// @brief Метод, определенный для вертолетов.
    void helicopter() const noexcept;

        /// @brief Дружественная функция для вывода данных о вертолете на консоль.
    /// @param os Поток для вывода данных на консоль.
    /// @param t Константная ссылка на объект вертолета.
    /// @return Ссылку на поток для вывода данных.
    friend std::ostream& operator<<(std::ostream& os, const Helicopter& t);
    /// @brief Дружественная функция для записи данных о вертолете с консоли.
    /// @param is Поток для записи данных с консоли.
    /// @param t Ссылка на объект вертолета для записи.
    /// @return Ссылку на поток для записи данных.
    friend std::istream& operator>>(std::istream& is, Helicopter& t);
    /// @brief Дружественная функция для записи данных о вертолете из файла.
    /// @param is Файловый поток для записи данных.
    /// @param t Ссылка на объект вертолета для записи.
    /// @return Ссылку на файловый поток для записи.
    friend std::ifstream& operator>>(std::ifstream& is, Helicopter& t);
};
} // namespace App::Types::Project

#include "helicopter.ipp"

#endif // HELICOPTER_H
