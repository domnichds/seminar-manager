#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SeminarData.hpp"
#include "SeminarManager.hpp"
#include "StudentManager.hpp"
#include "secondwindow.h"
#include "DateSortProxyModel.hpp"
#include <QStringListModel>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    setupUI();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    ui->setupUi(this);
    setFixedSize(this->size()); // Запрет изменения размера окна
    this->setWindowIcon(QIcon("icon.png"));
    setWindowTitle("Редактирование списка семинаров");

    // Установка логотипа
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->logoGraphicView->setScene(scene);
    QPixmap pixmap("logo.png");
    if (pixmap.isNull()) {
        qDebug() << "Ошибка загрузки изображения!";
        return;
    }
    // Подгонка pixmap под нужный размер и установка его на созданную сцену
    QSize viewSize = ui->logoGraphicView->size();
    // Qt::KeepAspectRatioByExpanding для сохранения пропорций, Qt::SmoothTransformation для мин. потерей качества
    QPixmap scaledPixmap = pixmap.scaled(viewSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QGraphicsPixmapItem *item = scene->addPixmap(scaledPixmap);
    item->setTransformationMode(Qt::SmoothTransformation);
    scene->setSceneRect(0, 0, viewSize.width(), viewSize.height());
    // Отключение полос прокрутки
    ui->logoGraphicView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->logoGraphicView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Центрирование изображения
    item->setPos((viewSize.width() - scaledPixmap.width()) / 2, (viewSize.height() - scaledPixmap.height()) / 2);

    // Инициализация моделей
    seminarModel = new QStandardItemModel(this);
    seminarProxyModel = new QSortFilterProxyModel(this);
    studentsModel = new QStandardItemModel(this);
    studentsProxyModel = new QSortFilterProxyModel(this);
    datesModel = new QStandardItemModel(this);
    datesProxyModel = new DateSortProxyModel(this);
    // Установка родителей для прокси моделей
    seminarProxyModel->setSourceModel(seminarModel);
    studentsProxyModel->setSourceModel(studentsModel);
    datesProxyModel->setSourceModel(datesModel);
    // Привязка моделей к спискам
    ui->studentsListView->setModel(studentsProxyModel);
    ui->datesListView->setModel(datesProxyModel);
    ui->seminarListView->setModel(seminarProxyModel);
    // Установка правил сортировки для списков
    seminarProxyModel->sort(0, Qt::AscendingOrder);
    studentsProxyModel->sort(0, Qt::AscendingOrder);
    datesProxyModel->sort(0, Qt::AscendingOrder);
    // Устновка автоматической сортировки при добавлении элементов
    seminarProxyModel->setDynamicSortFilter(true);
    studentsProxyModel->setDynamicSortFilter(true);
    datesProxyModel->setDynamicSortFilter(true);

    // Отключение возможности изменять элементы списков
    ui->seminarListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->studentsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->datesListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setupConnections()
{
    // Установка соединений (объект UI; сигнал; ссылка на окно; метод, вызваемый при срабатывании сигнала)
    connect(ui->addSeminarButton, &QPushButton::clicked, this, &MainWindow::onAddSeminarButtonClicked);
    connect(ui->seminarListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onSeminarSelected);
    connect(ui->studentsListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onStudentSelected);
    connect(ui->changeSeminarButton, &QPushButton::clicked, this, &MainWindow::onChangeSeminarNameButtonClicked);
    connect(ui->deleteSeminarButton, &QPushButton::clicked, this, &MainWindow::onDeleteSeminarButtonClicked);
    connect(ui->addDateButton, &QPushButton::clicked, this, &MainWindow::onAddDateButtonClicked);
    connect(ui->deleteDateButton, &QPushButton::clicked, this, &MainWindow::onDeleteDateButtonClicked);
    connect(ui->editDateButton, &QPushButton::clicked, this, &MainWindow::onEditDateButtonClicked);
    connect(ui->addStudentButton, &QPushButton::clicked, this, &MainWindow::onAddStudentButtonClicked);
    connect(ui->changeStudentButton, &QPushButton::clicked, this, &MainWindow::onChangeStudentNameButtonClicked);
    connect(ui->deleteStudentButton, &QPushButton::clicked, this, &MainWindow::onDeleteStudentButtonClicked);
    connect(ui->goToTableButton, &QPushButton::clicked, this, &MainWindow::onGoToTableButtonClicked);
};

void MainWindow::log(QString message)
{
    // Выводим переданное сообщение об ошибке в текстовое поле
    ui->systemMesssgeLable->setText(message);
}

SeminarData* MainWindow::getSeminarByName(const QString &name)
{
    // Поиск семинара в векторе семинаров
    auto it = std::find_if(seminars.begin(), seminars.end(),
    [&name](SeminarData &seminar){return seminar.name == name;});
    // При нахождении семинара возвращаем ссылку на него, иначе - nullptr
    return (it != seminars.end()) ? &(*it) : nullptr;
}

void MainWindow::updateStudentAndDateModels(SeminarData* seminar)
{
    // Выход из метода, если передано nullptr
    if (!seminar) return;

    // Очистка списков студентов и дат
    studentsModel->clear();
    datesModel->clear();

    // Заполнение списка студентов
    for (const auto &student : seminar->students) {
        QStandardItem *item = new QStandardItem(student.name);
        item->setData(student.name, Qt::UserRole);
        studentsModel->appendRow(item);
    }

    // Заполнение списка дат
    for (const QDate &date : seminar->dates) {
        QStandardItem *item = new QStandardItem(date.toString("dd.MM.yyyy")); // Перевод QDate в строку
        item->setData(date, Qt::UserRole);
        datesModel->appendRow(item);
    }
}

void MainWindow::onSeminarSelected(const QItemSelection &selected, const QItemSelection &deselected) {
    // Проверка на корректное выделение
    if (selected.indexes().isEmpty()) return;

    // Получение индекса и имени выбранного семинара
    QModelIndex proxyIndex = selected.indexes().first();
    if (!proxyIndex.isValid()) return;
    QModelIndex sourceIndex = seminarProxyModel->mapToSource(proxyIndex);
    QString seminarName = sourceIndex.data(Qt::UserRole).toString();
    ui->changeSeminarLineEdit->setText(seminarName);
    // Получение ссылки на семинар
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден"); // Проверка на nullptr
        return;
    }

    // Обновление списка дат и студентов
    updateStudentAndDateModels(&(*seminar));
}

