#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rec = 0;

    ui->DrawerWidget = new Drawer(this);

    connect(this, SIGNAL(sendAddEquation(Widget *)), ui->DrawerWidget, SLOT(receiveAddEquation(Widget *)));
    connect(this, SIGNAL(sendDeleteEquation(Widget *)), ui->DrawerWidget, SLOT(receiveDeleteEquation(Widget *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    auto item = new QListWidgetItem();
    Widget *widget = new Widget(this);
//    widget->setText(QString::number(ui->listWidget->count()));

    item->setSizeHint(widget->sizeHint());
    widget->setColor();
    widget->setText("");
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, widget);
    emit sendAddEquation(widget);
}

void MainWindow::removeItem(const QString &text)
{
    qDebug("removeItem func called");
    for(int i = 0; i < ui->listWidget->count(); i++) {
        auto item = ui->listWidget->item(i);
        auto itemWidget = dynamic_cast<Widget*>(ui->listWidget->itemWidget(item));
        if(itemWidget->getText() == text) {
            emit sendDeleteEquation(itemWidget);
            delete item;
            return;
        }
    }

}

void MainWindow::on_drawButton_clicked()
{
    // update the equationList and update the Drawer widget
    ui->DrawerWidget->update();
}

