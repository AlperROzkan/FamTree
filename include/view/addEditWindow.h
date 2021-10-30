#ifndef ADDEDITWINDOW_H
#define ADDEDITWINDOW_H

#include <QDialog>

namespace Ui {
class AddEditWindow;
}

class AddEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditWindow(QWidget *parent = nullptr);
    ~AddEditWindow();

private:
    Ui::AddEditWindow *ui;
};

#endif // ADDEDITWINDOW_H
