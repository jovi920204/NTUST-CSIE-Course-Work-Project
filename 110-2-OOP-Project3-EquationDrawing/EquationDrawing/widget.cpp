#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendRemoveItem(const QString &)), parent, SLOT(removeItem(const QString &)));

    srand(time(NULL)); // randomly changing colorWidget's color
    setVisibleStatus(true); // default all of equations are visible
    ui->deleteButton->setIcon(QIcon(":/img/img/delete.png")); // set deleteButton's icon
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::getText()
{
    return ui->lineEdit->text();
}
QColor Widget::getColor(){
    return equationColor;
}

void Widget::setText(const QString &text)
{
    ui->lineEdit->setText(text);
}

void Widget::setVisibleStatus(bool status){
    visible = status;
    if (status == 1){
        ui->visibleButton->setIcon(QIcon(":/img/img/eye_visible.png"));
    }
    else{
        ui->visibleButton->setIcon(QIcon(":/img/img/eye_slash.png"));
    }
}

void Widget::setColor(){
    qDebug() << "set Color";
    ui->colorWidget->setSizeIncrement(100,100);
    QColor qc = QColor::fromHsl(rand()%360,50+rand()%180,150);
    QColor c(qc.red(),qc.green(),qc.blue());
    while(std::find(colorVec.begin(),colorVec.end(),c) != colorVec.end()){
        qc = QColor::fromHsl(rand()%360,50+rand()%180,150);
        c.setRed(qc.red());
        c.setGreen(qc.green());
        c.setBlue(qc.blue());
    }
    colorVec.push_back(c);
    QString r = QString::number(qc.red());
    QString g = QString::number(qc.green());
    QString b = QString::number(qc.blue());
    QString color = "background-color: rgb(" + r + ", " + g + ", " + b +");";
    ui->colorWidget->setStyleSheet(color);
    equationColor = c;
}
void Widget::on_visibleButton_clicked()
{
    if (visible == 1) {
        visible = 0;
        ui->visibleButton->setIcon(QIcon(":/img/img/eye_slash.png"));
    }
    else {
        visible = 1;
        ui->visibleButton->setIcon(QIcon(":/img/img/eye_visible.png"));
    }
}

void Widget::on_deleteButton_clicked()
{
    qDebug("deleteButton clicked func called");
    emit sendRemoveItem(ui->lineEdit->text());
}

void Widget::setLineEditStatus(bool status)
{
    // status = 1 => lineEdit is Editible
    if (status == 0) {
        ui->lineEdit->setReadOnly(true);
    } else {
        ui->lineEdit->setReadOnly(false);
    }
}
void Widget::setError(bool e){
    if (e == 1) {
        ui->colorLabel->setText(tr("E"));
        ui->colorLabel->setAlignment(Qt::AlignCenter);
    }
    else {
        ui->colorLabel->setText(tr(""));
        ui->colorLabel->setAlignment(Qt::AlignCenter);
    }
}


