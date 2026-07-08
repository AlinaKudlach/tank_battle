#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyleSheet(
        "QWidget { background-color: #000000; }"
        "QPushButton { background-color: #000000; }"
        );

    MainWindow w;
    w.show();

    return app.exec();
}