void MainWindow::onStudentSelected(const QItemSelection &selected, const QItemSelection &deselected) {
    // Проверка на пустой выбор
    if (selected.indexes().isEmpty()) return;

    // Получение индекса и имени выбранного студента
    QModelIndex proxyIndex = selected.indexes().first();
    if (!proxyIndex.isValid()) return;
    QModelIndex sourceIndex = studentsProxyModel->mapToSource(proxyIndex);
    QString studentName = sourceIndex.data(Qt::UserRole).toString();

    // Установка имени в поле для редактирования
    ui->changeStudentLineEdit->setText(studentName);
}

void MainWindow::onAddSeminarButtonClicked() {
    // Получаем имя семинара и проверяем его на пустоту и дубликаты
    QString name = ui->addSeminarLineEdit->text().trimmed();
    if (name.isEmpty()) {
        log("Имя семинара не может быть пустым");
        return;
    }
    if (getSeminarByName(name)) {
        log("Семинар уже существует");
        return;
    }

    // Создание SeminarData и добавление его в вектор семинаров
    seminars.emplace_back(name);

    // Обновление UI
    QStandardItem *item = new QStandardItem(name);
    item->setData(name, Qt::UserRole);
    seminarModel->appendRow(item);
    ui->addSeminarLineEdit->clear();
    log("Семинар успешно добавлен");
}

