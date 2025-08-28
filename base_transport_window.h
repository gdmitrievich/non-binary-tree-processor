#ifndef BASE_TRANSPORT_WINDOW_H
#define BASE_TRANSPORT_WINDOW_H

#include <QWidget>
#include <QTableWidget>

#include <initializer_list>
#include "src/data_types/data_structures/tree.h"
#include "filling_in_transport_data_dialog.h"

namespace Ui {
class BaseTransportWindow;
}

class BaseTransportWindow : public QWidget
{
    Q_OBJECT

public:
    BaseTransportWindow(QString windowName, std::initializer_list<QString>&& columnNames, ::App::Types::Project::Enum::TransportType trType, QWidget* parent = nullptr);
    ~BaseTransportWindow();

    // Used for updating table from mainwindow after adding an object from fillingintrDialog.
    void updateWindow(const ::App::Types::DataTypes::Tree& trTree);

private slots:
    void removeLine();
    void addLineBeforeSelected();
    void addLineAfterSelected();

    void sendPassTransportDataSignal(QString key, const App::Types::Project::Transport* tr, ::App::Types::Project::Enum::TransportType trType, int row);

private:
    Ui::BaseTransportWindow *ui;
    QTableWidget* table;
    FillingInTransportDataDialog* fillingInTransportDataDialog;
    ::App::Types::Project::Enum::TransportType windowTrType_;

    void setFillingInTransportDataDialog();

    void fillTableRowByTransportObjData(std::size_t row, const std::initializer_list<QTableWidgetItem*>& rowItems);

    bool checkForAddition(int row, int additionRow);

signals:
    void passTransportData(QString key, const App::Types::Project::Transport* tr, ::App::Types::Project::Enum::TransportType trType, int row);
    void removeObjFromTrTreeByKey(QString key, ::App::Types::Project::Enum::TransportType trType);
};

#endif // BASE_TRANSPORT_WINDOW_H
