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

    graph = new QPixmap(500, 500);

    ui->graphicsView->setPixmap(*graph);
   // ui->graphicsView->setScaledContents(1);
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




    drawOS();

    QPainter paint;
    paint.begin(graph);
    QPainterPath myPath;

    Calculator calc;
    QPolygon pol;

    for(double i = -graph->width(); i < graph->width(); i+=0.5){
        double y;
        try{
            y = calc.eval(text->text(), i);
            pol.append(QPoint(i+graph->width()/2, -(y-graph->height()/2)));

        } catch(int e){
            printf("%d", 1);
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

     paint.begin(graph);
     paint.eraseRect(0, 0, graph->width(), graph->height());
     paint.drawLine(0, graph->height()/2, graph->width(), graph->height()/2);
     paint.drawLine(graph->width()/2 ,0 ,graph->width()/2, graph->height());

     paint.setPen(QPen(Qt::black,3));
     for(double i = -graph->width(); i <= graph->width(); i+=10.0)
         paint.drawPoint(i, graph->height()/2);
     for(double i = -graph->height(); i <= graph->height(); i+=10.0)
         paint.drawPoint(graph->width()/2, i);

    paint.end();
    ui->graphicsView->setPixmap(*graph);
    return;

 }
