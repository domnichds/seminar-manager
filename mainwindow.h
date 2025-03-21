#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "DateSortProxyModel.hpp"
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
    QSortFilterProxyModel *seminarProxyModel;
    QStandardItemModel *studentsModel;
    QSortFilterProxyModel *studentsProxyModel;
    QStandardItemModel *datesModel;
    DateSortProxyModel* datesProxyModel;

    void setupUI();
    void setupConnections();
    void log(QString message);

    SeminarData* getSeminarByName(const QString&);
    bool validateNotEmpty(const QString &input, const QString &errorMessage);
    void updateStudentAndDateModels(SeminarData* seminar);
    void refreshAllModels();

private slots:
    void onSeminarSelected(const QItemSelection& selected, const QItemSelection& deselected);
    void onStudentSelected(const QItemSelection& selected, const QItemSelection& deselected);
    void onAddSeminarButtonClicked();
    void onChangeSeminarNameButtonClicked();
    void onDeleteSeminarButtonClicked();
    void onAddStudentButtonClicked();
    void onChangeStudentNameButtonClicked();
    void onDeleteStudentButtonClicked();
    void onAddDateButtonClicked();
    void onEditDateButtonClicked();
    void onDeleteDateButtonClicked();
    void onGoToTableButtonClicked();
    void handleSecondWindowClosed();
};

#endif // MAINWINDOW_H
