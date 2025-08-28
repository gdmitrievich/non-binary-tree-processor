#ifndef AIR_TRANSPORT_H
#define AIR_TRANSPORT_H

#include "transport.h"

namespace App::Types::Project {
/// @brief Абстрактный класс, хранящий общие данные и поведение о воздушном транспорте.
class AirTransport : public Transport {
   protected:
    /// @brief Максимальная высота полета.
    int maxHeight_;
    /// @brief Кол-во пропеллеров.
    int amountOfPropellers_;

   public:
	/// @brief Конструктор по умолчанию.
    AirTransport();
	/// @brief Конструктор копирования.
    AirTransport(const AirTransport& t);
	/// @brief Конструктор, инициализирующий все поля объекта.
    AirTransport(const std::string& model, int yearOfRelease, int maxHeight,
                 int amountOfPropellers);

    /// @return Максимальную высоту полета.
    int getMaxHeight() const noexcept;
    /// @return Кол-во пропеллеров.
    int getAmountOfPropellers() const noexcept;

    /// @brief Чистый виртуальный метод, выполняющий логику полета воздушного транспорта.
    virtual void fly() const noexcept = 0;

    /// @brief Дружественная функция для вывода данных о воздушном транспорте на консоль.
    /// @param os Поток для вывода данных на консоль.
    /// @param t Константная ссылка на объект воздушного транспорта.
    /// @return Ссылку на поток для вывода данных.
    friend std::ostream& operator<<(std::ostream& os, const AirTransport& t);
	/// @brief Дружественная функция для записи данных воздушного транспорта с консоли.
    /// @param is Поток для записи данных с консоли.
    /// @param t Ссылка на объект воздушного транспорта для записи.
    /// @return Ссылку на поток для записи данных.
    friend std::istream& operator>>(std::istream& is, AirTransport& t);
	/// @brief Дружественная функция для записи данных воздушного транспорта из файла.
    /// @param is Файловый поток для записи данных.
    /// @param t Ссылка на объект воздушного транспорта для записи.
    /// @return Ссылку на файловый поток для записи.
    friend std::ifstream& operator>>(std::ifstream& is, AirTransport& t);
};
} // namespace App::Types::Project

#include "air_transport.ipp"

#endif // AIR_TRANSPORT_H
