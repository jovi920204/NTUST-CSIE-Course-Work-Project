//***********************************************************************
//  this MainWindow class is control all the widget, and caonnect to the user's action,
//  createButton and listWidget is letting user to add and edit equation.
//***********************************************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include "widget.h"
#include "drawer.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int rec;

signals:
    void sendAddEquation(Widget *);
    void sendDeleteEquation(Widget *);

private slots:
    void on_addButton_clicked();

    void removeItem(const QString &text);

    void on_drawButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
