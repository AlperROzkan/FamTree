#include "../include/view/mainwindow.h"
#include "../include/view/addEditWindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Buttons
    {
        connect(ui->buttonAdd, 
            SIGNAL(clicked()), 
            this, 
            SLOT(ButtonAddPerson()));

        connect(ui->buttonEdit,
            SIGNAL(clicked()),
            this,
            SLOT(ButtonEditPerson()));

        connect(ui->buttonDelete,
            SIGNAL(clicked()),
            this,
            SLOT(ButtonDeletePerson()));
    }
}

void MainWindow::ButtonAddPerson() {
    AddEditWindow addEditWindow;
    addEditWindow.setModal(true);
    addEditWindow.exec();
}

void MainWindow::ButtonDeletePerson() {

}

void MainWindow::ButtonEditPerson() {

}

MainWindow::~MainWindow()
{
    delete ui;
}

