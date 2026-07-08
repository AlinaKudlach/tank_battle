#include "mainmenu.h"
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400, 300);
    setStyleSheet("background-color: #000000;");

    QGridLayout *layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(10);

    titleLabel = new QLabel("TANK BATTLE", this);
    titleLabel->setFont(QFont("Arial", 32, QFont::Bold));
    titleLabel->setStyleSheet("color: #00ff00; background: transparent;");
    titleLabel->setAlignment(Qt::AlignCenter);

    QFile file("score.txt");
    int record = 0;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        record = in.readLine().toInt();
        file.close();
    }

    recordLabel = new QLabel("HIGH SCORE: " + QString::number(record), this);
    recordLabel->setFont(QFont("Arial", 14));
    recordLabel->setStyleSheet("color: #ffffff; background: transparent;");
    recordLabel->setAlignment(Qt::AlignCenter);

    playButton = new QPushButton("START", this);
    playButton->setFont(QFont("Arial", 16));
    playButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #000000;"
        "   color: #00ff00;"
        "   border: 2px solid #00ff00;"
        "   padding: 12px 50px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #111111;"
        "}"
        );
    playButton->setFixedSize(180, 50);

    exitButton = new QPushButton("EXIT", this);
    exitButton->setFont(QFont("Arial", 14));
    exitButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #000000;"
        "   color: #ff0000;"
        "   border: 2px solid #ff0000;"
        "   padding: 10px 50px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #111111;"
        "}"
        );
    exitButton->setFixedSize(180, 45);

    layout->addWidget(titleLabel, 0, 0, 1, 1, Qt::AlignCenter);
    layout->addWidget(recordLabel, 1, 0, 1, 1, Qt::AlignCenter);
    layout->addWidget(playButton, 3, 0, 1, 1, Qt::AlignCenter);
    layout->addWidget(exitButton, 4, 0, 1, 1, Qt::AlignCenter);

    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 0);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 0);
    layout->setRowStretch(4, 0);
    layout->setRowStretch(5, 2);

    connect(playButton, &QPushButton::clicked, this, &MainMenu::onPlay);
    connect(exitButton, &QPushButton::clicked, this, &MainMenu::onExit);
}

void MainMenu::onPlay()
{
    emit playGame();
}

void MainMenu::onExit()
{
    qApp->quit();
}