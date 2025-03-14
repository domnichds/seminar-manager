#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include "Seminar.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void log(QString);
    std::vector<Seminar> seminars;
    QStandardItemModel *seminarModel;

private slots:
    void onAddSeminarButtonClicked();
    void onSeminarSelected(const QItemSelection&, const QItemSelection&);
    void onChangeSeminarNameButtonClicked();
};
#endif // MAINWINDOW_H
