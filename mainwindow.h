#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "DateSortProxyModel.hpp"
#include "SeminarData.hpp"
#include "SeminarManager.hpp"
#include "CSVHandler.hpp"

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
    std::vector<SeminarData> seminars; // Получаем из .csv
    QStandardItemModel *seminarModel;
    QSortFilterProxyModel *seminarProxyModel; // Прокси модель для сортировки семинаров
    QStandardItemModel *studentsModel;
    QSortFilterProxyModel *studentsProxyModel; // Прокси модель для сортировки семинаров
    QStandardItemModel *datesModel;
    DateSortProxyModel* datesProxyModel; // Кастомная прокси модель для сортировки дат

    void setupUI(); // Метод для настройки элементов UI
    void setupConnections(); // Метод для установки привязок

    void log(QString message); // Метод для вывода пользовательских сообщений
    SeminarData* getSeminarByName(const QString&); // Получение ссылки на семинар по имени
    void updateStudentAndDateModels(SeminarData* seminar); // Обновление списка дат и студентов
    void refreshAllModels(); // Обновление всех 3 списков

private slots:
    // В onSeminarSelected и onStudentSelected &deselected не исползуется
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

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
