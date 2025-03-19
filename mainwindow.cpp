#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SeminarData.hpp"
#include "SeminarManager.hpp"
#include "StudentManager.hpp"
#include <QStringListModel>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    this->setWindowIcon(QIcon("icon.png"));

    setupUI();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // Установка логотипа
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

    // Инициализация моделей
    studentsModel = new QStandardItemModel(this);
    datesModel = new QStandardItemModel(this);
    seminarModel = new QStandardItemModel(this);
    ui->studentsListView->setModel(studentsModel);
    ui->datesListView->setModel(datesModel);
    ui->seminarListView->setModel(seminarModel);
}

void MainWindow::setupConnections()
{
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
}

SeminarData* MainWindow::getSeminarByName(const QString &name)
{
    // Поиск семинара в векторе семинаров
    auto it = std::find_if(seminars.begin(), seminars.end(),
                           [&name](SeminarData &seminar)
                           {
                               return seminar.name == name;
                           });
    // При нахождении семинара возвращаем ссылку на него, иначе - nullptr
    return (it != seminars.end()) ? &(*it) : nullptr;
}

bool MainWindow::validateNotEmpty(const QString &input, const QString &errorMessage)
{
    if (input.trimmed().isEmpty()) {
        log(errorMessage);
        return false;
    }
    return true;
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

void MainWindow::log(QString message)
{
    // Выводим переданное сообщение об ошибке в текстовое поле
    ui->systemMesssgeLable->setText(message);
}

void MainWindow::onSeminarSelected(const QItemSelection &selected, const QItemSelection &deselected) {
    // Проверка на корректное выделение
    if (selected.indexes().isEmpty()) return;

    // Получение индекса выбранного семинара и проверка его валидности
    QModelIndex currentIndex = selected.indexes().first();
    if (!currentIndex.isValid()) return;

    // Получение имени семинара и установка его в lineEdit
    QString seminarName = currentIndex.data(Qt::UserRole).toString();
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
    if (selected.indexes().isEmpty()) {
        return;
    }

    // Получение индекса выбранного студента и проверка на валидность
    QModelIndex studentIndex = selected.indexes().first();
    if (!studentIndex.isValid()) return;

    // Извлечение имени студента и установка его в lineEdit
    QString studentName = studentIndex.data(Qt::UserRole).toString();
    ui->changeStudentLineEdit->setText(studentName);
}

void MainWindow::onAddSeminarButtonClicked() {
    // Получаем имя семинара
    QString name = ui->addSeminarLineEdit->text().trimmed();

    // Проверка на пустое имя
    if (name.isEmpty()) {
        log("Имя семинара не может быть пустым");
        return;
    }

    // Проверка на дубликаты
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
    // Получение индекса выбранного элемента и проверка на корректный выбор
    QModelIndex currentIndex = ui->seminarListView->currentIndex();
    if (!currentIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }
    // Получение имени выделенного семинара
    QString oldSeminarName = currentIndex.data(Qt::UserRole).toString();

    // Получение имени семинара из поля ввода
    QString newSeminarName = ui->changeSeminarLineEdit->text().trimmed();

    // Поиск семинара в векторе семинаров
    for (auto &seminar : seminars) {
        if (seminar.name == oldSeminarName)
        {
            // Создание менеджера семинара
            SeminarManager manager(&seminar);
            // Изменение имени семинара и отлов ошибок
            try {
                manager.changeName(newSeminarName);
            }
            catch (const std::invalid_argument& e) {
                log(e.what());
                return;
            }

            // Обновление модели
            QStandardItem *item = seminarModel->itemFromIndex(currentIndex);
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
    // Получение индекса семинара
    QModelIndex currentIndex = ui->seminarListView->currentIndex();
    if (!currentIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }

    // Получение имени семинара
    QString seminarName = currentIndex.data(Qt::UserRole).toString();

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
                       [&seminarName](const SeminarData& seminar) {
                           return seminar.name == seminarName;
                       }),
        seminars.end()
        );

    // Обновление UI
    seminarModel->removeRow(currentIndex.row());
    studentsModel->clear();
    datesModel->clear();
    ui->seminarListView->selectionModel()->clearSelection();
    log("Семинар успешно удален");
}

void MainWindow::onAddStudentButtonClicked()
{
    // Получение индекса семинара
    QModelIndex currentSeminarIndex = ui->seminarListView->currentIndex();
    if (!currentSeminarIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }

    // Получение имени семинара
    QString seminarName = currentSeminarIndex.data(Qt::UserRole).toString();

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
    // Получение индекса семинара и проверка его валидности
    QModelIndex seminarIndex = ui->seminarListView->currentIndex();
    if (!seminarIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }

    // Получение имени семинара
    QString seminarName = seminarIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени и проверка на корректность выбора
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Проверка выбора студента
    QModelIndex studentIndex = ui->studentsListView->currentIndex();
    if (!studentIndex.isValid()) {
        log("Необходимо выбрать студента");
        return;
    }

    // Получение старого имени из индекса студента и нового из lineEdit
    QString oldName = studentIndex.data(Qt::UserRole).toString();
    QString newName = ui->changeStudentLineEdit->text().trimmed();

    // Проверка на пустое имя
    if (newName.isEmpty()) {
        log("Имя студента не может быть пустым");
        return;
    }

    // Поиск студента в векторе студентов
    auto studentIt = std::find_if(seminar->students.begin(), seminar->students.end(),
                                  [&oldName](const StudentData& s) {
                                      return s.name == oldName;
                                  });
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
    QStandardItem* item = studentsModel->item(studentIndex.row());
    item->setText(newName);
    item->setData(newName, Qt::UserRole);
    log("Имя студента изменено");
}

void MainWindow::onDeleteStudentButtonClicked() {
    // Получение индекса семинара
    QModelIndex seminarIndex = ui->seminarListView->currentIndex();
    if (!seminarIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }

    // Получение имени семинара
    QString seminarName = seminarIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Получение индекса студента
    QModelIndex studentIndex = ui->studentsListView->currentIndex();
    if (!studentIndex.isValid()) {
        log("Необходимо выбрать студента");
        return;
    }

    // Получение имени студента
    QString studentName = studentIndex.data(Qt::UserRole).toString();

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
    studentsModel->removeRow(studentIndex.row());
    ui->changeStudentLineEdit->clear();
    log("Студент успешно удалён");
}

void MainWindow::onAddDateButtonClicked()
{
    // Получение индекса семинара
    QModelIndex currentSeminarIndex = ui->seminarListView->currentIndex();
    if (!currentSeminarIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }

    // Получение имени семинара
    QString seminarName = currentSeminarIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени и проверка егр валидности
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Получение даты из поля
    QDate currentDate = ui->addDateEdit->date();

    // Добавление даты через SeminarManager и отлов исключений
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
    // Получение индекса семинара
    QModelIndex currentSeminarIndex = ui->seminarListView->currentIndex();
    if (!currentSeminarIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }

    // Получение имени семинара
    QString seminarName = currentSeminarIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Получение индекса даты
    QModelIndex currentDateIndex = ui->datesListView->currentIndex();
    if (!currentDateIndex.isValid()) {
        log("Необходимо выбрать дату для изменения");
        return;
    }

    // Получение старой даты
    QDate oldDate = currentDateIndex.data(Qt::UserRole).toDate();

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
    QStandardItem* item = datesModel->itemFromIndex(currentDateIndex);
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
    QModelIndex currentSeminarIndex = ui->seminarListView->currentIndex();
    if (!currentSeminarIndex.isValid()) {
        log("Необходимо выбрать семинар");
        return;
    }

    // Получение имени семинара
    QString seminarName = currentSeminarIndex.data(Qt::UserRole).toString();

    // Получение семинара по имени
    SeminarData* seminar = getSeminarByName(seminarName);
    if (!seminar) {
        log("Семинар не найден");
        return;
    }

    // Получение даты и проверка ее валидности
    QModelIndex currentDateIndex = ui->datesListView->currentIndex();
    if (!currentDateIndex.isValid()) {
        log("Необходимо выбрать дату для удаления");
        return;
    }

    // Получение выбранной даты
    QDate selectedDate = currentDateIndex.data(Qt::UserRole).toDate();

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
    datesModel->removeRow(currentDateIndex.row());
    log("Дата успешно удалена");
}
