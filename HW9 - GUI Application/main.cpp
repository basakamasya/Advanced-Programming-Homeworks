#include "mainwindow.h"
#include <QApplication>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QVector>
#include <QStringList>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