void MainWindow::onChangeSeminarNameButtonClicked()
{
    // Получение индекса и имени выбранного семинара
    QModelIndex currentProxyIndex = ui->seminarListView->currentIndex();
    if (!currentProxyIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }
    QModelIndex sourceIndex = seminarProxyModel->mapToSource(currentProxyIndex);
    QString oldSeminarName = sourceIndex.data(Qt::UserRole).toString();

    // Получение имени семинара из поля ввода
    QString newSeminarName = ui->changeSeminarLineEdit->text().trimmed();

    // Поиск семинара в векторе семинаров
    for (auto &seminar : seminars) {
        if (seminar.name == oldSeminarName)
        {
            // Создание менеджера семинара и изменение имени семинара
            SeminarManager manager(&seminar);
            try {
                manager.changeName(newSeminarName);
            }
            catch (const std::invalid_argument& e) {
                log(e.what());
                return;
            }

            // Обновление модели
            QStandardItem *item = seminarModel->itemFromIndex(sourceIndex);
            if (item) {
                item->setText(newSeminarName);
                item->setData(newSeminarName, Qt::UserRole);
            }
            log("Имя семинара изменено");
            return; // Выход из метода после успешного изменения имени
        }
    }
    log("Семинар не найден"); // Если цикл не нашел seminar.name == oldSeminarName
}

void MainWindow::onDeleteSeminarButtonClicked()
{
    // Получение индекса и имени выбранного семинара
    QModelIndex proxyIndex = ui->seminarListView->currentIndex();
    if (!proxyIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }
    QModelIndex sourceIndex = seminarProxyModel->mapToSource(proxyIndex);
    QString seminarName = sourceIndex.data(Qt::UserRole).toString();

    // Диалог подтверждения
    QMessageBox confirmBox;
    confirmBox.setWindowTitle("Удаление семинара");
    confirmBox.setText("Вы действительно хотите удалить семинар \"" + seminarName + "\"?");
    confirmBox.setIcon(QMessageBox::Question);
    confirmBox.addButton("Удалить", QMessageBox::YesRole);
    confirmBox.addButton("Отмена", QMessageBox::NoRole);
    if (confirmBox.exec() == QMessageBox::No) return;

    // Удаление семинара из вектора семинаров
    seminars.erase(
        std::remove_if(seminars.begin(), seminars.end(),
        [&seminarName](const SeminarData& seminar) {return seminar.name == seminarName;}),
        seminars.end()
    );

    // Обновление UI
    seminarModel->removeRow(sourceIndex.row());
    studentsModel->clear();
    datesModel->clear();
    ui->seminarListView->selectionModel()->clearSelection();
    log("Семинар успешно удален");
}

void MainWindow::onAddStudentButtonClicked()
{
    // Получение индекса и имени семинара
    QModelIndex seminarProxyIndex = ui->seminarListView->currentIndex();
    if (!seminarProxyIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }
    QModelIndex seminarSourceIndex = seminarProxyModel->mapToSource(seminarProxyIndex);
    QString seminarName = seminarSourceIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Получение имени студента и проверка на пустоту
    QString studentName = ui->addStudentLineEdit->text().trimmed();
    if (studentName.isEmpty()) {
        log("Имя студента не может быть пустым");
        return;
    }

    // Добавление студента через SeminarManager и отлов исключений
    try {
        SeminarManager manager(&(*seminar));
        manager.addStudent(studentName);
    }
    catch (const std::invalid_argument& e) {
        log(e.what());
        return;
    }

    // Обновление UI
    QStandardItem* studentItem = new QStandardItem(studentName);
    studentItem->setData(studentName, Qt::UserRole);
    studentsModel->appendRow(studentItem);
    ui->addStudentLineEdit->clear();
    log("Студент успешно добавлен");
}

