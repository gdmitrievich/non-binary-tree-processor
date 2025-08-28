#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>
#include <iostream>
#include <fstream>

namespace App::Types::Project {
/// @brief Абстрактный класс, хранящий общие данные и поведение о транспорте.
class Transport {
   protected:
    /// @brief Модель.
    ::std::string model_;
    /// @brief Год выпуска.
    int yearOfRelease_;

    /// @brief Получает результат пользовательского ввода и записывает его в field.
    /// @param message Сообщение, выводимое пользователю.
    /// @param field Поле, куда записывается результат пользовательского ввода.
    static void setUserAnswer(const char* message, ::std::string& field);
	/// @brief Получает результат пользовательского ввода и записывает его в field.
    /// @param message Сообщение, выводимое пользователю.
    /// @param field Поле, куда записывается результат пользовательского ввода.
    static bool setUserAnswer(const char* message, int& field);
    /// @brief Считывает данные из строки файла и записывает в поле field.
    /// @tparam T Тип поля.
    /// @param is Файловый поток для чтения.
    /// @param field Поле, куда записываются данные из файла.
    template <typename T>
    static void setDataFromLine(::std::ifstream& is, T& field);

   public:
    /// @brief Конструктор по умолчанию.
    Transport();
    /// @brief Конструктор копирования.
    Transport(const Transport& t);
    /// @brief Конструктор, инициализирующий все поля объекта.
    Transport(const std::string& model, int yearOfRelease);
    /// @brief Виртуальный деструктор.
    virtual ~Transport() noexcept;

	/// @return Модель транспорта.
    ::std::string getModel() const noexcept;
	/// @return Год релиза транспорта.
    int getYearOfRelease() const noexcept;

    /// @brief Чистый виртуальный метод, выполняющий логику старта транспорта.
    virtual void start() const noexcept = 0;
    /// @brief Чистый виртуальный метод, выполняющий логику остановки транспорта.
    virtual void stop() const noexcept = 0;

    /// @brief Дружественная функция для вывода данных о транспорте на консоль.
    /// @param os Поток для вывода данных на консоль.
    /// @param t Константная ссылка на объект транспорта.
    /// @return Ссылку на поток для вывода данных.
    friend std::ostream& operator<<(std::ostream& os, const Transport& t);
    /// @brief Дружественная функция для записи данных транспорта с консоли.
    /// @param is Поток для записи данных с консоли.
    /// @param t Ссылка на объект транспорта для записи.
    /// @return Ссылку на поток для записи данных.
    friend std::istream& operator>>(std::istream& is, Transport& t);
    /// @brief Дружественная функция для записи данных транспорта из файла.
    /// @param is Файловый поток для записи данных.
    /// @param t Ссылка на объект транспорта для записи.
    /// @return Ссылку на файловый поток для записи.
    friend std::ifstream& operator>>(std::ifstream& is, Transport& t);
};
} // namespace App::Types::Project

#include "transport.ipp"

#endif // TRANSPORT_H
