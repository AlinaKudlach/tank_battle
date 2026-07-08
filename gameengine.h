#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QList>
#include "tank.h"
#include "bullet.h"

class GameEngine
{
public:
    GameEngine();
    void reset();
    void update();
    void spawnEnemy();
    void playerShoot();
    void checkCollisions();
    void saveHighScoreIfNeeded();

    int getHighScore() const;
    int getMaxEnemies() const;
    int getEnemySpeed() const;

    Tank player;
    QList<Tank> enemies;
    QList<Bullet> bullets;
    int score = 0;
    int width = 800;
    int height = 600;
    int level = 1;
    int enemiesKilled = 0;
    int enemiesPerLevel = 5;
};

#endif