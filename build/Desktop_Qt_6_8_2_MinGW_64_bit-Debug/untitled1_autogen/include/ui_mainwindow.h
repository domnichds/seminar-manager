/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *addDateButton;
    QPushButton *deleteSeminarButton;
    QPushButton *addStudentButton;
    QPushButton *deleteDateButton;
    QPushButton *deleteStudentButton;
    QLabel *seminarManagerTextLabel;
    QDateEdit *addDateEdit;
    QLineEdit *addStudentLineEdit;
    QPushButton *addSeminarButton;
    QLineEdit *changeSeminarLineEdit;
    QGraphicsView *logoGraphicView;
    QPushButton *changeStudentButton;
    QDateEdit *changeDateEdit;
    QLabel *studentManagerLabel;
    QLineEdit *addSeminarLineEdit;
    QPushButton *changeDateButton;
    QLineEdit *changeStudentLineEdit;
    QPushButton *changeSeminarButton;
    QPushButton *goToTableButton;
    QLabel *systemMesssgeLable;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QListView *seminarListView;
    QListView *studentsListView;
    QListView *datesListView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1400, 800);
        QIcon icon;
        icon.addFile(QString::fromUtf8("build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-image: url(background.png);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 0, 470, 811));
        gridLayoutWidget->setMinimumSize(QSize(0, 41));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(10);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        gridLayout->setContentsMargins(10, 10, 10, 10);
        addDateButton = new QPushButton(gridLayoutWidget);
        addDateButton->setObjectName("addDateButton");
        addDateButton->setEnabled(true);
        addDateButton->setMinimumSize(QSize(0, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("ALS Sector Regular")});
        font.setBold(true);
        addDateButton->setFont(font);
        addDateButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(addDateButton, 8, 1, 1, 1);

        deleteSeminarButton = new QPushButton(gridLayoutWidget);
        deleteSeminarButton->setObjectName("deleteSeminarButton");
        deleteSeminarButton->setEnabled(true);
        deleteSeminarButton->setMinimumSize(QSize(450, 41));
        deleteSeminarButton->setFont(font);
        deleteSeminarButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(deleteSeminarButton, 7, 1, 1, 2);

        addStudentButton = new QPushButton(gridLayoutWidget);
        addStudentButton->setObjectName("addStudentButton");
        addStudentButton->setEnabled(true);
        addStudentButton->setMinimumSize(QSize(0, 41));
        addStudentButton->setFont(font);
        addStudentButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(addStudentButton, 13, 1, 1, 1);

        deleteDateButton = new QPushButton(gridLayoutWidget);
        deleteDateButton->setObjectName("deleteDateButton");
        deleteDateButton->setEnabled(true);
        deleteDateButton->setMinimumSize(QSize(0, 41));
        deleteDateButton->setFont(font);
        deleteDateButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(deleteDateButton, 10, 1, 1, 2);

        deleteStudentButton = new QPushButton(gridLayoutWidget);
        deleteStudentButton->setObjectName("deleteStudentButton");
        deleteStudentButton->setEnabled(true);
        deleteStudentButton->setMinimumSize(QSize(0, 41));
        deleteStudentButton->setFont(font);
        deleteStudentButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(deleteStudentButton, 17, 1, 1, 2);

        seminarManagerTextLabel = new QLabel(gridLayoutWidget);
        seminarManagerTextLabel->setObjectName("seminarManagerTextLabel");
        seminarManagerTextLabel->setEnabled(true);
        seminarManagerTextLabel->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("ALS Sector Bold")});
        font1.setPointSize(18);
        font1.setBold(true);
        seminarManagerTextLabel->setFont(font1);
        seminarManagerTextLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: white;\n"
"}\n"
""));

        gridLayout->addWidget(seminarManagerTextLabel, 2, 1, 1, 2);

        addDateEdit = new QDateEdit(gridLayoutWidget);
        addDateEdit->setObjectName("addDateEdit");
        addDateEdit->setMinimumSize(QSize(0, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("ALS Sector Regular")});
        font2.setPointSize(12);
        font2.setBold(false);
        addDateEdit->setFont(font2);
        addDateEdit->setMouseTracking(false);
        addDateEdit->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"    background: transparent;\n"
