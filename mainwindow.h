#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

enum DIRECTIONS{
    UP = 1,
    DOWN,
    LEFT,
    RIGHT
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void sysTimerTick();
protected:
    void keyPressEvent(QKeyEvent* event);
private:
    Ui::MainWindow *ui;
    QTimer *sysTimer;
    int counter;
    int snake_width;
    void generateRandomLocation();
    void snakeHasEatenFood();
    void updateSnakeMovement(int X,int Y);
    int boardHeight;
    int boardWidth;
    int speed;
    int direction;
};
#endif // MAINWINDOW_H
