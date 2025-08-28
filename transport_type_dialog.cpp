#include "transport_type_dialog.h"
#include "ui_transport_type_dialog.h"

#include <QtWidgets>
#include "src/utility/utility.h"

TransportTypeDialog::TransportTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransportTypeDialog),
    trTypesBox(),
    trType_(::App::Types::Project::Enum::Default)
{
    setWindowTitle("Select transport type");
    setMaximumSize(100, 100);
    QVBoxLayout* vertlayout = new QVBoxLayout(this);

    QHBoxLayout* rowLayout = new QHBoxLayout;
    QLabel* label = new QLabel("Type: ");
    rowLayout->addWidget(label);

    trTypesBox = new QComboBox;
    trTypesBox->addItem(QString("Default"));
    trTypesBox->addItem(QString("Bus"));
    trTypesBox->addItem(QString("Car"));
    trTypesBox->addItem(QString("Airplane"));
    trTypesBox->addItem(QString("Helicopter"));
    trTypesBox->addItem(QString("Metro"));
    rowLayout->addWidget(trTypesBox);

    vertlayout->addLayout(rowLayout);

    QPushButton* agreeBtn = new QPushButton("Ok", this);
    connect(agreeBtn, &QPushButton::clicked, this, &TransportTypeDialog::updateTrType);
    connect(this, &TransportTypeDialog::finished, this, &TransportTypeDialog::updateTrType);
    connect(agreeBtn, &QPushButton::clicked, this, &TransportTypeDialog::accept);

    vertlayout->addWidget(agreeBtn);

    setLayout(vertlayout);
    ui->setupUi(this);
}

TransportTypeDialog::~TransportTypeDialog()
{
    delete ui;
}

void TransportTypeDialog::updateTrType(int result) {
    trType_ = ::App::Utility::TransportType::strToTransportType(trTypesBox->currentText());
}
