#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "gamecanvas.h"
#include "mainmenu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startGame();

private:
    QStackedWidget *stackedWidget;
    MainMenu *menu;
    GameCanvas *canvas;
};

#endif