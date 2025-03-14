#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Seminar.h"
#include <QStringListModel>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    this->setWindowIcon(QIcon("icon.png"));

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->logoGraphicView->setScene(scene);
    QPixmap pixmap("logo.png");
    if (pixmap.isNull()) {
        qDebug() << "Ошибка загрузки изображения!";
        return;
    }
    QSize viewSize = ui->logoGraphicView->size();
    QPixmap scaledPixmap = pixmap.scaled(viewSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QGraphicsPixmapItem *item = scene->addPixmap(scaledPixmap);
    item->setTransformationMode(Qt::SmoothTransformation);
    scene->setSceneRect(0, 0, viewSize.width(), viewSize.height());
    ui->logoGraphicView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->logoGraphicView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    item->setPos((viewSize.width() - scaledPixmap.width()) / 2, (viewSize.height() - scaledPixmap.height()) / 2);

    seminarModel = new QStandardItemModel(this);
    ui->seminarListView->setModel(seminarModel);
    connect(ui->addSeminarButton, &QPushButton::clicked, this, &MainWindow::onAddSeminarButtonClicked);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddSeminarButtonClicked()
{
    QString name = ui->addSeminarLineEdit->text();

    for (auto seminar : seminars)
    {
        if (seminar.name == name) throw std::invalid_argument("Семинар уже существет");
    }
    if (name.isEmpty()) throw std::invalid_argument("Имя семинара не может быть пустым");
    Seminar new_seminar(name);
    seminars.push_back(new_seminar);
    QStandardItem *item = new QStandardItem(new_seminar.name);
    seminarModel->appendRow(item);
    ui->addSeminarLineEdit->clear();
}



/*    QStringList listDates;
    listDates << "01.02.2025" << "08.02.2025" << "15.02.2025" << "22.02.2025" << "29.02.2025" << "07.03.2025"
              << "14.03.2025" << "21.03.2025" << "28.03.2025" << "04.04.2025" << "11.04.2025" << "18.04.2025"
              << "25.04.2025" << "02.05.2025" << "09.05.2025" << "16.05.2025" << "23.05.2025" << "30.05.2025"
              << "06.06.2025" << "13.06.2025" << "20.06.2025" << "27.06.2025" << "04.07.2025" << "11.07.2025"
              << "18.07.2025" << "25.07.2025" << "01.08.2025" << "08.08.2025" << "15.08.2025" << "22.08.2025"
              << "29.08.2025" << "05.09.2025" << "12.09.2025" << "19.09.2025" << "26.09.2025" << "03.10.2025"
              << "10.10.2025" << "17.10.2025" << "24.10.2025" << "31.10.2025" << "07.11.2025" << "14.11.2025"
              << "21.11.2025" << "28.11.2025" << "05.12.2025" << "12.12.2025" << "19.12.2025" << "26.12.2025"
              << "02.01.2026" << "09.01.2026" << "16.01.2026" << "23.01.2026" << "30.01.2026";

    QStringList listSeminar;
    listSeminar << "Алгоритмические языки" << "Интегралы и дифференциальные уравнения"
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

    QStringList listStudents;
    listStudents << "Домнич Данил" << "Дмитриев Александр" << "Малахов Михаил"
                 << "Петров Иван" << "Смирнов Алексей" << "Иванов Сергей"
                 << "Кузнецов Артем" << "Попов Владимир" << "Лебедев Андрей"
                 << "Григорьев Денис" << "Соловьев Виктор" << "Васильев Константин"
                 << "Тимофеев Павел" << "Шмидт Марк" << "Морозов Станислав"
                 << "Захаров Борис" << "Морозова Светлана" << "Федоров Сергей"
                 << "Козлов Владимир" << "Чеснокова Ольга" << "Коваленко Михаил"
                 << "Николаев Николай" << "Лазарев Владислав" << "Тарасов Роман"
                 << "Семёнов Алексей" << "Сидоров Павел" << "Григориева Юлия"
                 << "Романова Елена" << "Михайлова Татьяна" << "Филиппов Дмитрий"
                 << "Боровиков Максим" << "Мищенко Игорь" << "Никитин Павел"
                 << "Баринов Артем" << "Костина Мария" << "Козлова Анастасия"
                 << "Чистякова Ирина" << "Богданова Ирина" << "Щербаков Валерий"
                 << "Кулешова Вера" << "Жукова Лилия" << "Смирнов Роман"
                 << "Котова Дарина" << "Кудрявцева Наталья" << "Мищенко Екатерина"
                 << "Новикова Алёна" << "Мартынов Валентин" << "Голубева Инна"
                 << "Щербина Марина" << "Карасев Сергей" << "Егорова Дарина"
                 << "Лавров Константин";

    QStringListModel *modelItems = new QStringListModel(this);
    modelItems->setStringList(listDates);
    ui->datesListView->setModel(modelItems);

    QStringListModel *modelDates = new QStringListModel(this);
    modelDates->setStringList(listSeminar);
    ui->seminarListView->setModel(modelDates);

    QStringListModel *modelStudents = new QStringListModel(this);
    modelStudents->setStringList(listStudents);
    ui->studentsListView->setModel(modelStudents);
*/
