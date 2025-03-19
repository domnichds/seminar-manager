#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QStandardItemModel>
#include "SeminarData.hpp"
#include "SeminarManager.hpp"

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
    std::vector<SeminarData> seminars;
    QStandardItemModel *seminarModel;
    QStandardItemModel *studentsModel;
    QStandardItemModel *datesModel;

    void setupUI();
    void setupConnections();
    void log(QString message);

    SeminarData* getSeminarByName(const QString&);
    bool validateNotEmpty(const QString &input, const QString &errorMessage);
    void updateStudentAndDateModels(SeminarData* seminar);

private slots:
    void onAddSeminarButtonClicked();
    void onSeminarSelected(const QItemSelection& selected, const QItemSelection& deselected);
    void onStudentSelected(const QItemSelection& selected, const QItemSelection& deselected);
    void onChangeSeminarNameButtonClicked();
    void onDeleteSeminarButtonClicked();
    void onAddDateButtonClicked();
    void onDeleteDateButtonClicked();
    void onEditDateButtonClicked();
    void onAddStudentButtonClicked();
    void onChangeStudentNameButtonClicked();
    void onDeleteStudentButtonClicked();
};

#endif // MAINWINDOW_H
