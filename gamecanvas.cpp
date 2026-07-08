#include "gamecanvas.h"
#include <QPainter>
#include <QKeyEvent>
#include <QFont>

GameCanvas::GameCanvas(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 600);
    setFocusPolicy(Qt::StrongFocus);
    setStyleSheet("background-color: #000000;");

    for (int i = 0; i < 4; ++i) keys[i] = false;

    connect(&timer, &QTimer::timeout, this, &GameCanvas::updateGame);
}

void GameCanvas::startGame()
{
    isRunning = true;
    gameOverShown = false;
    timer.start(16);
}

void GameCanvas::stopGame()
{
    isRunning = false;
    timer.stop();
}

void GameCanvas::resetGame()
{
    engine.reset();
    gameOverShown = false;
    startGame();
}

void GameCanvas::updateGame()
{
    if (!isRunning) return;

    if (keys[0]) engine.player.move(0, -engine.player.speed);
    if (keys[1]) engine.player.move(0, engine.player.speed);
    if (keys[2]) engine.player.move(-engine.player.speed, 0);
    if (keys[3]) engine.player.move(engine.player.speed, 0);

    engine.update();

    if (engine.enemies.size() < engine.getMaxEnemies() && rand() % 30 == 0) {
        engine.spawnEnemy();
    }

    engine.checkCollisions();

    for (const auto& enemy : engine.enemies) {
        if (engine.player.getRect().intersects(enemy.getRect())) {
            engine.saveHighScoreIfNeeded();
            stopGame();
            gameOverShown = true;
            emit gameOver();
            update();
            return;
        }
    }

    update();
}

void GameCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    engine.player.draw(&painter);

    for (auto& enemy : engine.enemies) {
        enemy.draw(&painter);
    }

    for (auto& bullet : engine.bullets) {
        bullet.draw(&painter);
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 14));
    painter.drawText(10, 30, "Очки: " + QString::number(engine.score));
    painter.drawText(10, 50, "Врагов: " + QString::number(engine.enemies.size()));
    painter.drawText(10, 70, "Уровень: " + QString::number(engine.level));

    if (gameOverShown) {
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 40, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");

        painter.setFont(QFont("Arial", 20));
        painter.setPen(Qt::white);
        painter.drawText(rect().adjusted(0, 60, 0, 0), Qt::AlignCenter,
                         "Очки: " + QString::number(engine.score) +
                             "  Рекорд: " + QString::number(engine.getHighScore()) +
                             "  Уровень: " + QString::number(engine.level));
    }
}

void GameCanvas::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) keys[0] = true;
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) keys[1] = true;
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) keys[2] = true;
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) keys[3] = true;

    if (event->key() == Qt::Key_Space && isRunning) {
        engine.playerShoot();
    }

    if (event->key() == Qt::Key_P) {
        if (isRunning) stopGame();
        else startGame();
    }

    if (event->key() == Qt::Key_R) {
        resetGame();
    }
}

void GameCanvas::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) keys[0] = false;
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) keys[1] = false;
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) keys[2] = false;
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) keys[3] = false;
}