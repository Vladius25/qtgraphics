#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool m_bUserIsResizing;
    QPixmap *graph;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void calcButton();
    void drawOS();

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual bool eventFilter(QObject* pObj, QEvent* pEvent);


};



#endif // MAINWINDOW_H
