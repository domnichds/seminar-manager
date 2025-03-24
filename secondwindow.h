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

private:
    std::vector<SeminarData>* seminars;
    QStandardItemModel* seminarListModel;
    QSortFilterProxyModel* seminarProxyModel;
    QStandardItemModel* attendanceTableModel;
    Ui::SecondWindow *ui;

    void setupUI();
    void setupConnections();

    void log(QString);
    void updateSeminarList();
    SeminarData* getSeminarByName(const QString&);
    void updateDataTable(SeminarData*);
    QString convertMark(short);
    QString convertDate(QDate);
    short convertMarkToShort(QString);
    ~SecondWindow();

private slots:
    void onSeminarSelected(const QItemSelection&, const QItemSelection&);
    void onSetMarkButtonClicked();
    void onGoBackButtonClicked();

signals:
    void windowClosed();

protected:
    void closeEvent(QCloseEvent *event) override;
};


#endif // SECONDWINDOW_H
