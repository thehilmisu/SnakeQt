#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog);
    this->setFocusPolicy(Qt::NoFocus);
    this->setWindowTitle("Snake");

    boardWidth = this->width();
    boardHeight= this->height();

    sysTimer = new QTimer();
    sysTimer->setInterval(100);
    sysTimer->start();

    counter = 0;

    connect(sysTimer,SIGNAL(timeout()),this,SLOT(sysTimerTick()));

    snake_width = 15;

    ui->lblSnake->setGeometry(0,0,snake_width,15);

    generateRandomLocation();

    speed = 15;

    direction = RIGHT;
}
void MainWindow::generateRandomLocation()
{
    int random_x = (qrand() % (boardWidth-ui->lblFood->width()));
    int random_y = (qrand() % (boardWidth-ui->lblFood->width()));

    while(random_x % 15 != 0)
        random_x+=1;

    while(random_y % 15 != 0)
        random_y+=1;

    //qDebug() << random_x << random_y;
    ui->lblFood->setGeometry(random_x,
                             random_y,
                             15,15);

}
void MainWindow::updateSnakeMovement(int X, int Y)
{
    int currentX = ui->lblSnake->x();
    int currentY = ui->lblSnake->y();

    int new_x = currentX + X;
    int new_y = currentY + Y;

    if(new_x >= boardWidth){
        new_x = 15;
    }
    if(new_y >= boardHeight){
        new_y =15;
    }
    if(new_y <= 0){
        new_y = boardHeight;
    }
    if(new_x <=0){
        new_x = boardWidth;
    }

    ui->lblSnake->setGeometry(new_x,new_y,snake_width,15);

    QRect snakeRect = ui->lblSnake->geometry();

    if(snakeRect.contains(ui->lblFood->x(),ui->lblFood->y()))
    {
        generateRandomLocation();
        snakeHasEatenFood();
    }

}
void MainWindow::snakeHasEatenFood()
{
    snake_width += 15;

    ui->lblSnake->setGeometry(ui->lblSnake->x(),
                              ui->lblSnake->y(),
                              snake_width,
                              ui->lblSnake->height());
}
void MainWindow::sysTimerTick()
{
    counter++;
    if(counter > 1){
        counter = 0;
        switch (direction) {
            case UP:
                updateSnakeMovement(0,-speed);
            break;
            case DOWN:
                updateSnakeMovement(0,speed);
            break;
            case RIGHT:
                updateSnakeMovement(speed,0);
            break;
            case LEFT:
                updateSnakeMovement(-speed,0);
            break;

        }
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Up)
    {
        //qDebug() << "key UP";
        direction = UP;
    }
    else if(event->key() == Qt::Key_Down)
    {
        //qDebug() << "key DOWN";
        direction = DOWN;
    }
    else if(event->key() == Qt::Key_Left)
    {
        //qDebug() << "key LEFT";
        direction = LEFT;
    }
    else if(event->key() == Qt::Key_Right)
    {
        //qDebug() << "key RIGHT";
        direction = RIGHT;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

