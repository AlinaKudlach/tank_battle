#include "tank.h"
#include <QPainter>

Tank::Tank(int x, int y, int size, bool isPlayer)
    : x(x), y(y), size(size), speed(isPlayer ? 5 : 2), isPlayer(isPlayer)
{
    color = isPlayer ? Qt::green : Qt::red;
}

void Tank::draw(QPainter* painter)
{
    painter->setBrush(color);
    painter->setPen(Qt::NoPen);
    painter->drawRect(x, y, size, size);

    painter->setBrush(Qt::yellow);
    painter->setPen(Qt::NoPen);

    switch (direction) {
    case Up:    painter->drawRect(x + size/2 - 3, y - 6, 6, 8); break;
    case Down:  painter->drawRect(x + size/2 - 3, y + size - 2, 6, 8); break;
    case Left:  painter->drawRect(x - 6, y + size/2 - 3, 8, 6); break;
    case Right: painter->drawRect(x + size - 2, y + size/2 - 3, 8, 6); break;
    }
}

void Tank::move(int dx, int dy)
{
    if (dy < 0) direction = Up;
    else if (dy > 0) direction = Down;
    else if (dx < 0) direction = Left;
    else if (dx > 0) direction = Right;

    this->dx = dx;
    this->dy = dy;

    x += dx;
    y += dy;

    if (x < 0) x = 0;
    if (x > 800 - size) x = 800 - size;
    if (y < 0) y = 0;
    if (y > 600 - size) y = 600 - size;
}

QRect Tank::getRect() const
{
    return QRect(x, y, size, size);
}