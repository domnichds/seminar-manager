/********************************************************************************
** Form generated from reading UI file 'secondwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDWINDOW_H
#define UI_SECONDWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SecondWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QListView *seminarListView;
    QTableView *attendanceTableView;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *putMarkButton;
    QComboBox *markSelectComboBox;
    QPushButton *saveChangesButton;
    QPushButton *goBackButton;

    void setupUi(QMainWindow *SecondWindow)
    {
        if (SecondWindow->objectName().isEmpty())
            SecondWindow->setObjectName("SecondWindow");
        SecondWindow->resize(1400, 800);
        QIcon icon;
        icon.addFile(QString::fromUtf8("build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        SecondWindow->setWindowIcon(icon);
        SecondWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-image: url(bg.png);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    background-origin: content;\n"
"}\n"
""));
        centralwidget = new QWidget(SecondWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(270, 0, 1131, 811));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, 20, 10, 10);
        seminarListView = new QListView(horizontalLayoutWidget);
        seminarListView->setObjectName("seminarListView");
        seminarListView->setMaximumSize(QSize(380, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("ALS Sector Regular")});
        font.setPointSize(12);
        seminarListView->setFont(font);
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
"\n"
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
"}\n"
"QListView::item:focus {\n"
"	outline: none;\n"
"}"));

        horizontalLayout->addWidget(seminarListView);

        attendanceTableView = new QTableView(horizontalLayoutWidget);
        attendanceTableView->setObjectName("attendanceTableView");
        attendanceTableView->setMinimumSize(QSize(800, 200));
        attendanceTableView->setMaximumSize(QSize(500, 780));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("ALS Sector Regular")});
        font1.setPointSize(12);
        font1.setBold(false);
        attendanceTableView->setFont(font1);
        attendanceTableView->setStyleSheet(QString::fromUtf8("QTableView {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    border: none;\n"
"    gridline-color: rgba(255, 255, 255, 0.2);\n"
"    selection-background-color: rgba(112, 69, 211, 0.8);\n"
"    selection-color: white;\n"
"    font-family: \"ALS Sector Regular\";\n"
"    font-size: 12pt;\n"
"    font-weight: normal;\n"
"}\n"
"QTableView::item:selected {\n"
"    border: none;\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"}\n"
"QTableView::item:hover {\n"
"    background-color: rgba(112, 69, 211, 0.6);\n"
"}\n"
"QTableView::item:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    border: 1px solid rgba(255, 255, 255, 0.5);\n"
"    font-size: 12pt;\n"
"    font-family: \"ALS Sector Regular\";\n"
"    padding: 5px;\n"
"}\n"
"QTableCornerButton::section {\n"
"    background-color: transparent;\n"
"    border: 1px solid rgba(255, 255, 255, 0.5);\n"
"}"));
        attendanceTableView->setCornerButtonEnabled(false);

        horizontalLayout->addWidget(attendanceTableView);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 0, 271, 241));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(10, 10, 10, 10);
        putMarkButton = new QPushButton(gridLayoutWidget);
        putMarkButton->setObjectName("putMarkButton");
        putMarkButton->setMinimumSize(QSize(0, 41));
        putMarkButton->setMaximumSize(QSize(16777215, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("ALS Sector Regular")});
        font2.setBold(true);
        putMarkButton->setFont(font2);
        putMarkButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        gridLayout->addWidget(putMarkButton, 0, 0, 1, 1);

        markSelectComboBox = new QComboBox(gridLayoutWidget);
        markSelectComboBox->setObjectName("markSelectComboBox");
        markSelectComboBox->setMinimumSize(QSize(0, 41));
        markSelectComboBox->setMaximumSize(QSize(16777215, 41));
        markSelectComboBox->setFont(font2);
        markSelectComboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    border-radius: 12px;\n"
"    padding: 5px 10px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QComboBox:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"QComboBox:focus {\n"
"    background-color: rgba(112, 69, 211, 0.9);\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"    outline: none;\n"
"}\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 30px;\n"
"    border-left: 1px solid rgba(65, 32, 138, 0.8);\n"
"}\n"
"QComboBox::down-arrow {\n"
"    width: 14px;\n"
"    height: 14px;\n"
"}"));

        gridLayout->addWidget(markSelectComboBox, 1, 0, 1, 1);

        saveChangesButton = new QPushButton(gridLayoutWidget);
        saveChangesButton->setObjectName("saveChangesButton");
        saveChangesButton->setMinimumSize(QSize(0, 41));
        saveChangesButton->setMaximumSize(QSize(16777215, 41));
        saveChangesButton->setFont(font2);
        saveChangesButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}\n"
""));

        gridLayout->addWidget(saveChangesButton, 2, 0, 1, 1);

        goBackButton = new QPushButton(gridLayoutWidget);
        goBackButton->setObjectName("goBackButton");
        goBackButton->setMinimumSize(QSize(0, 41));
        goBackButton->setMaximumSize(QSize(16777215, 41));
        goBackButton->setFont(font2);
        goBackButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(65, 32, 138, 0.6);\n"
"    color: white;\n"
"    border: 1px solid rgba(65, 32, 138, 0.8);\n"
"    padding: 10px 20px;\n"
"    border-radius: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(112, 69, 211, 0.8);\n"
"    border: 1px solid rgba(112, 69, 211, 1);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgba(65, 32, 138, 1);\n"
"    border: 1px solid rgba(65, 32, 138, 1);\n"
"}\n"
"\n"
"QPushButton:focus {\n"
"    outline: none;\n"
"    border: 2px solid rgba(112, 69, 211, 1);\n"
"}\n"
""));

        gridLayout->addWidget(goBackButton, 3, 0, 1, 1);

        SecondWindow->setCentralWidget(centralwidget);

        retranslateUi(SecondWindow);

        QMetaObject::connectSlotsByName(SecondWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SecondWindow)
    {
        SecondWindow->setWindowTitle(QCoreApplication::translate("SecondWindow", "MainWindow", nullptr));
        putMarkButton->setText(QCoreApplication::translate("SecondWindow", "\320\237\320\276\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\276\321\202\320\274\320\265\321\202\320\272\321\203", nullptr));
        saveChangesButton->setText(QCoreApplication::translate("SecondWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", nullptr));
        goBackButton->setText(QCoreApplication::translate("SecondWindow", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214\321\201\321\217 \320\272 \321\201\320\265\320\274\320\270\320\275\320\260\321\200\320\260\320\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecondWindow: public Ui_SecondWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDWINDOW_H
