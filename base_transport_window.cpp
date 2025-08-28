#include "base_transport_window.h"
#include "ui_base_transport_window.h"

#include <QtWidgets>
#include <QValidator>

BaseTransportWindow::BaseTransportWindow(QString windowName, std::initializer_list<QString>&& columnNames, ::App::Types::Project::Enum::TransportType trType, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::BaseTransportWindow),
    table(),
    fillingInTransportDataDialog(),
    windowTrType_(trType)
{
    ui->setupUi(this);
    setWindowTitle(windowName);
    setFixedWidth(900);

    setFillingInTransportDataDialog();

    table = new QTableWidget(0, columnNames.size(), this);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList headers = columnNames;
    table->setHorizontalHeaderLabels(headers);
    for (int i = 0; i < table->horizontalHeader()->count(); ++i) {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    QPushButton *removeButton = new QPushButton("Remove", this);
    QPushButton *addAfter = new QPushButton("Add after", this);
    QPushButton *addBefore = new QPushButton("Add before", this);
    QPushButton *goBackBtn = new QPushButton("Back", this);

    QHBoxLayout *menuLayout = new QHBoxLayout;
    menuLayout->addWidget(removeButton);
    menuLayout->addWidget(addAfter);
    menuLayout->addWidget(addBefore);
    menuLayout->addWidget(goBackBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(menuLayout);
    mainLayout->addWidget(table);

    setLayout(mainLayout);

    connect(removeButton, &QPushButton::clicked, this, &BaseTransportWindow::removeLine);
    connect(addBefore, &QPushButton::clicked, this, &BaseTransportWindow::addLineBeforeSelected);
    connect(addAfter, &QPushButton::clicked, this, &BaseTransportWindow::addLineAfterSelected);
    connect(goBackBtn, &QPushButton::clicked, this, &BaseTransportWindow::hide);

    connect(fillingInTransportDataDialog, &FillingInTransportDataDialog::dataFilled, this, &BaseTransportWindow::sendPassTransportDataSignal);
}

BaseTransportWindow::~BaseTransportWindow()
{
    delete ui;
}

void BaseTransportWindow::setFillingInTransportDataDialog() {
    using ::App::Types::Project::Enum::TransportType;
    switch (windowTrType_) {
    case TransportType::Bus:
        fillingInTransportDataDialog = new FillingInTransportDataDialog(
                    "Fill the bus data",
                    {
                        {"Key", nullptr},
                        {"Model", nullptr},
                        {"Year of release", new QIntValidator},
                        {"Amount of wheels", new QIntValidator},
                        {"Amount of passangers", new QIntValidator}},
                    ::App::Types::Project::Enum::Bus);
        break;
    case TransportType::Car:
        fillingInTransportDataDialog = new FillingInTransportDataDialog(
                    "Fill the car data",
                    {
                        {"Key", nullptr},
                        {"Model", nullptr},
                        {"Year of release", new QIntValidator},
                        {"Amount of wheels", new QIntValidator},
                        {"Trunk capacity", new QIntValidator}},
                    ::App::Types::Project::Enum::Car);
        break;
    case TransportType::Airplane:
        fillingInTransportDataDialog = new FillingInTransportDataDialog(
                    "Fill the airplane data",
                    {
                        {"Key", nullptr},
                        {"Model", nullptr},
                        {"Year of release", new QIntValidator},
                        {"Max height", new QIntValidator},
                        {"Amount of propellers", new QIntValidator},
                        {"Wingspan", new QIntValidator}},
                    ::App::Types::Project::Enum::Airplane);
        break;
    case TransportType::Helicopter:
        fillingInTransportDataDialog = new FillingInTransportDataDialog(
                        "Fill the helicopter data",
                        {
                            {"Key", nullptr},
                            {"Model", nullptr},
                            {"Year of release", new QIntValidator},
                            {"Max height", new QIntValidator},
                            {"Amount of propellers", new QIntValidator},
                            {"Nose length", new QIntValidator}},
                        ::App::Types::Project::Enum::Helicopter);
        break;
    case TransportType::Metro:
        fillingInTransportDataDialog = new FillingInTransportDataDialog(
                        "Fill the metro data",
                        {
                            {"Key", nullptr},
                            {"Model", nullptr},
                            {"Year of release", new QIntValidator},
                            {"Number of wheelsets", new QIntValidator},
                            {"Number of wagons", new QIntValidator}},
                        ::App::Types::Project::Enum::Metro);
        break;
    }
}

// TODO: solve table error.
void BaseTransportWindow::updateWindow(const ::App::Types::DataTypes::Tree& trTree) {
    auto trTypeIterator = trTree.begin();
    while (trTypeIterator != trTree.end() && (*trTypeIterator)->getTransportType() != windowTrType_) {
        ++trTypeIterator;
    }

    if (trTypeIterator == trTree.end()) {
        close();
        return;
    }

    table->setRowCount(0);

    int i {};
    for (const auto& trPtr : **trTypeIterator) {
        table->insertRow(i);
        auto t = trPtr->getChild();
        if (dynamic_cast<const App::Types::Project::Bus*>(t)) {
            auto bus = dynamic_cast<const App::Types::Project::Bus*>(t);
            fillTableRowByTransportObjData(i++, {
                                               new QTableWidgetItem(QString::fromStdString(trPtr->getKey())),
                                               new QTableWidgetItem(QString::fromStdString(bus->getModel())),
                                               new QTableWidgetItem(QString::number(bus->getYearOfRelease())),
                                               new QTableWidgetItem(QString::number(bus->getAmountOfWheels())),
                                               new QTableWidgetItem(QString::number(bus->getAmountOfPassengers()))
                                           });
        } else if (dynamic_cast<const App::Types::Project::Car*>(t)) {
            auto car = dynamic_cast<const App::Types::Project::Car*>(t);
            fillTableRowByTransportObjData(i++, {
                                               new QTableWidgetItem(QString::fromStdString(trPtr->getKey())),
                                               new QTableWidgetItem(QString::fromStdString(car->getModel())),
                                               new QTableWidgetItem(QString::number(car->getYearOfRelease())),
                                               new QTableWidgetItem(QString::number(car->getAmountOfWheels())),
                                               new QTableWidgetItem(QString::number(car->getTrunkCapacity()))
                                           });
        } else if (dynamic_cast<const App::Types::Project::Airplane*>(t)) {
            auto airplane = dynamic_cast<const App::Types::Project::Airplane*>(t);
            fillTableRowByTransportObjData(i++, {
                                               new QTableWidgetItem(QString::fromStdString(trPtr->getKey())),
                                               new QTableWidgetItem(QString::fromStdString(airplane->getModel())),
                                               new QTableWidgetItem(QString::number(airplane->getYearOfRelease())),
                                               new QTableWidgetItem(QString::number(airplane->getMaxHeight())),
                                               new QTableWidgetItem(QString::number(airplane->getAmountOfPropellers())),
                                               new QTableWidgetItem(QString::number(airplane->getWingspan()))
                                           });
        } else if (dynamic_cast<const App::Types::Project::Helicopter*>(t)) {
            auto helicopter = dynamic_cast<const App::Types::Project::Helicopter*>(t);
            fillTableRowByTransportObjData(i++, {
                                               new QTableWidgetItem(QString::fromStdString(trPtr->getKey())),
                                               new QTableWidgetItem(QString::fromStdString(helicopter->getModel())),
                                               new QTableWidgetItem(QString::number(helicopter->getYearOfRelease())),
                                               new QTableWidgetItem(QString::number(helicopter->getMaxHeight())),
                                               new QTableWidgetItem(QString::number(helicopter->getAmountOfPropellers())),
                                               new QTableWidgetItem(QString::number(helicopter->getNoseLength()))
                                           });
        } else if (dynamic_cast<const App::Types::Project::Metro*>(t)) {
            auto metro = dynamic_cast<const App::Types::Project::Metro*>(t);
            fillTableRowByTransportObjData(i++, {
                                               new QTableWidgetItem(QString::fromStdString(trPtr->getKey())),
                                               new QTableWidgetItem(QString::fromStdString(metro->getModel())),
                                               new QTableWidgetItem(QString::number(metro->getYearOfRelease())),
                                               new QTableWidgetItem(QString::number(metro->getNumberOfWheelsets())),
                                               new QTableWidgetItem(QString::number(metro->getNumberOfWagons())),
                                           });
        }
    }
}

void BaseTransportWindow::fillTableRowByTransportObjData(std::size_t row, const std::initializer_list<QTableWidgetItem*>& rowItems) {
    std::size_t i {};
    for (const auto& rowItem : rowItems) {
        table->setItem(row, i++, rowItem);
    }
}

void BaseTransportWindow::removeLine() {
    int row = this->table->currentRow();
    if (table->rowCount() == 0) {
        QMessageBox messageBox;
        messageBox.information(this, "Info", "There is no data to delete here!");
        return;
    } else if (row == -1) {
        QMessageBox messageBox;
        messageBox.information(this, "Info", "You need to specify the row!");
        return;
    }
    emit removeObjFromTrTreeByKey(table->item(row, 0)->text(), windowTrType_);
    table->removeRow(row);
}

void BaseTransportWindow::addLineBeforeSelected() {
    int row = this->table->currentRow();
    checkForAddition(row, row);
}

void BaseTransportWindow::addLineAfterSelected() {
    int row = this->table->currentRow();
    checkForAddition(row, row + 1);
}

bool BaseTransportWindow::checkForAddition(int row, int additionRow) {
    if (row == -1 && table->rowCount() > 0) {
        QMessageBox messageBox;
        messageBox.information(this, "Info", "You need to specify the row!");
        return false;
    }

    fillingInTransportDataDialog->clearFields();
    fillingInTransportDataDialog->setRowIdx(additionRow);
    fillingInTransportDataDialog->exec();

    return true;
}

void BaseTransportWindow::sendPassTransportDataSignal(QString key, const App::Types::Project::Transport* tr, ::App::Types::Project::Enum::TransportType trType, int row) {
    emit passTransportData(key, tr, trType, row);
}
