#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Seminar.h"
#include <QStringListModel>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
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

    studentsModel = new QStandardItemModel(this);
    datesModel = new QStandardItemModel(this);
    seminarModel = new QStandardItemModel(this);
    ui->studentsListView->setModel(studentsModel);
    ui->datesListView->setModel(datesModel);
    ui->seminarListView->setModel(seminarModel);

    connect(ui->addSeminarButton, &QPushButton::clicked, this, &MainWindow::onAddSeminarButtonClicked);
    connect(ui->seminarListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onSeminarSelected);
    connect(ui->studentsListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onStudentSelected);
    connect(ui->changeSeminarButton, &QPushButton::clicked, this, &MainWindow::onChangeSeminarNameButtonClicked);
    connect(ui->deleteSeminarButton, &QPushButton::clicked, this, &MainWindow::onDeleteSeminarButtonClicked);
    connect(ui->addDateButton, &QPushButton::clicked, this, &MainWindow::onAddDateButtonClicked);
    connect(ui->deleteDateButton, &QPushButton::clicked, this, &MainWindow::onDeleteDateButtonClicked);
    connect(ui->editDateButton, &QPushButton::clicked, this, &MainWindow::onEditDateButtonClicked);
    connect(ui->addStudentButton, &QPushButton::clicked, this, &MainWindow::onAddStudentButtonClicked);
    connect(ui->changeStudentButton, &QPushButton::clicked, this, &::MainWindow::onChangeStudentNameButtonClicked);
    connect(ui->deleteStudentButton, &QPushButton::clicked, this, &MainWindow::onDeleteStudentButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::log(QString message)
{
    // Выводим переданное сообщение об ошибке в текстовое поле
    ui->systemMesssgeLable->setText(message);
}

void MainWindow::onAddSeminarButtonClicked() {
    // Получаем данные из поля ввода имени семинара
    QString name = ui->addSeminarLineEdit->text();

    // Проверяем, есть ли семинар с таким именем в списке семинаров
    for (auto &seminar : seminars)
    {
        if (seminar.name == name) {log(QString::fromStdString("Семинар уже существет")); return;}
    }

    // Проверяем имя семинара на пустую строку
    if (name.isEmpty())
    {
        log(QString::fromStdString("Имя семинара не может быть пустым"));
        return;
    }

    Seminar new_seminar(name);
    seminars.push_back(new_seminar);

    // Добавляем объект созданного семинара в список seminarListView
    QStandardItem *item = new QStandardItem(new_seminar.name);
    item->setData(new_seminar.name, Qt::UserRole);
    seminarModel->appendRow(item);

    // Очищаем поле ввода имени семинара
    ui->addSeminarLineEdit->clear();
    log(QString::fromStdString("Семинар успешно добавлен"));
}

void MainWindow::onChangeSeminarNameButtonClicked()
{
    // Получаем индекс выбранного элемента
    QModelIndex currentIndex = ui->seminarListView->currentIndex();

    // Проверяем, действительно ли пользователь выбрал семинар
    if (!currentIndex.isValid())
    {
        log(QString::fromStdString("Необходимо выбрать семинар"));
        return;
    }

    // Получаем данные о старом и новом семинаре
    QString oldSeminarName = currentIndex.data(Qt::UserRole).toString();
    QString newSeminarName = ui->changeSeminarLineEdit->text().trimmed();

    // Проверяем, что имя нового семинара не пустая строка
    if (newSeminarName.isEmpty())
    {
        log(QString::fromStdString("Имя семинара не может быть пустым"));
        return;
    }
    for (auto &seminar : seminars) {
        if (seminar.name == oldSeminarName)
        {
            seminar.name = newSeminarName;
            break;
        }
    }

    // Устанавливаем новый текст для объекта списка
    QStandardItem *item = seminarModel->itemFromIndex(currentIndex);
    if (item) {
        item->setText(newSeminarName);
    }

    log(QString::fromStdString("Имя семинара изменено"));
}

void MainWindow::onSeminarSelected(const QItemSelection &selected, const QItemSelection &deselected) {
    // Выходим из метода, если ничего не выбрано
    if (selected.indexes().isEmpty()) return;

    // Получаем индекс первого из выбранных элементов (исключительно косметическое, в данной задаче
    // мы не можем выбрать более одного семинара)
    QModelIndex currentIndex = selected.indexes().first();
    if (!currentIndex.isValid())
    {
        return;
    }

    // Получаем имя выбранного семинара и устанавливаем его в поле для редактирования
    QString seminarName = currentIndex.data(Qt::UserRole).toString();
    ui->changeSeminarLineEdit->setText(seminarName);

    // Ищем семинар в векторе
    auto it = std::find_if(seminars.begin(), seminars.end(),
                           [&seminarName](const Seminar& seminar) { return seminar.name == seminarName; });
    if (it == seminars.end())
    {
        log(QString::fromStdString("Семинар не найден"));
        return;
    }

    // Очищаем списки дат и студентов, а после заполняем их новыми данными
    studentsModel->clear();
    datesModel->clear();
    for (const auto& student : it->students) {
        QStandardItem *item = new QStandardItem(student.name);
        item->setData(student.name, Qt::UserRole);
        studentsModel->appendRow(item);
    }
    for (const QDate& date : it->dates) {
        QStandardItem *dateItem = new QStandardItem(date.toString("dd.MM.yyyy"));
        dateItem->setData(date, Qt::UserRole);
        datesModel->appendRow(dateItem);
    }
}

void MainWindow::onStudentSelected(const QItemSelection &selected, const QItemSelection &deselected)
{
    // Выходим если ничего не выбрано
    if (selected.indexes().isEmpty()) {
        ui->changeStudentLineEdit->clear(); // Очищаем поле при снятии выбора
        return;
    }

    // Получаем индекс выбранного студента
    QModelIndex studentIndex = selected.indexes().first();
    if (!studentIndex.isValid()) return;

    // Извлекаем имя студента из UserRole
    QString studentName = studentIndex.data(Qt::UserRole).toString();

    // Устанавливаем имя в поле редактирования
    ui->changeStudentLineEdit->setText(studentName);
}

void MainWindow::onChangeStudentNameButtonClicked()
{
    // Получаем индекс выбранного семинара и проверяем, выбран ли какой-то семинар
    QModelIndex seminarIndex = ui->seminarListView->currentIndex();
    if (!seminarIndex.isValid())
    {
        log(QString::fromStdString("Необходимо выбрать семинар"));
        return;
    }
    QString seminarName = seminarIndex.data(Qt::UserRole).toString();

    // Ищем семинар в списке
    auto seminarIt = std::find_if(seminars.begin(), seminars.end(),
                           [&seminarName](const Seminar& seminar) { return seminar.name == seminarName; });
    if (seminarIt == seminars.end())
    {
        log(QString::fromStdString("Семинар не найден"));
        return;
    }


    // Получаем индекс выбранного студента и проверяем, выбран ли какой-то студент
    QModelIndex studentIndex = ui->studentsListView->currentIndex();
    if (!studentIndex.isValid()) {
        log(QString::fromStdString("Необходимо выбрать студента"));
        return;
    }
    QString oldName = studentIndex.data(Qt::UserRole).toString();

    // Получаем новое имя из поля ввода
    QString newName = ui->changeStudentLineEdit->text().trimmed();
    if (newName.isEmpty()) {
        log(QString::fromStdString("Имя студента не может быть пустым"));
        return;
    }

    // Ищем студента в семинаре
    auto studentIt = std::find_if(seminarIt->students.begin(), seminarIt->students.end(),
                                  [&oldName](const Student& s) { return s.name == oldName; });
    if (studentIt == seminarIt->students.end()) {
        log(QString::fromStdString("Студент не найден"));
        return;
    }

    // Изменяем имя студента и отлавливаем исключения
    try
    {
        studentIt->changeName(newName, seminarIt->students);
    }
    catch (const std::invalid_argument& e)
    {
        log(QString::fromStdString(e.what()));
        return;
    }

    // Обновляем элемент в модели
    QStandardItem* item = studentsModel->item(studentIndex.row());
    item->setText(newName);
    item->setData(newName, Qt::UserRole); // Обновляем UserRole
    log(QString::fromStdString("Имя студента изменено"));
}

void MainWindow::onDeleteSeminarButtonClicked()
{
    // Получаем индекс выбранного семинара и проверяем выбран ли какой-то семинар
    QModelIndex currentIndex = ui->seminarListView->currentIndex();
    if (!currentIndex.isValid())
    {
        log(QString::fromStdString("Необходимо выбрать семинар"));
        return;
    }
    QString seminarName = currentIndex.data(Qt::UserRole).toString();

    // Создаем окно с подтверждением удаления семинара
    QMessageBox confirmBox;
    confirmBox.setWindowTitle("Удаление семинара");
    confirmBox.setText("Вы действительно хотите удалить семинар \"" + seminarName + "\"?");
    confirmBox.setIcon(QMessageBox::Question);
    QPushButton *yesButton = confirmBox.addButton("Удалить", QMessageBox::YesRole);
    QPushButton *noButton = confirmBox.addButton("Отмена", QMessageBox::NoRole);

    // Выводим окно на экран
    confirmBox.exec();

    // Если выбрали "Отмена", то выходим из метода
    if (confirmBox.clickedButton() == noButton) return;

    // Удаляем семинар из вектора, если выбрано "Удалить"
    seminars.erase(std::remove_if(seminars.begin(), seminars.end(), [&seminarName](const Seminar& seminar)
                                  {return seminar.name == seminarName;}), seminars.end());

    // Удаляем семинар из списка
    seminarModel->removeRow(currentIndex.row());

    // Очищаем списки студентов и дат
    studentsModel->clear();
    datesModel->clear();

    // Сбрасываем selection, чтобы избежать ошибок
    ui->seminarListView->selectionModel()->clearSelection();
    log(QString::fromStdString("Семинар успешно удален"));
}

void MainWindow::onAddDateButtonClicked()
{
    // Получаем индекс и проверяем выбран ли какой-то семинар
    QModelIndex currentSeminarIndex = ui->seminarListView->currentIndex();
    if (!currentSeminarIndex.isValid())
    {
        log(QString::fromStdString("Необходимо выбрать семинар"));
        return;
    }
    QString seminarName = currentSeminarIndex.data(Qt::UserRole).toString();

    // Ищем семинар в списке
    auto it = std::find_if(seminars.begin(), seminars.end(),
                           [&seminarName](const Seminar& seminar) { return seminar.name == seminarName; });
    if (it == seminars.end())
    {
        log(QString::fromStdString("Семинар не найден"));
        return;
    }

    // Получаем дату из поля ввода
    QDate currentDate = ui->addDateEdit->date();

    // Добавляем дату в seminar и отлавливаем исключения
    try
    {
        it->addDate(currentDate);
    }
    catch (const std::invalid_argument& e)
    {
        log(e.what()); return;
    }

    // Добавляем новую дату в список
    QStandardItem *dateItem = new QStandardItem(currentDate.toString("dd.MM.yyyy"));
    dateItem->setData(currentDate, Qt::UserRole);
    datesModel->appendRow(dateItem);
    log(QString::fromStdString("Дата успешно добавлена"));
}

void MainWindow::onDeleteDateButtonClicked()
{
    // Получаем текущий идекс семинара и проверяем, выбран ли какой-то семинар
    QModelIndex currentSeminarIndex = ui->seminarListView->currentIndex();
    if (!currentSeminarIndex.isValid()) {
        log(QString::fromStdString("Необходимо выбрать семинар"));
        return;
    }
    QString seminarName = currentSeminarIndex.data(Qt::UserRole).toString();

    // Ищем семинар в списке семинаров
    auto it = std::find_if(seminars.begin(), seminars.end(),
                           [&seminarName](const Seminar& seminar) { return seminar.name == seminarName; });
    if (it == seminars.end())
    {
        log(QString::fromStdString("Семинар не найден"));
        return;
    }

    // Получаем текущий иднекс даты и проверяем, выбрана ли какая-то дата
    QModelIndex currentDateIndex = ui->datesListView->currentIndex();
    if (!currentDateIndex.isValid()) {
        log(QString::fromStdString("Необходимо выбрать дату для удаления"));
        return;
    }
    QDate selectedDate = currentDateIndex.data(Qt::UserRole).toDate();

    // Удаляем дату и отлавливаем исключения. В данном случае они не выбрасываются, однако
    // такая логика полезна для масштабирования (его не будет, мы сдадим это и забудем)
    try
    {
        it->deleteDate(selectedDate);
    }
    catch (const std::exception &e)
    {
        log(QString::fromStdString(e.what()));
        return;
    }

    // Удаляем строку с датой
    datesModel->removeRow(currentDateIndex.row());
    log(QString::fromStdString("Дата успешно удалена"));
}

void MainWindow::onEditDateButtonClicked()
{
    // Получаем индекс семинара и проверяем, выбрал ли какой-то семинар
    QModelIndex currentSeminarIndex = ui->seminarListView->currentIndex();
    if (!currentSeminarIndex.isValid()) {
        log(QString::fromStdString("Необходимо выбрать семинар"));
        return;
    }
    QString seminarName = currentSeminarIndex.data(Qt::UserRole).toString();

    // Ищем семинар в списки семинаров
    auto it = std::find_if(seminars.begin(), seminars.end(),
                           [&seminarName](const Seminar& seminar) { return seminar.name == seminarName; });
    if (it == seminars.end())
    {
        log(QString::fromStdString("Семинар не найден"));
        return;
    }

    // Получаем индекс даты и проверям, выбрана ли какая-то дата
    QModelIndex currentDateIndex = ui->datesListView->currentIndex();
    if (!currentDateIndex.isValid())
    {
        log(QString::fromStdString("Необходимо выбрать дату для изменения"));
        return;
    }
    QDate oldDate = currentDateIndex.data(Qt::UserRole).toDate();

    // Получаем новую дату и изменяем старую, отлавливая исключения
    QDate newDate = ui->editDateEdit->date();
    try
    {
        it->editDate(oldDate, newDate);
    }
    catch (const std::invalid_argument& e)
    {
        log(QString::fromStdString(e.what()));
        return;
    }

    // Обновляем элемент списка
    QStandardItem *item = datesModel->itemFromIndex(currentDateIndex);
    item->setData(newDate, Qt::UserRole);
    item->setText(newDate.toString("dd.MM.yyyy"));
    log(QString::fromStdString("Дата успешно изменена"));
}

void MainWindow::onAddStudentButtonClicked()
{
    // Получаем индекс семинара и проверяем, выбран ли какой-то семинар
    QModelIndex currentSeminarIndex = ui->seminarListView->currentIndex();
    if (!currentSeminarIndex.isValid()) {
        log(QString::fromStdString("Необходимо выбрать семинар"));
        return;
    }
    QString seminarName = currentSeminarIndex.data(Qt::UserRole).toString();

    // Ищем семинар в списке семинаров
    auto it = std::find_if(seminars.begin(), seminars.end(),
                           [&seminarName](const Seminar& seminar) { return seminar.name == seminarName; });
    if (it == seminars.end()) {
        log(QString::fromStdString("Семинар не найден"));
        return;
    }

    // Получаем имя студента и проверяем не пусто ли оно
    QString studentName = ui->addStudentLineEdit->text().trimmed();
    if (studentName.isEmpty()) {
        log(QString::fromStdString("Имя студента не может быть пустым"));
        return;
    }

    // Добавляем студента в вектор студентов и отлавливаем ошибки
    try
    {
    it->addStudent(studentName);
    }
    catch (const std::invalid_argument& e)
    {
        log(QString::fromStdString(e.what()));
        return;
    }

    // Добавляем студента в список
    QStandardItem *studentItem = new QStandardItem(studentName);
    studentItem->setData(studentName, Qt::UserRole);
    studentsModel->appendRow(studentItem);

    // Очищаем поле ввода имени
    ui->addStudentLineEdit->clear();
    log(QString::fromStdString("Студент успешно добавлен"));
}

void MainWindow::onDeleteStudentButtonClicked()
{
    // Проверяем, выбран ли семинар
    QModelIndex seminarIndex = ui->seminarListView->currentIndex();
    if (!seminarIndex.isValid()) {
        log(QString::fromStdString("Необходимо выбрать семинар"));
        return;
    }
    QString seminarName = seminarIndex.data(Qt::UserRole).toString();

    // Ищем семинар в векторе
    auto seminarIt = std::find_if(seminars.begin(), seminars.end(),
                                  [&seminarName](const Seminar& seminar) { return seminar.name == seminarName; });
    if (seminarIt == seminars.end()) {
        log(QString::fromStdString("Семинар не найден"));
        return;
    }

    // Проверяем, выбран ли студент
    QModelIndex studentIndex = ui->studentsListView->currentIndex();
    if (!studentIndex.isValid()) {
        log(QString::fromStdString("Необходимо выбрать студента"));
        return;
    }
    QString studentName = studentIndex.data(Qt::UserRole).toString();

    // Подтверждение удаления
    QMessageBox confirmBox;
    confirmBox.setWindowTitle("Удаление студента");
    confirmBox.setText("Вы действительно хотите удалить студента \"" + studentName + "\"?");
    confirmBox.setIcon(QMessageBox::Question);
    QPushButton* yesButton = confirmBox.addButton("Удалить", QMessageBox::YesRole);
    QPushButton* noButton = confirmBox.addButton("Отмена", QMessageBox::NoRole);
    confirmBox.exec();

    if (confirmBox.clickedButton() == noButton) return;

    // Удаляем студента из данных
    seminarIt->deleteStudent(studentName);

    // Удаляем студента из модели
    studentsModel->removeRow(studentIndex.row());

    // Очищаем поле редактирования
    ui->changeStudentLineEdit->clear();

    log(QString::fromStdString("Студент успешно удалён"));
}
