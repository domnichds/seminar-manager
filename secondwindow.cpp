#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QStringListModel>
#include <QLineEdit>



SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    this->setWindowIcon(QIcon("icon.png"));

    QStringList subjects;
    subjects << "Алгоритмические языки" << "Интегралы и дифференциальные уравнения"
             << "Математическая логика" << "Основы программирования"
             << "Теория вероятностей" << "Классическая механика"
             << "Алгебра" << "Линейная алгебра" << "Квантовая механика"
             << "Структуры данных" << "Теория чисел" << "Техническая литература"
             << "Математические методы оптимизации" << "Теория графов"
             << "Биология" << "Психология" << "Философия науки"
             << "Информационные системы" << "Экономика"
             << "Физика твердого тела" << "Анализ данных" << "Цифровая электроника"
             << "Технология программирования" << "Моделирование процессов"
             << "Численные методы" << "Теория информации" << "Объектно-ориентированное программирование"
             << "Искусственный интеллект" << "Компьютерная графика" << "Сетевые технологии"
             << "Операционные системы" << "Робототехника" << "Генетика"
             << "Паттерны проектирования" << "Архитектура компьютеров";

    QStringList rowHeaders = {
        "Иванов Иван", "Петров Петр", "Сидоров Алексей", "Морозова Анна", "Васильева Ольга",
        "Смирнов Сергей", "Кузнецов Николай", "Попов Дмитрий", "Лебедев Андрей", "Новиков Михаил",
        "Федоров Александр", "Михайлов Артём", "Егоров Владимир", "Соколова Мария", "Ларина Екатерина",
        "Алексеева Наталья", "Козлова Татьяна", "Степанов Игорь", "Соловьёв Юрий", "Виноградова Анастасия",
        "Белов Денис", "Григорьев Константин", "Дмитриев Виктор", "Крылов Роман", "Макаров Василий",
        "Никифоров Егор", "Овчинников Арсений", "Павлов Максим", "Сергеев Тимофей", "Тихонов Станислав",
        "Фролов Евгений", "Чернов Антон", "Шмидт Михаил", "Яковлев Фёдор", "Куликов Борис",
        "Гаврилов Степан", "Воробьев Валерий", "Зайцев Артём", "Ильин Николай", "Карасев Илья",
        "Лукин Григорий", "Миронов Владислав", "Никитин Павел", "Островский Аркадий", "Пономарев Василий",
        "Романов Геннадий", "Савельев Руслан", "Тимофеев Александр", "Ушаков Павел", "Филиппов Аркадий"
    };

    QStringList colHeaders = {
        "01.01\n2025", "08.01\n2025", "15.01\n2025", "22.01\n2025", "29.01\n2025",
        "05.02\n2025", "12.02\n2025", "19.02\n2025", "26.02\n2025", "05.03\n2025",
        "12.03\n2025", "19.03\n2025", "26.03\n2025", "02.04\n2025", "09.04\n2025",
        "16.04\n2025", "23.04\n2025", "30.04\n2025", "07.05\n2025", "14.05\n2025",
        "21.05\n2025", "28.05\n2025", "04.06\n2025", "11.06\n2025", "18.06\n2025",
        "25.06\n2025", "02.07\n2025", "09.07\n2025", "16.07\n2025", "23.07\n2025",
        "30.07\n2025", "06.08\n2025", "13.08\n2025", "20.08\n2025", "27.08\n2025",
        "03.09\n2025", "10.09\n2025", "17.09\n2025", "24.09\n2025", "01.10\n2025",
        "08.10\n2025", "15.10\n2025", "22.10\n2025", "29.10\n2025", "05.11\n2025",
        "12.11\n2025", "19.11\n2025", "26.11\n2025", "03.12\n2025", "10.12\n2025"
    };


    QStandardItemModel *model = new QStandardItemModel(50, 50, this);
    for (int i = 0; i < rowHeaders.size(); ++i) {
        model->setHeaderData(i, Qt::Vertical, rowHeaders[i]);
    }
    for (int i = 0; i < colHeaders.size(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, colHeaders[i]);
    }
    ui->attendanceTableView->setModel(model);
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

    QStringListModel *listModel = new QStringListModel(subjects, this);
    ui->seminarListView->setModel(listModel);
    ui->seminarListView->setFocusPolicy(Qt::NoFocus);

    ui->markSelectComboBox->addItem("Отсутствовал");
    ui->markSelectComboBox->addItem("Присутствовал");
    ui->markSelectComboBox->addItem("Работал");
    ui->markSelectComboBox->setEditable(false);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

