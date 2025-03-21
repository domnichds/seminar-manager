#ifndef DATESORTPROXYMODEL_HPP
#define DATESORTPROXYMODEL_HPP

#include <QSortFilterProxyModel>
#include <QDate>

class DateSortProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
public:
    explicit DateSortProxyModel(QObject* parent = nullptr);

protected:
    bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
};

#endif // DATESORTPROXYMODEL_HPP