void MainWindow::onChangeStudentNameButtonClicked()
{
    // Получение индекса и имени выбранного семинара
    QModelIndex seminarProxyIndex = ui->seminarListView->currentIndex();
    if (!seminarProxyIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }
    QModelIndex seminarSourceIndex = seminarProxyModel->mapToSource(seminarProxyIndex);
    QString seminarName = seminarSourceIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени и проверка на корректность выбора
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Проверка выбора студента
    QModelIndex studentProxyIndex = ui->studentsListView->currentIndex();
    if (!studentProxyIndex.isValid()) {
        log("Необходимо выбрать студента");
        return;
    }

    // Получение старого имени из индекса студента и нового из lineEdit
    QModelIndex studentSourceIndex = studentsProxyModel->mapToSource(studentProxyIndex);
    QString oldName = studentSourceIndex.data(Qt::UserRole).toString();
    QString newName = ui->changeStudentLineEdit->text().trimmed();

    // Проверка на пустое имя
    if (newName.isEmpty()) {
        log("Имя студента не может быть пустым");
        return;
    }

    // Поиск студента в векторе студентов
    auto studentIt = std::find_if(seminar->students.begin(), seminar->students.end(),
    [&oldName](const StudentData& s) {return s.name == oldName;});
    if (studentIt == seminar->students.end()) {
        log("Студент не найден");
        return;
    }

    // Изменение имени через studentManager и отлов исключений
    try {
        StudentManager manager(&(*studentIt));
        manager.changeName(newName, seminar->students);
    }
    catch (const std::invalid_argument& e) {
        log(e.what());
        return;
    }

    // Обновление UI
    QStandardItem* item = studentsModel->item(studentSourceIndex.row());
    item->setText(newName);
    item->setData(newName, Qt::UserRole);
    log("Имя студента изменено");
}

void MainWindow::onDeleteStudentButtonClicked() {
    // Получение индекса и имени выбранного семинара
    QModelIndex seminarProxyIndex = ui->seminarListView->currentIndex();
    if (!seminarProxyIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }
    QModelIndex seminarSourceIndex = seminarProxyModel->mapToSource(seminarProxyIndex);
    QString seminarName = seminarSourceIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Получение индекса и имени выбранного студента
    QModelIndex studentProxyIndex = ui->studentsListView->currentIndex();
    if (!studentProxyIndex.isValid()) {
        log("Необходимо выбрать студента");
        return;
    }
    QModelIndex studentSourceIndex = studentsProxyModel->mapToSource(studentProxyIndex);
    QString studentName = studentSourceIndex.data(Qt::UserRole).toString();

    // Подтверждение удаления
    QMessageBox confirmBox;
    confirmBox.setWindowTitle("Удаление студента");
    confirmBox.setText("Вы действительно хотите удалить студента \"" + studentName + "\"?");
    confirmBox.setIcon(QMessageBox::Question);
    confirmBox.addButton("Удалить", QMessageBox::YesRole);
    confirmBox.addButton("Отмена", QMessageBox::NoRole);
    if (confirmBox.exec() == QMessageBox::No) return;

    // Удаление студента через SeminarManager и отлов исключений
    try {
        SeminarManager manager(&(*seminar));
        manager.deleteStudent(studentName);
    }
    catch (const std::invalid_argument& e) {
        log(e.what());
        return;
    }

    // Обновление UI
    studentsModel->removeRow(studentSourceIndex.row());
    ui->changeStudentLineEdit->clear();
    log("Студент успешно удалён");
}

void MainWindow::onAddDateButtonClicked()
{
    // Получение индекса и имени выбранного семинара
    QModelIndex seminarProxyIndex = ui->seminarListView->currentIndex();
    if (!seminarProxyIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }
    QModelIndex seminarSourceIndex = seminarProxyModel->mapToSource(seminarProxyIndex);
    QString seminarName = seminarSourceIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени и проверка его валидности
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Добавление даты через SeminarManager и отлов исключений
    QDate currentDate = ui->addDateEdit->date();
    try {
        SeminarManager manager(&(*seminar));
        manager.addDate(currentDate);
    }
    catch (const std::invalid_argument& e) {
        log(e.what());
        return;
    }

    // Обновление UI
    QStandardItem* dateItem = new QStandardItem(currentDate.toString("dd.MM.yyyy"));
    dateItem->setData(currentDate, Qt::UserRole);
    datesModel->appendRow(dateItem);
    log("Дата успешно добавлена");
}

