#include <QtTest>
#include "../tank_battle/tank.h"
#include "../tank_battle/bullet.h"
#include "../tank_battle/gameengine.h"

class TestTankBattle : public QObject
{
    Q_OBJECT

private slots:
    void testTankCreation();
    void testTankMovement();
    void testBulletCreation();
    void testCollision();
    void testLevels();
};

void TestTankBattle::testTankCreation()
{
    Tank tank(100, 200, 30, true);
    QCOMPARE(tank.x, 100);
    QCOMPARE(tank.y, 200);
    QCOMPARE(tank.size, 30);
    QCOMPARE(tank.isPlayer, true);
    QCOMPARE(tank.color, Qt::green);
}

void TestTankBattle::testTankMovement()
{
    Tank tank(100, 100, 30, true);
    tank.move(10, 0);
    QCOMPARE(tank.x, 110);
    QCOMPARE(tank.y, 100);

    tank.move(0, -10);
    QCOMPARE(tank.x, 110);
    QCOMPARE(tank.y, 90);

    QCOMPARE(tank.direction, Up);
}

void TestTankBattle::testBulletCreation()
{
    Bullet bullet(100, 100, 0, -5);
    QCOMPARE(bullet.x, 100);
    QCOMPARE(bullet.y, 100);
    QCOMPARE(bullet.dx, 0);
    QCOMPARE(bullet.dy, -5);

    bullet.move();
    QCOMPARE(bullet.y, 95);
}

void TestTankBattle::testCollision()
{
    Tank tank(100, 100, 30, true);
    QRect rect1 = tank.getRect();
    QCOMPARE(rect1, QRect(100, 100, 30, 30));

    Tank enemy(110, 110, 25, false);
    QRect rect2 = enemy.getRect();
    QVERIFY(rect1.intersects(rect2));

    Tank enemy2(200, 200, 25, false);
    QRect rect3 = enemy2.getRect();
    QVERIFY(!rect1.intersects(rect3));
}

void TestTankBattle::testLevels()
{
    GameEngine engine;
    engine.level = 1;

    QCOMPARE(engine.getMaxEnemies(), 4);
    QCOMPARE(engine.getEnemySpeed(), 1);

    engine.level = 3;
    QCOMPARE(engine.getMaxEnemies(), 6);
    QCOMPARE(engine.getEnemySpeed(), 2);

    engine.level = 5;
    QCOMPARE(engine.getMaxEnemies(), 8);
    QCOMPARE(engine.getEnemySpeed(), 3);
}

QTEST_APPLESS_MAIN(TestTankBattle)

#include "tst_testtankbattle.moc"