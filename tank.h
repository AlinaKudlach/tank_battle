#ifndef TANK_H
#define TANK_H

#include <QRect>
#include <QColor>
#include <QPainter>

enum Direction { Up, Down, Left, Right };

class Tank
{
public:
    Tank(int x = 0, int y = 0, int size = 30, bool isPlayer = true);

    void draw(QPainter* painter);
    void move(int dx, int dy);
    QRect getRect() const;

    int x, y, size, speed, dx = 0, dy = 0;
    bool isPlayer;
    QColor color;
    Direction direction = Up;
};

#endif