#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include "gameengine.h"

class GameCanvas : public QWidget
{
    Q_OBJECT

public:
    GameCanvas(QWidget *parent = nullptr);
    void startGame();
    void stopGame();
    void resetGame();
    bool isRunning = false;

signals:
    void gameOver();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateGame();

private:
    QTimer timer;
    GameEngine engine;
    bool keys[4];
    bool gameOverShown = false;
};

#endif