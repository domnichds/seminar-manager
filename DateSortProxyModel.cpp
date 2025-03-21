#include "DateSortProxyModel.hpp"

DateSortProxyModel::DateSortProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent) {}

bool DateSortProxyModel::lessThan(const QModelIndex& left, const QModelIndex& right) const {
    // Парсинг строк в даты
    QString leftStr = sourceModel()->data(left).toString();
    QString rightStr = sourceModel()->data(right).toString();

    QDate leftDate = QDate::fromString(leftStr, "dd.MM.yyyy");
    QDate rightDate = QDate::fromString(rightStr, "dd.MM.yyyy");

    // Сравнение дат
    return leftDate < rightDate;
}