void MainWindow::onEditDateButtonClicked()
{
    // Получение индекса и имени выбранного семинара
    QModelIndex seminarProxyIndex = ui->seminarListView->currentIndex();
    if (!seminarProxyIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }
    QModelIndex seminarSourceIndex = seminarProxyModel->mapToSource(seminarProxyIndex);
    QString seminarName = seminarSourceIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Получение индекса и значения даты
    QModelIndex dateProxyIndex = ui->datesListView->currentIndex();
    if (!dateProxyIndex.isValid()) {
        log("Необходимо выбрать дату для изменения");
        return;
    }
    QModelIndex dateSourceIndex = datesProxyModel->mapToSource(dateProxyIndex);
    QDate oldDate = dateSourceIndex.data(Qt::UserRole).toDate();

    // Получение новой даты из поля редактирования даты
    QDate newDate = ui->editDateEdit->date();

    // Добавление даты через SeminarManager и отлов исключений
    try {
        SeminarManager manager(&(*seminar));
        manager.editDate(oldDate, newDate);
    }
    catch (const std::invalid_argument& e) {
        log(e.what());
        return;
    }

    // Обновление UI
    QStandardItem* item = datesModel->itemFromIndex(dateSourceIndex);
    if (item) {
        item->setData(newDate, Qt::UserRole);
        item->setText(newDate.toString("dd.MM.yyyy"));
        log("Дата успешно изменена");
    } else {
        log("Ошибка обновления даты");
    }
}

void MainWindow::onDeleteDateButtonClicked()
{
    // Получение индекса семинара
    QModelIndex seminarProxyIndex = ui->seminarListView->currentIndex();
    if (!seminarProxyIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }

    // Получение имени семинара
    QModelIndex seminarSourceIndex = seminarProxyModel->mapToSource(seminarProxyIndex);
    QString seminarName = seminarSourceIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Получение даты и проверка ее валидности
    QModelIndex dateProxyIndex = ui->datesListView->currentIndex();
    if (!dateProxyIndex.isValid()) {
        log("Необходимо выбрать дату для удаления");
        return;
    }

    // Получение выбранной даты
    QModelIndex dateSourceIndex = datesProxyModel->mapToSource(dateProxyIndex);
    QDate selectedDate = dateSourceIndex.data(Qt::UserRole).toDate();

    // Удаление данных через SeminarManager и отлов исключений
    try {
        SeminarManager manager(&(*seminar));
        manager.deleteDate(selectedDate);
    }
    catch (const std::exception& e) {
        log(e.what());
        return;
    }

    // Удаляем дату из модели
    datesModel->removeRow(dateSourceIndex.row());
    log("Дата успешно удалена");
}

void MainWindow::onGoToTableButtonClicked()
{
    // Вызов конструктора второго окна
    SecondWindow* secondWindow = new SecondWindow(&seminars);
    secondWindow->show();
    connect(secondWindow, &SecondWindow::windowClosed, this, &MainWindow::handleSecondWindowClosed);
    // Скрытие основного окна
    this->hide();
}

void MainWindow::handleSecondWindowClosed() {
    this->show(); // Показываем MainWindow
    refreshAllModels(); // Обновляем данные
}

void MainWindow::refreshAllModels() {
    // Обновление списка семинаров
    seminarModel->clear();
    for (const auto& seminar : seminars) {
        QStandardItem* item = new QStandardItem(seminar.name);
        item->setData(seminar.name, Qt::UserRole);
        seminarModel->appendRow(item);
    }

    // Обновление студентов и дат текущего семинара
    QModelIndex proxyIndex = ui->seminarListView->currentIndex();
    if (proxyIndex.isValid()) {
        QModelIndex sourceIndex = seminarProxyModel->mapToSource(proxyIndex);
        QString seminarName = sourceIndex.data(Qt::UserRole).toString();
        SeminarData* seminar = getSeminarByName(seminarName);
        updateStudentAndDateModels(seminar);
    } else {
        studentsModel->clear();
        datesModel->clear();
    }
}
