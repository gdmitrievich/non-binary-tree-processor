#ifndef FILLING_IN_TRANSPORT_DATA_DIALOG_H
#define FILLING_IN_TRANSPORT_DATA_DIALOG_H

#include <QDialog>
#include <QValidator>
#include <QLineEdit>

#include "src/data_types/project_types/transport_type.h"
#include "src/data_types/project_types/transport.h"

namespace Ui {
class FillingInTransportDataDialog;
}

class FillingInTransportDataDialog : public QDialog
{
    Q_OBJECT

public:
    FillingInTransportDataDialog(QString dialogName, std::initializer_list<std::pair<QString, QValidator*>>&& inputFields, ::App::Types::Project::Enum::TransportType trType);
    ~FillingInTransportDataDialog();

    void setRowIdx(int rowIdx) {rowIdx_ = rowIdx;}

    void clearFields();

private:
    Ui::FillingInTransportDataDialog *ui;
    ::App::Types::Project::Enum::TransportType trType_;
    std::unordered_map<std::size_t, QLineEdit*> lineEditsDict;
    int rowIdx_;

    bool areAllTheFieldsFilledIn() const;

private slots:
    void sendDataFilledSignal();

signals:
    void dataFilled(QString key, const App::Types::Project::Transport* tr, ::App::Types::Project::Enum::TransportType trType, int rowIdx);
};

#endif // FILLING_IN_TRANSPORT_DATA_DIALOG_H
