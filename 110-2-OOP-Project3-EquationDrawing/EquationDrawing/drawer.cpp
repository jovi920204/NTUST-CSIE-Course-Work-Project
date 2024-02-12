#include "drawer.h"
#include "ui_drawer.h"
#include <QGraphicsRectItem>>

Drawer::Drawer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Drawer)
{
    ui->setupUi(this);
    this->setGeometry(0,0,601,601);
    intervalNumber = 10;

    xMax = 10;
    xMin = -10;
    yMax = 10;
    yMin = -10;
    xRange = xMax - xMin;
    yRange = yMax - yMin;
    setMouseTracking(true);
}

Drawer::~Drawer()
{
    delete ui;
}

void Drawer::changeRange(double xmax,double xmin, double ymax, double ymin){
//    qDebug() << xmax << " " << xmin << " " << ymax << " " << ymin;
    if ((xmax - xmin) <= 10 || (ymax - ymin) <= 10){
        return;
    }
    if ((xmax-xmin) >= 600 || (ymax - ymin) >= 600){
        return;
    }
    xMax = xmax, xMin = xmin, yMax = ymax, yMin = ymin;
    Drawer::update();
}

void Drawer::addEquation(Widget *w){
    qDebug() << "Add equation";
    equationList.append(w);
}

void Drawer::receiveAddEquation(Widget *w){
    addEquation(w);
}

void Drawer::receiveDeleteEquation(Widget *w){
    auto iter = std::find(equationList.begin(), equationList.end(), w);
    equationList.erase(iter);
    this->update();
    qDebug() << "deleted from equationList";
}

void Drawer::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    int side = qMin(xMax-xMin,yMax-yMin);
    int x_Pro = 600/(xMax-xMin);

    xRange = xMax - xMin;
    yRange = yMax - yMin;
    QRect rect(0, 0, 600, 600);
    painter.drawRect(rect);
    painter.setViewport(rect);
    this->SetMathCoordinate(this, &painter);

    int interval = intervalNumber;

    // draw x and y axis
    painter.setPen(QPen(Qt::black, 1/x_Pro+(0.1)*xRange/10));
    painter.drawLine(xMin,0,xMax,0);
    painter.drawLine(0,yMin,0,yMax);

    // draw grid => default interval is 10 block + draw marked number
    painter.setPen(QPen(Qt::black,1/x_Pro));
    for (double x=0;x<=xMax;x+=(side/interval)){
        painter.drawLine(QPointF(x,yMin),QPointF(x,yMax));

        this->ResetDefaultCoordinate(this, &painter);
        QFont numberFont("Arial");
        numberFont.setPixelSize(20);
        painter.setFont(numberFont);

        painter.drawText(QPoint((x-xMin)*(600/xRange),(0+yMax)*(600/yRange)), QString::number(x));
        this->SetMathCoordinate(this, &painter);
    }

    painter.setPen(QPen(Qt::black,1/x_Pro));
    for (double x=0;x>=xMin;x-=(side/interval)){
        painter.drawLine(QPointF(x,yMin),QPointF(x,yMax));

        this->ResetDefaultCoordinate(this, &painter);
        QFont numberFont("Arial");
        numberFont.setPixelSize(20);
        painter.setFont(numberFont);

        painter.drawText(QPoint((x-xMin)*(600/xRange),(0+yMax)*(600/yRange)), QString::number(x));
        this->SetMathCoordinate(this, &painter);
    }

    painter.setPen(QPen(Qt::black,1/x_Pro));
    for (double y=0;y<=yMax;y+=(side/interval)){
        painter.drawLine(QPointF(xMin,y),QPointF(xMax,y));

        this->ResetDefaultCoordinate(this, &painter);
        QFont numberFont("Arial");
        numberFont.setPixelSize(20);
        painter.setFont(numberFont);

        painter.drawText(QPoint((0-xMin)*(600/xRange) ,(yMax-y)*(600/yRange)), QString::number(y));
        this->SetMathCoordinate(this, &painter);
    }

    painter.setPen(QPen(Qt::black,1/x_Pro));
    for (double y=0;y>=yMin;y-=(side/interval)){
        painter.drawLine(QPointF(xMin,y),QPointF(xMax,y));

        this->ResetDefaultCoordinate(this, &painter);
        QFont numberFont("Arial");
        numberFont.setPixelSize(20);
        painter.setFont(numberFont);

        painter.drawText(QPoint((0-xMin)*(600/xRange),(yMax-y)*(600/yRange)), QString::number(y));
        this->SetMathCoordinate(this, &painter);
    }

    this->SetMathCoordinate(this, &painter);
    // draw equation;
    double dot = (xMax-xMin)/200.f;
    Equation().clearVariableList();
    for(int i=0;i<equationList.size();i++){
        Widget *w = equationList[i];
        Equation e(w->getText().toStdString());
        try {
            e.checkAndInit();
            if (!w->isVisible()) continue;
            std::string varible = e.getVariable();
            painter.setPen(QPen(w->getColor(),1/x_Pro+(0.1)*xRange/2/10));
            if (varible == "x"){
                double preX = e.calculate(xMin) ,preY = xMin;
                for(double d = xMin+dot; d <= xMax; d+=dot){
                    if (preX > 0 && e.calculate(d) < 0 && preX-e.calculate(d) > xRange){
                        preX = d;
                        preY = e.calculate(d);
                        continue;
                    }
                    painter.drawLine(QPointF(preX, preY), QPointF(e.calculate(d), d));
                    preX = e.calculate(d);
                    preY = d;
                }
            }
            else if (varible == "y"){
                double preX = xMin ,preY = e.calculate(xMin);
                for(double d = xMin+dot; d <= xMax; d+=dot){
                    if (preY > 0 && e.calculate(d) < 0 && preY-e.calculate(d) > yRange){
                        preX = d;
                        preY = e.calculate(d);
                        continue;
                    }
                    painter.drawLine(QPointF(preX, preY), QPointF(d, e.calculate(d)));
                    preX = d;
                    preY = e.calculate(d);
                }
            }
            else {
                e.calculate();

            }
            w->setError(false);

        }
        catch (std::string errorInformation) {
            qDebug() << w->getText() << "Error: " << QString::fromStdString(errorInformation);
            w->setError(true);
        }
    }


}

