#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>
#include <Box2DIncludes/Box2D/Collision/Shapes/b2Shape.h>
#include <Box2DIncludes/Box2D/Dynamics/b2Body.h>
#include <Box2D/Box2D.h>
#include <QDebug>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);

    // Size the texture
    texture.create(800, 500);
    //sprite_texture.loadFromFile("/home/pengxi/Desktop/github/a8-an-educational-app-f18-csconner1998/Test.jpg");
    sprite_texture.loadFromFile("/home/parallels/a8/a8-an-educational-app-f18-csconner1998/Test.jpg");

    sprite_texture.setSmooth(true);

    // Create the sprite
    sprite.setTexture(sprite_texture);
    x = 200;
    y = 200;

    sprite.setOrigin(0,0);
//    sprite.setPosition(x,y);
    sf::RectangleShape square(sf::Vector2f(50, 50));
    square.setOrigin(0,0);
    square.setFillColor(sf::Color::Black);
    square.setPosition(100,250);
    boxes.push_back(square);
    square.setSize(sf::Vector2f(50,75));
    square.setFillColor(sf::Color::Red);
    square.setPosition(200,250);
    boxes.push_back(square);
    square.setSize(sf::Vector2f(50,100));
    square.setFillColor(sf::Color::Blue);
    square.setPosition(300,250);
    boxes.push_back(square);

    //create boxlist for b2dhandler
    std::vector<int*> boxInfo;
    int* toAdd = new int[3]{5, 100, 250};
    boxInfo.push_back(toAdd);
    toAdd = new int[3]{6, 250, 250};
    boxInfo.push_back(toAdd);
    toAdd = new int[3]{7, 450, 250};
    boxInfo.push_back(toAdd);

    this->world = new box2dhandler(boxInfo, 800, 500);
    renderTexture();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::renderTexture);

    //16 millis means 60fps
    timer->start(16);
}


void MainWindow::renderTexture() {
    // Clear the whole texture with red color
    texture.clear(sf::Color::White);
    auto position = world->getBoxPositions();

    this->world->updateWorld();

    std::vector<std::tuple<int,int, float32, int>> boxLocations = world->getBoxPositions();
    for(int counter = 0; counter < boxLocations.size(); counter++)
    {
        std::tuple<int, int, float32, int> location = boxLocations.at(counter);
        sf::RectangleShape square(sf::Vector2f(std::get<3>(location), std::get<3>(location)));
        square.setFillColor(sf::Color::Black);
        square.setPosition(std::get<0>(location), std::get<1>(location));
        square.rotate(std::get<2>(location));
        texture.draw(square);   // shape is a sf::Shape
        square.setPosition(x,y);
    }


//    for(std::vector<sf::RectangleShape>::iterator it = boxes.begin(); it != boxes.end(); ++it)
//    {
//        std::tuple<int, int, float32, int> location = world->getBoxPositions()[0];

//        it->setPosition(600 - std::get<0>(location), 300 - std::get<1>(location));
//        texture.draw(*it);   // shape is a sf::Shape
//    }

    texture.display();

    // Set to a QImage
    QImage qi(texture.getTexture().copyToImage().getPixelsPtr(), 800,500, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();

       ui->label->setPixmap(QPixmap::fromImage(qi));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
//    square.get
    float tempX = event ->x() - ui->label->x();
    float tempY = event ->y() - ui->label->y() - 50;
    for(std::vector<sf::RectangleShape>::size_type i=0; i != boxes.size(); i++)
    {
        if(boxes[i].getGlobalBounds().contains(tempX,tempY))
        {
            boxes[i].setPosition(tempX-25,tempY - 25);
        }
    }

}



void MainWindow::on_mergeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_insertButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_bubbleButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_selectButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_Home_4_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Home_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Home_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Home_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_NextButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_NextButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_NextButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_NextButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}
