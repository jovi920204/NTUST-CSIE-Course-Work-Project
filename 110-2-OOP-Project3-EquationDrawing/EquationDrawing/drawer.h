//***********************************************************************
//  this Drawer class is the widget, which can draw equation ,x-y axis and grid
//***********************************************************************

#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <fstream>
#include <complex>
#include <QFile>
#include <QList>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPushButton>

#include <map>
#include <vector>
#include "widget.h"
#include "equation.h"


namespace Ui {
class Drawer;
}

class Drawer : public QWidget
{
    Q_OBJECT

public:
    explicit Drawer(QWidget *parent = nullptr);
    ~Drawer();


    int intervalNumber;

    void changeRange(double xmax,double xmin, double ymax, double ymin); // the scale only integer

    void addEquation(Widget *w);

    void zoomIn();

    void zoomOut();

    inline void SetMathCoordinate(Drawer* dialog,QPainter* painter);
    inline void ResetDefaultCoordinate(Drawer* dialog,QPainter* painter);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void receiveAddEquation(Widget *);
    void receiveDeleteEquation(Widget *);

private:
    Ui::Drawer *ui;
    double xMax,xMin,yMax,yMin;
    double xRange, yRange;

    QList<Widget*> equationList;
    // 當CreateButton新增時, 用成員函式新增Widget物件到equationLst裡面
    // visible或是delete也是調用成員函式完成狀態更新或是刪除
    std::map<QString,QString> table; // variable table
    QPointF lastMousePos; // mouse current position
    bool pressflag = false;

};

#endif // DRAWER_H
