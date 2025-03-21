#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QStringListModel>
#include <QLineEdit>

SecondWindow::SecondWindow(std::vector<SeminarData>* seminars, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::SecondWindow), seminars(seminars)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    this->setWindowIcon(QIcon("icon.png"));

    setWindowTitle("Таблица посещаемости");
    setWindowFlags(Qt::Window);
    seminarListModel = new QStandardItemModel(this);
    seminarProxyModel = new QSortFilterProxyModel(this);
    attendanceTableModel = new QStandardItemModel(this);

    seminarProxyModel->setSourceModel(seminarListModel);
    seminarProxyModel->setSortRole(Qt::UserRole);
    seminarProxyModel->sort(0, Qt::AscendingOrder);

    ui->seminarListView->setModel(seminarProxyModel);
    ui->seminarListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->seminarListView->setFocusPolicy(Qt::NoFocus);

    ui->attendanceTableView->setModel(attendanceTableModel);
    ui->attendanceTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->attendanceTableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->attendanceTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->attendanceTableView->horizontalHeader()->setStyleSheet("background: transparent;");
    ui->attendanceTableView->verticalHeader()->setStyleSheet("background: transparent;");
    ui->attendanceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->attendanceTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->attendanceTableView->setCornerButtonEnabled(false);
    QFont font("ALS Sector Regular", 12);
    ui->attendanceTableView->setFont(font);

    ui->markSelectComboBox->addItem("Отсутствовал");
    ui->markSelectComboBox->addItem("Присутствовал");
    ui->markSelectComboBox->addItem("Работал");
    ui->markSelectComboBox->setEditable(false);

    updateSeminarList();
    connect(ui->seminarListView->selectionModel(), &QItemSelectionModel::selectionChanged,this, &SecondWindow::onSeminarSelected);
    connect(ui->goBackButton, &QPushButton::clicked, this, &SecondWindow::onGoBackButtonClicked);
    connect(ui->putMarkButton, &QPushButton::clicked, this, &SecondWindow::onSetMarkButtonClicked);
}

void SecondWindow::log(QString message)
{
    // Установка текста для сообщений
    ui->systemMesssgeLable->setText(message);
}

QString SecondWindow::convertMark(short mark)
{
    switch (mark) {
    case -1: return QString::fromStdString("Н");
    case 0: return QString::fromStdString("П");
    case 1: return QString::fromStdString("Р");
    }
}

QString SecondWindow::convertDate(QDate date)
{
    QString new_date = date.toString("dd.MM\nyyyy");
    return new_date;
}

short SecondWindow::convertMarkToShort(QString mark)
{
    if (mark == "Отсутствовал") return -1;
    else if (mark == "Присутствовал") return 0;
    else if (mark == "Работал") return 1;
}

void SecondWindow::updateSeminarList() {
    seminarListModel->clear();
    for (const auto& seminar : *seminars) {
        QStandardItem* item = new QStandardItem(seminar.name);
        item->setData(seminar.name, Qt::UserRole);
        seminarListModel->appendRow(item);
    }
}

SeminarData* SecondWindow::getSeminarByName(const QString &name)
{
    // Поиск семинара в векторе семинаров
    auto it = std::find_if(seminars->begin(), seminars->end(),
                           [&name](SeminarData &seminar)
                           {
                               return seminar.name == name;
                           });
    // При нахождении семинара возвращаем ссылку на него, иначе - nullptr
    return (it != seminars->end()) ? &(*it) : nullptr;
}

void SecondWindow::onSeminarSelected(const QItemSelection& selected, const QItemSelection& deselected) {
    Q_UNUSED(deselected);

    if (selected.isEmpty()) {
        attendanceTableModel->clear();
        return;
    }

    QModelIndex proxyIndex = selected.indexes().first();
    QModelIndex sourceIndex = seminarProxyModel->mapToSource(proxyIndex);
    QString seminarName = sourceIndex.data(Qt::UserRole).toString();
    SeminarData* seminar = getSeminarByName(seminarName);

    if (!seminar) return;

    updateDataTable(seminar);
}

void SecondWindow::updateDataTable(SeminarData* seminar) {
    attendanceTableModel->clear();

    // Сортировка дат в хронологическом порядке
    std::vector<QDate> sortedDates = seminar->dates;
    std::sort(sortedDates.begin(), sortedDates.end());

    // Сортировка студентов по алфавиту
    std::vector<StudentData> sortedStudents = seminar->students;
    std::sort(sortedStudents.begin(), sortedStudents.end(),
              [](const StudentData& a, const StudentData& b) {
                  return a.name < b.name;
              }
              );

    // Установка заголовков столбцов
    QStringList colHeaders;
    for (const QDate& date : sortedDates) {
        colHeaders << convertDate(date);
    }
    attendanceTableModel->setHorizontalHeaderLabels(colHeaders);

    // Заполнение таблицы данными
    QStringList rowHeaders;
    int row = 0;
    for (const StudentData& student : sortedStudents) {
        rowHeaders << student.name;
        for (int col = 0; col < sortedDates.size(); ++col) {
            QDate date = sortedDates[col];
            short mark = student.marks.at(date);
            QStandardItem* item = new QStandardItem(convertMark(mark));
            attendanceTableModel->setItem(row, col, item);
        }
        ++row;
    }
    attendanceTableModel->setVerticalHeaderLabels(rowHeaders);
}

void SecondWindow::onSetMarkButtonClicked()
{
    // Проверка выбранной ячейки
    QModelIndex currentIndex = ui->attendanceTableView->currentIndex();
    if (!currentIndex.isValid()) {
        log("Выберите ячейку в таблице!");
        return;
    }

    // Получение данных из выделенной ячейки
    int row = currentIndex.row();
    int col = currentIndex.column();

    // Получение имени студента из заголовка строки
    QString studentName = attendanceTableModel->headerData(row, Qt::Vertical).toString();

    // Получение даты из заголовка столбца
    QString dateStr = attendanceTableModel->headerData(col, Qt::Horizontal).toString();
    QDate date = QDate::fromString(dateStr, "dd.MM\nyyyy");
    if (!date.isValid()) {
        log("Ошибка формата даты!");
        return;
    }

    // Получение выбранного семинара
    QModelIndex seminarIndex = ui->seminarListView->currentIndex();
    if (!seminarIndex.isValid()) {
        log("Выберите семинар!");
        return;
    }

    QString seminarName = seminarIndex.data(Qt::UserRole).toString();
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден!");
        return;
    }

    // Поиск студента по имени
    auto studentIt = std::find_if(seminar->students.begin(), seminar->students.end(),
                                  [&studentName](const StudentData& s) { return s.name == studentName; });

    if (studentIt == seminar->students.end()) {
        log("Студент не найден!");
        return;
    }

    // Проверка существования даты в семинаре
    auto dateIt = std::find(seminar->dates.begin(), seminar->dates.end(), date);
    if (dateIt == seminar->dates.end()) {
        log("Дата не найдена в семинаре!");
        return;
    }

    // Получение оценки из ComboBox
    QString markStr = ui->markSelectComboBox->currentText();
    short mark;
    try {
        mark = convertMarkToShort(markStr);
    }
    catch (const std::invalid_argument& e) {
        log(e.what());
        return;
    }

    // Обновление оценки
    studentIt->marks[date] = mark;

    // Обновление таблицы
    updateDataTable(seminar);

    log("Оценка успешно обновлена!");
}

void SecondWindow::onGoBackButtonClicked()
{
    emit windowClosed();
    this->close();
}

void SecondWindow::closeEvent(QCloseEvent *event) {
    emit windowClosed();
    QMainWindow::closeEvent(event);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

