#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include <QPainter>

class Bullet
{
public:
    Bullet(int x = 0, int y = 0, int dx = 0, int dy = -5);

    void move();
    void draw(QPainter* painter);
    QRect getRect() const;

    int x, y, dx, dy, size;
};

#endif