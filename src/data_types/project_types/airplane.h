#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "air_transport.h"

namespace App::Types::Project {
/// @brief Класс самолета.
class Airplane : public AirTransport {
   protected:
    /// @brief Размах крыльев.
    int wingspan_;

   public:
   	/// @brief Конструктор по умолчанию.
    Airplane();
	/// @brief Конструктор копирования.
    Airplane(const Airplane& t);
	/// @brief Конструктор, инициализирующий все поля объекта.
    Airplane(const std::string& model, int yearOfRelease, int maxHeight,
             int amountOfPropellers, int wingspan);

    /// @return Размах крыльев.
    int getWingspan() const noexcept;

    /// @brief Переопределенный виртуальный метод, реализующий логику старта самолета.
    virtual void start() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику остановки самолета.
    virtual void stop() const noexcept override;
	/// @brief Переопределенный виртуальный метод, реализующий логику полета самолета.
    virtual void fly() const noexcept override;

    /// @brief Метод, определенный для самолетов.
    void airplane() const noexcept;

    /// @brief Дружественная функция для вывода данных о самолете на консоль.
    /// @param os Поток для вывода данных на консоль.
    /// @param t Константная ссылка на объект самолета.
    /// @return Ссылку на поток для вывода данных.
    friend std::ostream& operator<<(std::ostream& os, const Airplane& t);
    /// @brief Дружественная функция для записи данных о самолете с консоли.
    /// @param is Поток для записи данных с консоли.
    /// @param t Ссылка на объект самолета для записи.
    /// @return Ссылку на поток для записи данных.
    friend std::istream& operator>>(std::istream& is, Airplane& t);
    /// @brief Дружественная функция для записи данных о самолете из файла.
    /// @param is Файловый поток для записи данных.
    /// @param t Ссылка на объект самолета для записи.
    /// @return Ссылку на файловый поток для записи.
    friend std::ifstream& operator>>(std::ifstream& is, Airplane& t);
};
} // namespace App::Types::Project

#include "airplane.ipp"

#endif // AIRPLANE_H
