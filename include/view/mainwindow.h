#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public Q_SLOTS:

    /**
     * @brief Adding person
     * 
     */
    void ButtonAddPerson();

    /**
    * @brief Deleting person
    *
    */
    void ButtonDeletePerson();

    /**
    * @brief Edit person
    *
    */ 
    void ButtonEditPerson();
};
#endif // MAINWINDOW_H
