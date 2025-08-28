#include "filling_in_transport_data_dialog.h"
#include "ui_filling_in_transport_data_dialog.h"

#include <QtWidgets>
#include "src/data_types/project_types/bus.h"
#include "src/data_types/project_types/car.h"
#include "src/data_types/project_types/airplane.h"
#include "src/data_types/project_types/helicopter.h"
#include "src/data_types/project_types/metro.h"
#include <QString>

FillingInTransportDataDialog::FillingInTransportDataDialog(QString dialogName, std::initializer_list<std::pair<QString, QValidator*>>&& inputFields, ::App::Types::Project::Enum::TransportType trType) :
    ui(new Ui::FillingInTransportDataDialog),
    trType_(trType),
    lineEditsDict(),
    rowIdx_(-1)
{
    setWindowTitle(dialogName);
    setMaximumSize(100, 100);
    QVBoxLayout* vertlayout = new QVBoxLayout(this);

    std::size_t i {};
    for (const auto& pair : inputFields) {
        QLabel* label = new QLabel(pair.first);
        lineEditsDict[i] = new QLineEdit;
        lineEditsDict[i]->setValidator(pair.second);

        QHBoxLayout* rowLayout = new QHBoxLayout;
        rowLayout->addWidget(label);
        rowLayout->addWidget(lineEditsDict[i]);

        vertlayout->addLayout(rowLayout);
        i++;
    }

    QPushButton* agreeBtn = new QPushButton("Save", this);
    connect(agreeBtn, &QPushButton::clicked, this, &FillingInTransportDataDialog::sendDataFilledSignal);
    vertlayout->addWidget(agreeBtn);

    setLayout(vertlayout);
    ui->setupUi(this);
}

FillingInTransportDataDialog::~FillingInTransportDataDialog()
{
    delete ui;
}

void FillingInTransportDataDialog::clearFields() {
    for (auto& [i, lineEditPtr] : lineEditsDict) {
        lineEditPtr->clear();
    }
}

bool FillingInTransportDataDialog::areAllTheFieldsFilledIn() const {
    for (const auto& lineEdit : lineEditsDict) {
        if (lineEdit.second->text().isEmpty()) {
            QMessageBox m;
            m.warning(nullptr, "Error", "You have to fill in all the fields!");
            return false;
        }
    }

    return true;
}

void FillingInTransportDataDialog::sendDataFilledSignal() {
    using ::App::Types::Project::Enum::TransportType;

    if (!areAllTheFieldsFilledIn()) {
        return;
    }

    switch (trType_) {
        case TransportType::Bus:
            emit dataFilled(
                    lineEditsDict[0]->text(),
                    new App::Types::Project::Bus(
                        lineEditsDict[1]->text().toStdString(),
                        lineEditsDict[2]->text().toInt(),
                        lineEditsDict[3]->text().toInt(),
                        lineEditsDict[4]->text().toInt()
                    ),
                    TransportType::Bus,
                    rowIdx_
                );
            break;
        case TransportType::Car:
            emit dataFilled(
                    lineEditsDict[0]->text(),
                    new App::Types::Project::Car(
                        lineEditsDict[1]->text().toStdString(),
                        lineEditsDict[2]->text().toInt(),
                        lineEditsDict[3]->text().toInt(),
                        lineEditsDict[4]->text().toInt()
                    ),
                    TransportType::Car,
                    rowIdx_
                );
            break;
        case TransportType::Airplane:
            emit dataFilled(
                    lineEditsDict[0]->text(),
                    new App::Types::Project::Airplane(
                        lineEditsDict[1]->text().toStdString(),
                        lineEditsDict[2]->text().toInt(),
                        lineEditsDict[3]->text().toInt(),
                        lineEditsDict[4]->text().toInt(),
                        lineEditsDict[5]->text().toInt()
                    ),
                    TransportType::Airplane,
                    rowIdx_
                );
            break;
        case TransportType::Helicopter:
            emit dataFilled(
                    lineEditsDict[0]->text(),
                    new App::Types::Project::Helicopter(
                        lineEditsDict[1]->text().toStdString(),
                        lineEditsDict[2]->text().toInt(),
                        lineEditsDict[3]->text().toInt(),
                        lineEditsDict[4]->text().toInt(),
                        lineEditsDict[5]->text().toInt()
                    ),
                    TransportType::Helicopter,
                    rowIdx_
                );
            break;
        case TransportType::Metro:
            emit dataFilled(
                    lineEditsDict[0]->text(),
                    new App::Types::Project::Metro(
                        lineEditsDict[1]->text().toStdString(),
                        lineEditsDict[2]->text().toInt(),
                        lineEditsDict[3]->text().toInt(),
                        lineEditsDict[4]->text().toInt()
                    ),
                    TransportType::Metro,
                    rowIdx_
                );
            break;
        }

    accept();
}
