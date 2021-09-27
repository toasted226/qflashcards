#include "mainwindow.h"

#include <QApplication>
#include <QStandardPaths>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("toasteddev");
    a.setApplicationName("qflashcards");

    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    if(path.isEmpty())
    {
        qFatal("Could not determine settings storage location");
    }

    QDir directory(path);

    if(directory.mkpath(directory.absolutePath()) && QDir::setCurrent(directory.absolutePath()))
    {
        qDebug() << "Settings in " << QDir::currentPath();
    }

    MainWindow w;
    w.show();
    return a.exec();
}
