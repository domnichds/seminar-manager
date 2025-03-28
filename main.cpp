#include "mainwindow.h"
#include "secondwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Загрузка шрифтов
    int idBold = QFontDatabase::addApplicationFont(":/ALS Sector/ALS_Sector-Bold.otf");
    if (idBold == -1) {
        qDebug() << "Не удалось загрузить ALS_Sector-Bold.otf";
    } else {
        qDebug() << "ALS_Sector-Bold.otf успешно загружен";
    }

    int idRegular = QFontDatabase::addApplicationFont(":/ALS Sector/ALS_Sector-Regular.otf");
    if (idRegular == -1) {
        qDebug() << "Не удалось загрузить ALS_Sector-Regular.otf";
    } else {
        qDebug() << "ALS_Sector-Regular.otf успешно загружен";
    }
    MainWindow w;
    w.show();
    a.setQuitOnLastWindowClosed(false);
    return a.exec();
}
