#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculator.h"
#include <string>
#include <QDebug>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    int w = ui->centralWidget->width();
    int h = ui->centralWidget->height();



    //ui->graphicsView->setScaledContents(1);
    ui->graphicsView->setStyleSheet("QLabel { background-color : white; color : blue; }");

    ui->graphicsView->setAlignment(Qt::AlignCenter);


    drawOS();
    QPushButton *calcBut = ui->calcButton;

    connect(calcBut, SIGNAL(clicked()), this, SLOT(calcButton()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calcButton()
{

    QLineEdit *text = ui->lineEdit;

    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    graph = new QPixmap(w, h);

    drawOS();

    QPainter paint;
    paint.begin(graph);
    QPainterPath myPath;

    Calculator calc;
    QPolygon pol;

    for(double i = -graph->width(); i < graph->width(); i+=0.1){
        double y;
        try{
            y = calc.eval(text->text(), i);
            pol.append(QPoint(i+graph->width()/2, -(10*y-graph->height()/2)));

        } catch(int e){
            //printf("%.f\n", i);
            /*paint.setPen(QPen(Qt::black,3));
            paint.drawPoint(i+graph->width()/2, -(y-graph->height()/2));
            paint.setPen(QPen(Qt::black,1));*/
        }


    }

   myPath.addPolygon(pol);
   paint.drawPath(myPath);
   paint.end();
   ui->graphicsView->setPixmap(*graph);


}

 void MainWindow::drawOS(){

     QPainter paint;

     int w = ui->graphicsView->width();
     int h = ui->graphicsView->height();

     ui->graphicsView->setGeometry(5, 5, w, h);
     graph = new QPixmap(w, h);

     paint.begin(graph);
     paint.eraseRect(0, 0, w, h);
     paint.drawLine(0, h/2, w, h/2);
     paint.drawLine(w/2, 0, w/2, h);

     paint.setPen(QPen(Qt::black,3));
     double step = 10.0;
     for(double i = h/2; i <= w; i+=step)
         paint.drawPoint(i, h/2);
     for(double i = h/2; i >= 0; i-=step)
         paint.drawPoint(i, h/2);
     for(double i = w/2; i <= h; i+=step)
         paint.drawPoint(w/2, i);
     for(double i = w/2; i >= 0; i-=step)
         paint.drawPoint(w/2, i);


    paint.end();
    ui->graphicsView->setPixmap(*graph);
    return;

 }