"    border: 1px solid rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border-radius: 8px;\n"
"}\n"
"QDateEdit:hover {\n"
"    border: 1px solid rgba(112, 69, 211, 0.8);\n"
"    background-color: rgba(112, 69, 211, 0.2);\n"
"}\n"
"QDateEdit:focus {\n"
"    border: 1px solid rgba(65, 32, 138, 0.9);\n"
"    background-color: rgba(65, 32, 138, 0.3);\n"
"}\n"
"QDateEdit::down-arrow {\n"
"    width: 0px;\n"
"    height: 0px;\n"
"    border: none;\n"
"    background: transparent;\n"
"    opacity: 0;\n"
"}\n"
"QDateEdit::up-arrow {\n"
"    width: 0px;\n"
"    height: 0px;\n"
"    border: none;\n"
"    background: transparent;\n"
"    opacity: 0;\n"
"}\n"
"\n"
""));
        addDateEdit->setWrapping(false);
        addDateEdit->setFrame(true);
        addDateEdit->setDate(QDate(2025, 2, 1));

        gridLayout->addWidget(addDateEdit, 8, 2, 1, 1);

        addStudentLineEdit = new QLineEdit(gridLayoutWidget);
        addStudentLineEdit->setObjectName("addStudentLineEdit");
        addStudentLineEdit->setMinimumSize(QSize(0, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("ALS Sector Regular")});
        font3.setBold(false);
        addStudentLineEdit->setFont(font3);
        addStudentLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: rgba(65, 32, 138, 0.2);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: normal;\n"
"}\n"
"QLineEdit:hover {\n"
"    background-color: rgba(112, 69, 211, 0.3);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QLineEdit:focus {\n"
"    background-color: rgba(112, 69, 211, 0.4);\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"    outline: none;\n"
"}\n"
"QLineEdit:!empty {\n"
"    background-color: rgba(112, 69, 211, 0.1);\n"
"}"));

        gridLayout->addWidget(addStudentLineEdit, 13, 2, 1, 1);

        addSeminarButton = new QPushButton(gridLayoutWidget);
        addSeminarButton->setObjectName("addSeminarButton");
        addSeminarButton->setEnabled(true);
        addSeminarButton->setMinimumSize(QSize(0, 41));
        addSeminarButton->setFont(font);
        addSeminarButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(addSeminarButton, 4, 1, 1, 1);

        changeSeminarLineEdit = new QLineEdit(gridLayoutWidget);
        changeSeminarLineEdit->setObjectName("changeSeminarLineEdit");
        changeSeminarLineEdit->setMinimumSize(QSize(0, 41));
        changeSeminarLineEdit->setFont(font3);
        changeSeminarLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: rgba(65, 32, 138, 0.2);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: normal;\n"
"}\n"
"QLineEdit:hover {\n"
"    background-color: rgba(112, 69, 211, 0.3);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QLineEdit:focus {\n"
"    background-color: rgba(112, 69, 211, 0.4);\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"    outline: none;\n"
"}\n"
"QLineEdit:!empty {\n"
"    background-color: rgba(112, 69, 211, 0.1);\n"
"}"));

        gridLayout->addWidget(changeSeminarLineEdit, 6, 2, 1, 1);

        logoGraphicView = new QGraphicsView(gridLayoutWidget);
        logoGraphicView->setObjectName("logoGraphicView");
        logoGraphicView->setMinimumSize(QSize(450, 150));
        logoGraphicView->setMaximumSize(QSize(450, 150));

        gridLayout->addWidget(logoGraphicView, 1, 1, 1, 2);

        changeStudentButton = new QPushButton(gridLayoutWidget);
        changeStudentButton->setObjectName("changeStudentButton");
        changeStudentButton->setEnabled(true);
        changeStudentButton->setMinimumSize(QSize(0, 41));
        changeStudentButton->setFont(font);
        changeStudentButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(changeStudentButton, 16, 1, 1, 1);

        changeDateEdit = new QDateEdit(gridLayoutWidget);
        changeDateEdit->setObjectName("changeDateEdit");
        changeDateEdit->setMinimumSize(QSize(0, 41));
        changeDateEdit->setFont(font2);
        changeDateEdit->setMouseTracking(false);
        changeDateEdit->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"    background: transparent;\n"
"    border: 1px solid rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border-radius: 8px;\n"
"}\n"
"QDateEdit:hover {\n"
"    border: 1px solid rgba(112, 69, 211, 0.8);\n"
"    background-color: rgba(112, 69, 211, 0.2);\n"
"}\n"
"QDateEdit:focus {\n"
"    border: 1px solid rgba(65, 32, 138, 0.9);\n"
"    background-color: rgba(65, 32, 138, 0.3);\n"
"}\n"
"QDateEdit::down-arrow {\n"
"    width: 0px;\n"
"    height: 0px;\n"
"    border: none;\n"
"    background: transparent;\n"
"    opacity: 0;\n"
"}\n"
"QDateEdit::up-arrow {\n"
"    width: 0px;\n"
"    height: 0px;\n"
"    border: none;\n"
"    background: transparent;\n"
"    opacity: 0;\n"
"}"));
        changeDateEdit->setWrapping(false);
        changeDateEdit->setFrame(true);
        changeDateEdit->setDate(QDate(2025, 2, 1));

        gridLayout->addWidget(changeDateEdit, 9, 2, 1, 1);

        studentManagerLabel = new QLabel(gridLayoutWidget);
        studentManagerLabel->setObjectName("studentManagerLabel");
        studentManagerLabel->setMaximumSize(QSize(16777215, 30));
        studentManagerLabel->setFont(font1);
        studentManagerLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: white;\n"
