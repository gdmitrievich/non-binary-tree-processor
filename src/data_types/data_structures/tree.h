#ifndef TREE_H
#define TREE_H

#include <string>

#include "list/doubly_linked_list.h"
#include "parent.h"
#include "../project_types/transport.h"

namespace App::Types::DataTypes {
/// @brief Дерево объектов, производных от типа Transport.
class Tree {
   private:
    /// @brief Список из родительских вершин.
    DoublyLinkedListList::DoublyLinkedList<
        Parent<::App::Types::Project::Transport>*>
        parents_;

    /// @brief Возвращает указатель на родительский узел по типу перечислителя transportType.
    /// @param transportType Перечислитель, на основе которого выполняется поиск необходимого родителя.
    /// @return Указатель на родителя в случае успешного поиска, nullptr - в противном случае.
    Parent<::App::Types::Project::Transport>* getParentPtrByItsType(
        ::App::Types::Project::Enum::TransportType transportType)
        const noexcept;

    /// @brief Возвращает указатель на родительский узел по типу перечислителя transportType.
    /// @param transportType Перечислитель, на основе которого выполняется поиск необходимого родителя.
    /// @param idx Индекс найденного элемента в списке, начиная с первого.
    /// @return Указатель на родителя в случае успешного поиска, nullptr - в противном случае. А также индекс этого элемента в списке, начиная с первого, по ссылке.
    Parent<::App::Types::Project::Transport>* getParentPtrByItsType(
        ::App::Types::Project::Enum::TransportType transportType,
        ::std::size_t& idx) const noexcept;

	/// @brief Хранит кол-во узлов в списке.
    std::size_t count_;

    /// @brief Сохраняет данные транспортов типа T через файловый поток записи с указанием идентификатора транспорта.
    /// @tparam T Общий тип транспортов для записи. Производный от класса Transport.
    /// @param os Файловый поток записи данных.
    /// @param parent Указатель на объект типа Parent, хранящий список из транспортов типа T.
    /// @param trTypeName Строковое представление типа транспорта T.
    template <typename T>
    void saveTransportData(std::ofstream& os, const Parent<::App::Types::Project::Transport>* parent, std::string&& trTypeName) const;
    /// @brief Загружает данные транспортов типа T, производных от Transport, через файловый поток чтения с указанием перечислителя, представляющего данный тип транспорта.
    /// @tparam T Общий тип транспортов для чтения. Производный от класса Transport.
    /// @param is Файловый поток чтения данных.
    /// @param trType Перечислитель, устанавливающий к какому типу транспорта относятся транспорта, читаемые из файла.
    /// @param t Дерево, в которое добавляются элементы транспорта, считанные с файла.
    template <typename T>
    void loadTransportData(std::ifstream& is, ::App::Types::Project::Enum::TransportType trType, Tree& t) const;

   public:
    /// @brief Конструктор.
    Tree();

	/// @return Итератор на первый объект списка.
    typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Parent<::App::Types::Project::Transport>*>::ForwardIterator begin();
	/// @return Итератор на непроинициализированную область памяти.
    typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Parent<::App::Types::Project::Transport>*>::ForwardIterator end();
	/// @return Константный итератор на первый объект списка.
    typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Parent<::App::Types::Project::Transport>*>::ForwardIterator begin() const;
	/// @return Константный итератор на непроинициализированную область памяти.
    typename App::Types::DataTypes::DoublyLinkedListList::DoublyLinkedList<Parent<::App::Types::Project::Transport>*>::ForwardIterator end() const;

    /// @brief Ищет элемент в дереве, сначала найдя необходимую родительскую вершину по transportType, а после и сам элемент в списке найденного родителя.
    /// @param key Ключ, по которому выполняется поиск элемента.
    /// @param transportType Перечислитель, по которому выполняется поиск родительской вершины.
    /// @return Возвращает указатель на найденный элемент в случае успешного поиска, иначе - nullptr.
    ::App::Types::Project::Transport* search(
        const ::std::string& key,
        ::App::Types::Project::Enum::TransportType transportType) const noexcept;

    /// @brief Добавляет элемент в дерево, сначала найдя необходимую родительскую вершину по transportType, а затем добавляя ее в список найденного родителя.
    /// @param key Ключ, по которому выполняется поиск элемента в дочерних узлах родительских вершин.
    /// @param value Указатель на объект, добавляемый в список дочерних узлов найденной родительской вершины.
    /// @param transportType Перечислитель, по которому выполняется поиск родительской вершины.
    bool add(const ::std::string& key,
             const ::App::Types::Project::Transport* value,
             ::App::Types::Project::Enum::TransportType transportType, int idx = -1);

    /// @brief Добавляет родителя в дерево по типу перечислителя, к которому он относится.
    /// @param transportType Перечислитель, по которому выполняется добавление родительской вершины.
    /// @param idx Индекс, по которому выполняется вставка родительской вершины в список.
    /// @return true - в случае, если данная вершина не существовало до этого момента в списке, иначе false.
    bool addParent(::App::Types::Project::Enum::TransportType transportType, int idx = -1) noexcept;

    /// @brief Удаляет элемент из дерева.
    /// @param key Ключ, по которому выполняется поиск удаляемого элемента в списке родительской вершины.
    /// @param transportType Перечислитель, по которому выполняется поиск родительской вершины.
    bool remove(const ::std::string& key,
                ::App::Types::Project::Enum::TransportType transportType) noexcept;
    /// @brief Удаляет родителя и все его элементы из дерева.
    /// @param transportType Перечислитель, по которому выполняется поиск удаляемой родительской вершины.
    /// @return true - если вершина существовала и была удалена, false - в противном случае.
    bool removeParent(::App::Types::Project::Enum::TransportType transportType) noexcept;
    /// @brief Удаляет все элементы дерева.
    void clear() noexcept;

    /// @brief Возвращает кол-во элементов в списке.
    std::size_t count() const;

    /// @brief Получает данные из дерева и записывает их в файл.
    /// @param os Файловый поток для записи.
    /// @param t Дерево с данными для записи.
    /// @return Возвращает открытый файловый поток для записи.
    friend std::ofstream& operator<<(std::ofstream& os, const Tree& t);
	/// @brief Считывает данные с файлового потока, преобразовывает их в объекты типа транспорта и добавляет в дерево.
    /// @param is Файловый поток для чтения.
    /// @param t Дерево, в которое записываются объекты типа транспорта.
    /// @return Возвращает открытый файловый поток для чтения.
	friend std::ifstream& operator>>(std::ifstream& is, Tree& t);
};
} // namespace App::Types::DataTypes

#include "tree.ipp"

#endif // TREE_H
