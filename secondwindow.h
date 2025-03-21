#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "SeminarManager.hpp"
#include <QStandardItemModel>
#include <qitemselectionmodel.h>
#include <QSortFilterProxyModel>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(std::vector<SeminarData>* seminars, QWidget *parent = nullptr);
    void log(QString);
    void updateSeminarList();
    SeminarData* getSeminarByName(const QString&);
    void onSeminarSelected(const QItemSelection&, const QItemSelection&);
    void updateDataTable(SeminarData*);
    QString convertMark(short);
    QString convertDate(QDate);
    short convertMarkToShort(QString);
    ~SecondWindow();

private:
    std::vector<SeminarData>* seminars;
    QStandardItemModel* seminarListModel;
    QSortFilterProxyModel* seminarProxyModel;
    QStandardItemModel* attendanceTableModel;
    Ui::SecondWindow *ui;

private slots:
    void onSetMarkButtonClicked();
    void onGoBackButtonClicked();
signals:
    void windowClosed();

protected:
    void closeEvent(QCloseEvent *event) override;
};


#endif // SECONDWINDOW_H
