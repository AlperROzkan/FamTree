#include "include/view/addEditWindow.h"
#include "ui_addEditWindow.h"

AddEditWindow::AddEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditWindow)
{
    ui->setupUi(this);
}

AddEditWindow::~AddEditWindow()
{
    delete ui;
}
