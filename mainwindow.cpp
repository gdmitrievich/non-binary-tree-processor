#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>

#include "src/utility/utility.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      table(),
      trTree(),
      trTypeDialog(),
      trWindows()
{   
    ui->setupUi(this);
    setWindowTitle("Transport types");
    setMaximumWidth(100);

    table = new QTableWidget(0, 2, this);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList headers = {"Transport_type", "Number"};
    table->setHorizontalHeaderLabels(headers);
    table->setColumnWidth(1, 60);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);

    QPushButton *loadButton = new QPushButton("Load", this);
    QPushButton *saveButton = new QPushButton("Save", this);

    QPushButton *removeButton = new QPushButton("Remove", this);
    QPushButton *addAfter = new QPushButton("Add after", this);
    QPushButton *addBefore = new QPushButton("Add before", this);

    QHBoxLayout *menuLayout = new QHBoxLayout;
    menuLayout->addWidget(loadButton);
    menuLayout->addWidget(saveButton);
    menuLayout->addWidget(removeButton);
    menuLayout->addWidget(addAfter);
    menuLayout->addWidget(addBefore);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(menuLayout);
    mainLayout->addWidget(table);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadData);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveData);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeLine);
    connect(addAfter, &QPushButton::clicked, this, &MainWindow::addLineAfterSelected);
    connect(addBefore, &QPushButton::clicked, this, &MainWindow::addLineBeforeSelected);

    connect(table,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(openAdditionalWindow(int,int)));

    trTypeDialog = new TransportTypeDialog;

    trWindows[::App::Types::Project::Enum::Bus] = new BaseTransportWindow("Bus info", {"Key", "Model", "Year of release", "Amount of wheels", "Amount of passangers"}, ::App::Types::Project::Enum::Bus);
    trWindows[::App::Types::Project::Enum::Car] = new BaseTransportWindow("Car info", {"Key", "Model", "Year of release", "Amount of wheels", "Trunk capacity"}, ::App::Types::Project::Enum::Car);
    trWindows[::App::Types::Project::Enum::Airplane] = new BaseTransportWindow("Airplane info", {"Key", "Model", "Year of release", "Max height", "Amount of propellers", "Wingspan"}, ::App::Types::Project::Enum::Airplane);
    trWindows[::App::Types::Project::Enum::Helicopter] = new BaseTransportWindow("Helicopter info", {"Key", "Model", "Year of release", "Max height", "Amount of propellers", "Nose length"}, ::App::Types::Project::Enum::Helicopter);
    trWindows[::App::Types::Project::Enum::Metro] = new BaseTransportWindow("Metro info", {"Key", "Model", "Year of release", "Number of wheelsets", "Number of wagons"}, ::App::Types::Project::Enum::Metro);

    for (auto& [type, trWindowPtr] : trWindows) {
        connect(trWindowPtr, &BaseTransportWindow::passTransportData, this, &MainWindow::obtainTransportObjData);
        connect(trWindowPtr, &BaseTransportWindow::removeObjFromTrTreeByKey, this, &MainWindow::removeTrObjFromTreeByKey);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// TODO: you must solve situation in which data file doesn't choosen!
void MainWindow::loadData() {
    trTree.clear();
    ::App::Utility::FileManagment::Load(QFileDialog::getOpenFileName(this, "Choose file with transport data!", QDir::currentPath(), "*.txt (*.txt)"), trTree);
    updateTable();
    updateTrObjWindows();
}

void MainWindow::saveData() {
    ::App::Utility::FileManagment::Save(QFileDialog::getOpenFileName(this, "Choose file to save transport data!", QDir::currentPath(), "*.txt (*.txt)"), trTree);
}

void MainWindow::removeLine() {
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

    ::App::Types::Project::Enum::TransportType type = ::App::Utility::TransportType::strToTransportType(table->item(row, 0)->text());
    trTree.removeParent(type);
    table->removeRow(row);
    if (trWindows[type]->isVisible()) {
        trWindows[type]->close();
    }
}

void MainWindow::addLineBeforeSelected() {
    int row = this->table->currentRow();
    if (!checkForAddition(row, row))
        return;

    if (row <= 0) {
        table->insertRow(0);
        updateTable();
    } else {
        row--;
        table->insertRow(row);
        updateTable();
    }
}

void MainWindow::addLineAfterSelected() {
    int row = this->table->currentRow();
    if (!checkForAddition(row, row + 1))
        return;

    row++;
    table->insertRow(row);
    updateTable();
}

bool MainWindow::checkForAddition(int row, int additionRow) {
    if (isTableFull()) {
        QMessageBox messageBox;
        messageBox.information(this, "Info", "You can no longer add new types of transport because there are no others anymore!");
        return false;
    }

    if (row == -1 && table->rowCount() > 0) {
        QMessageBox messageBox;
        messageBox.information(this, "Info", "You need to specify the row!");
        return false;
    }

    trTypeDialog->exec();

    if (trTypeDialog->getSelectedTransportType() == ::App::Types::Project::Enum::TransportType::Default)
        return false;

    if (!trTree.addParent(trTypeDialog->getSelectedTransportType(), additionRow)) {
        QMessageBox messageBox;
        messageBox.information(this, "Info", "This type of the transport already exists!");
        return false;
    }

    return true;
}

void MainWindow::openAdditionalWindow(int row, int col) {
    using ::App::Types::Project::Enum::TransportType;
    switch (::App::Utility::TransportType::strToTransportType(table->item(row, 0)->text())) {
        case TransportType::Bus:
            openSpecificTransportWindow(TransportType::Bus);
            break;
        case TransportType::Car:
            openSpecificTransportWindow(TransportType::Car);
            break;
        case TransportType::Airplane:
            openSpecificTransportWindow(TransportType::Airplane);
            break;
        case TransportType::Helicopter:
            openSpecificTransportWindow(TransportType::Helicopter);
            break;
        case TransportType::Metro:
            openSpecificTransportWindow(TransportType::Metro);
            break;
    }
}

void MainWindow::openSpecificTransportWindow(::App::Types::Project::Enum::TransportType trType) {
    if (trWindows[trType]->isVisible()) {
        QMessageBox messageBox;
        messageBox.information(this, "Error", "You have already opened this window!");
        return;
    }

    trWindows[trType]->updateWindow(trTree);
    trWindows[trType]->show();
}

void MainWindow::obtainTransportObjData(QString key, const App::Types::Project::Transport* tr, ::App::Types::Project::Enum::TransportType trType, int row) {
    if (!trTree.add(key.toStdString(), tr, trType, row)) {
        QMessageBox messageBox;
        messageBox.information(this, "Info", QString::fromStdString(::App::Utility::TransportType::transportTypeToStr(trType).toStdString() + " with key \"" + key.toStdString() + "\" already exists!"));
        return;
    }

    trWindows[trType]->updateWindow(trTree);
    updateTable();
}

void MainWindow::removeTrObjFromTreeByKey(QString key, ::App::Types::Project::Enum::TransportType trType) {
    trTree.remove(key.toStdString(), trType);
    updateTable();
}

void MainWindow::updateTable() {
    table->setRowCount(0);
    for (int i {}; i < trTree.count(); ++i)
        table->insertRow(0);

    int i {};
    for (const auto& parentPtr : trTree) {
        QTableWidgetItem *item = new QTableWidgetItem(::App::Utility::TransportType::transportTypeToStr(parentPtr->getTransportType()));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(parentPtr->count()));
        table->setItem(i, 0, item);
        table->setItem(i, 1, item2);
        i++;
    }
}

void MainWindow::updateTrObjWindows() {
    for (auto& [type, trWindowPtr] : trWindows) {
        if (trWindowPtr->isVisible())
            trWindowPtr->updateWindow(trTree);
    }
}

// Close all windows.
void MainWindow::closeEvent(QCloseEvent *event)
{
    trTypeDialog->close();
    for (auto& [type, windowPtr] : trWindows) {
        windowPtr->close();
    }
    QMainWindow::closeEvent(event);
}