"}\n"
""));

        gridLayout->addWidget(studentManagerLabel, 12, 1, 1, 2);

        addSeminarLineEdit = new QLineEdit(gridLayoutWidget);
        addSeminarLineEdit->setObjectName("addSeminarLineEdit");
        addSeminarLineEdit->setMinimumSize(QSize(0, 41));
        addSeminarLineEdit->setFont(font3);
        addSeminarLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: rgba(65, 32, 138, 0.2);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: normal;\n"
"}\n"
"QLineEdit:hover {\n"
"    background-color: rgba(112, 69, 211, 0.3);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QLineEdit:focus {\n"
"    background-color: rgba(112, 69, 211, 0.4);\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"    outline: none;\n"
"}\n"
"QLineEdit:!empty {\n"
"    background-color: rgba(112, 69, 211, 0.1);\n"
"}"));

        gridLayout->addWidget(addSeminarLineEdit, 4, 2, 1, 1);

        changeDateButton = new QPushButton(gridLayoutWidget);
        changeDateButton->setObjectName("changeDateButton");
        changeDateButton->setEnabled(true);
        changeDateButton->setMinimumSize(QSize(0, 41));
        changeDateButton->setFont(font);
        changeDateButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(changeDateButton, 9, 1, 1, 1);

        changeStudentLineEdit = new QLineEdit(gridLayoutWidget);
        changeStudentLineEdit->setObjectName("changeStudentLineEdit");
        changeStudentLineEdit->setMinimumSize(QSize(0, 41));
        changeStudentLineEdit->setFont(font3);
        changeStudentLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: rgba(65, 32, 138, 0.2);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: normal;\n"
"}\n"
"QLineEdit:hover {\n"
"    background-color: rgba(112, 69, 211, 0.3);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QLineEdit:focus {\n"
"    background-color: rgba(112, 69, 211, 0.4);\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"    outline: none;\n"
"}\n"
"QLineEdit:!empty {\n"
"    background-color: rgba(112, 69, 211, 0.1);\n"
"}"));

        gridLayout->addWidget(changeStudentLineEdit, 16, 2, 1, 1);

        changeSeminarButton = new QPushButton(gridLayoutWidget);
        changeSeminarButton->setObjectName("changeSeminarButton");
        changeSeminarButton->setEnabled(true);
        changeSeminarButton->setMinimumSize(QSize(0, 41));
        changeSeminarButton->setFont(font);
        changeSeminarButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(changeSeminarButton, 6, 1, 1, 1);

        goToTableButton = new QPushButton(gridLayoutWidget);
        goToTableButton->setObjectName("goToTableButton");
        goToTableButton->setEnabled(true);
        goToTableButton->setMinimumSize(QSize(0, 41));
        goToTableButton->setFont(font);
        goToTableButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}"));

        gridLayout->addWidget(goToTableButton, 18, 1, 1, 2);

        systemMesssgeLable = new QLabel(gridLayoutWidget);
        systemMesssgeLable->setObjectName("systemMesssgeLable");
        systemMesssgeLable->setMaximumSize(QSize(16777215, 30));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("ALS Sector Bold")});
        font4.setPointSize(12);
        font4.setBold(true);
        systemMesssgeLable->setFont(font4);
        systemMesssgeLable->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: white;\n"
