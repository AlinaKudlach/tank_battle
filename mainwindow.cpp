#include "mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Танковый бой");
    setFixedSize(800, 600);

    stackedWidget = new QStackedWidget(this);

    menu = new MainMenu(this);
    canvas = new GameCanvas(this);

    stackedWidget->addWidget(menu);
    stackedWidget->addWidget(canvas);

    connect(menu, &MainMenu::playGame, this, &MainWindow::startGame);
    connect(canvas, &GameCanvas::gameOver, [this]() {
        QTimer::singleShot(3000, [this]() {
            stackedWidget->setCurrentWidget(menu);
        });
    });

    setCentralWidget(stackedWidget);
}

void MainWindow::startGame()
{
    canvas->resetGame();
    stackedWidget->setCurrentWidget(canvas);
}

MainWindow::~MainWindow() {}