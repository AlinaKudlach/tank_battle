#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);

signals:
    void playGame();

private slots:
    void onPlay();
    void onExit();

private:
    QLabel *titleLabel;
    QPushButton *playButton;
    QPushButton *exitButton;
    QLabel *recordLabel;
};

#endif