#ifndef TRANSPORT_TYPE_DIALOG_H
#define TRANSPORT_TYPE_DIALOG_H

#include <QDialog>
#include "src/data_types/project_types/transport_type.h"
#include <QComboBox>

namespace Ui {
class TransportTypeDialog;
}

class TransportTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransportTypeDialog(QWidget *parent = nullptr);
    ~TransportTypeDialog();

    ::App::Types::Project::Enum::TransportType getSelectedTransportType() const {return trType_;}

private:
    Ui::TransportTypeDialog *ui;
    QComboBox* trTypesBox;

    ::App::Types::Project::Enum::TransportType trType_;

private slots:
    void updateTrType(int result);
};

#endif // TRANSPORT_TYPE_DIALOG_H