void Drawer::mousePressEvent(QMouseEvent *event){
    pressflag = true;
}

void Drawer::mouseMoveEvent(QMouseEvent *event){
    int sensity = 600/(xMax-xMin);

    if(pressflag){
        QPointF temp;
        QPointF nowMousePos = event->pos();
        if (lastMousePos.isNull()){
            lastMousePos = nowMousePos;
        }
        else{
            temp = nowMousePos - lastMousePos;
            changeRange(xMax-temp.x()/sensity,xMin-temp.x()/sensity,yMax+temp.y()/sensity,yMin+temp.y()/sensity);
            lastMousePos = nowMousePos;
        }

    }
}

void Drawer::mouseReleaseEvent(QMouseEvent *event){
    pressflag = false;
    lastMousePos = QPoint();
}

void Drawer::wheelEvent(QWheelEvent *event){
    QPoint numDegrees = event->angleDelta();
    if (numDegrees.y() > 0){ // 向前滾動
        this->zoomIn();
    }
    else {
        this->zoomOut();
    }
}

void Drawer::zoomIn(){
    this->changeRange(xMax-1,xMin+1,yMax-1,yMin+1);
}

void Drawer::zoomOut(){
    this->changeRange(xMax+1,xMin-1,yMax+1,yMin-1);
}


inline void Drawer::SetMathCoordinate(Drawer* dialog,QPainter* painter){
    painter->setWindow(xMin, yMax, xRange, -yRange);
}

inline void Drawer::ResetDefaultCoordinate(Drawer* dialog,QPainter* painter){
    painter->setWindow(0, 0,  dialog->width(), dialog->height());
}