"}\n"
""));

        gridLayout->addWidget(systemMesssgeLable, 19, 1, 1, 2);

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(470, 0, 931, 780));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(5, 10, 5, 10);
        seminarListView = new QListView(horizontalLayoutWidget);
        seminarListView->setObjectName("seminarListView");
        seminarListView->setMinimumSize(QSize(450, 760));
        seminarListView->setMaximumSize(QSize(450, 760));
        seminarListView->setFont(font2);
        seminarListView->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        seminarListView->setAutoFillBackground(false);
        seminarListView->setStyleSheet(QString::fromUtf8("QListView {\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"QListView::viewport {\n"
"    background: transparent;\n"
"}\n"
"QListView::item {\n"
"    background-color: transparent;\n"
"    border: 1px solid transparent;\n"
"    padding: 5px;\n"
"}\n"
"QListView::item:hover {\n"
"    background-color: rgba(112, 69, 211, 0.2);\n"
"    border: 1px solid rgba(112, 69, 211, 0.5);\n"
"    border-radius: 8px;\n"
"}\n"
"QListView::item:pressed {\n"
"    background-color: rgba(65, 32, 138, 0.4);\n"
"    border: 1px solid rgba(65, 32, 138, 0.6);\n"
"    border-radius: 8px;\n"
"}\n"
"QListView::item:selected {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    border: 1px solid rgba(65, 32, 138, 0.9);\n"
"    border-radius: 8px;\n"
"    outline: none;\n"
"}"));
        seminarListView->setFrameShape(QFrame::Shape::NoFrame);
        seminarListView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);

        horizontalLayout->addWidget(seminarListView);

        studentsListView = new QListView(horizontalLayoutWidget);
        studentsListView->setObjectName("studentsListView");
        studentsListView->setMinimumSize(QSize(300, 760));
        studentsListView->setMaximumSize(QSize(300, 760));
        studentsListView->setFont(font2);
        studentsListView->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        studentsListView->setAutoFillBackground(false);
        studentsListView->setStyleSheet(QString::fromUtf8("QListView {\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"QListView::viewport {\n"
"    background: transparent;\n"
"}\n"
"QListView::item {\n"
"    background-color: transparent;\n"
"    border: 1px solid transparent;\n"
"    padding: 5px;\n"
"}\n"
"QListView::item:hover {\n"
"    background-color: rgba(112, 69, 211, 0.2);\n"
"    border: 1px solid rgba(112, 69, 211, 0.5);\n"
"    border-radius: 8px;\n"
"}\n"
"QListView::item:pressed {\n"
"    background-color: rgba(65, 32, 138, 0.4);\n"
"    border: 1px solid rgba(65, 32, 138, 0.6);\n"
"    border-radius: 8px;\n"
"}\n"
"QListView::item:selected {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    border: 1px solid rgba(65, 32, 138, 0.9);\n"
"    border-radius: 8px;\n"
"    outline: none;\n"
"}"));
        studentsListView->setFrameShape(QFrame::Shape::NoFrame);
        studentsListView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);

        horizontalLayout->addWidget(studentsListView);

        datesListView = new QListView(horizontalLayoutWidget);
        datesListView->setObjectName("datesListView");
        datesListView->setMinimumSize(QSize(130, 760));
        datesListView->setMaximumSize(QSize(130, 760));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("ALS Sector Regular")});
        font5.setPointSize(12);
        datesListView->setFont(font5);
        datesListView->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        datesListView->setStyleSheet(QString::fromUtf8("QListView {\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"QListView::viewport {\n"
"    background: transparent;\n"
"}\n"
"QListView::item {\n"
"    background-color: transparent;\n"
"    border: 1px solid transparent;\n"
"    padding: 5px;\n"
"}\n"
"QListView::item:hover {\n"
"    background-color: rgba(112, 69, 211, 0.2);\n"
"    border: 1px solid rgba(112, 69, 211, 0.5);\n"
"    border-radius: 8px;\n"
"}\n"
"QListView::item:pressed {\n"
"    background-color: rgba(65, 32, 138, 0.4);\n"
"    border: 1px solid rgba(65, 32, 138, 0.6);\n"
"    border-radius: 8px;\n"
"}\n"
"QListView::item:selected {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    border: 1px solid rgba(65, 32, 138, 0.9);\n"
"    border-radius: 8px;\n"
"    outline: none;\n"
"}"));
        datesListView->setFrameShape(QFrame::Shape::NoFrame);

        horizontalLayout->addWidget(datesListView);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addDateButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        deleteSeminarButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\320\265\320\274\320\270\320\275\320\260\321\200", nullptr));
        addStudentButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\260", nullptr));
        deleteDateButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        deleteStudentButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\260", nullptr));
        seminarManagerTextLabel->setText(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\320\265\320\274\320\270\320\275\320\260\321\200\320\260\320\274\320\270", nullptr));
        addSeminarButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\320\265\320\274\320\270\320\275\320\260\321\200", nullptr));
        changeStudentButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\274\321\217", nullptr));
        studentManagerLabel->setText(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\260\320\274\320\270", nullptr));
        changeDateButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        changeSeminarButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        goToTableButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270 \320\272 \320\266\321\203\321\200\320\275\320\260\320\273\321\203", nullptr));
        systemMesssgeLable->setText(QCoreApplication::translate("MainWindow", "\320\241\320\270\321\201\321\202\320\265\320\274\320\275\320\276\320\265 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265 (\320\276\321\210\320\270\320\261\320\272\320\270)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
