#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QTableWidget>

#include "src/data_types/data_structures/tree.h"
#include <QValidator>
#include <QComboBox>

#include "transport_type_dialog.h"
#include "base_transport_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadData();
    void saveData();
    void removeLine();
    void addLineBeforeSelected();
    void addLineAfterSelected();

    void openAdditionalWindow(int row, int col);

    void obtainTransportObjData(QString key, const App::Types::Project::Transport* tr, ::App::Types::Project::Enum::TransportType trType, int row);
    void removeTrObjFromTreeByKey(QString key, ::App::Types::Project::Enum::TransportType trType);

private:
    Ui::MainWindow *ui;
    QTableWidget* table;
    ::App::Types::DataTypes::Tree trTree;
    TransportTypeDialog* trTypeDialog;
    std::unordered_map<::App::Types::Project::Enum::TransportType, BaseTransportWindow*> trWindows;

    const int NUMBER_OF_EXISTING_TYPES = 5;

    bool checkForAddition(int row, int additionRow);

    void openSpecificTransportWindow(::App::Types::Project::Enum::TransportType trType);

    bool isTableFull() const {return table->rowCount() == NUMBER_OF_EXISTING_TYPES;}

    void updateTable();
    void updateTrObjWindows();

    void closeEvent(QCloseEvent *event);

};
#endif // MAINWINDOW_H
