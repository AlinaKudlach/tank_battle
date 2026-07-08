#include "gameengine.h"
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <ctime>

GameEngine::GameEngine()
{
    srand(time(nullptr));
    reset();
}

void GameEngine::reset()
{
    player = Tank(400, 300, 30, true);
    enemies.clear();
    bullets.clear();
    score = 0;
    level = 1;
    enemiesKilled = 0;
}

int GameEngine::getMaxEnemies() const
{
    return qMin(3 + level, 10);
}

int GameEngine::getEnemySpeed() const
{
    return 1 + (level - 1) / 2;
}

void GameEngine::update()
{
    int enemySpeed = getEnemySpeed();

    for (auto& enemy : enemies) {
        if (rand() % 15 == 0) {
            enemy.move((rand() % 3 - 1) * enemySpeed, (rand() % 3 - 1) * enemySpeed);
        } else {
            enemy.move(enemy.dx, enemy.dy);
        }

        if (enemy.x < 0 || enemy.x > width) enemy.x = 10;
        if (enemy.y < 0 || enemy.y > height) enemy.y = 10;
    }

    for (int i = bullets.size() - 1; i >= 0; --i) {
        bullets[i].move();
        if (bullets[i].x < -20 || bullets[i].x > width + 20 ||
            bullets[i].y < -20 || bullets[i].y > height + 20) {
            bullets.removeAt(i);
        }
    }
}

void GameEngine::spawnEnemy()
{
    int x = rand() % width;
    int y = rand() % height;
    enemies.append(Tank(x, y, 25, false));
}

void GameEngine::playerShoot()
{
    if (bullets.size() >= 1) return;

    int x = player.x + player.size / 2 - 4;
    int y = player.y + player.size / 2 - 4;

    switch (player.direction) {
    case Up:    bullets.append(Bullet(x, y, 0, -8)); break;
    case Down:  bullets.append(Bullet(x, y, 0, 8)); break;
    case Left:  bullets.append(Bullet(x, y, -8, 0)); break;
    case Right: bullets.append(Bullet(x, y, 8, 0)); break;
    }
}

void GameEngine::checkCollisions()
{
    for (int i = bullets.size() - 1; i >= 0; --i) {
        for (int j = enemies.size() - 1; j >= 0; --j) {
            if (bullets[i].getRect().intersects(enemies[j].getRect())) {
                bullets.removeAt(i);
                enemies.removeAt(j);
                score += 10;
                enemiesKilled++;

                if (enemiesKilled >= enemiesPerLevel) {
                    level++;
                    enemiesKilled = 0;
                }
                break;
            }
        }
    }
}

int GameEngine::getHighScore() const
{
    QFile file("score.txt");
    if (!file.open(QIODevice::ReadOnly)) return 0;
    QTextStream in(&file);
    int hs = in.readLine().toInt();
    file.close();
    return hs;
}

void GameEngine::saveHighScoreIfNeeded()
{
    int current = getHighScore();
    if (score > current) {
        QFile file("score.txt");
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << score;
            file.close();
        }
    }
}