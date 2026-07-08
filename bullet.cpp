#include "bullet.h"
#include <QPainter>

Bullet::Bullet(int x, int y, int dx, int dy)
    : x(x), y(y), dx(dx), dy(dy), size(8) {}

void Bullet::move()
{
    x += dx;
    y += dy;
}

void Bullet::draw(QPainter* painter)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(x, y, size, size);
}

QRect Bullet::getRect() const
{
    return QRect(x, y, size, size);
}