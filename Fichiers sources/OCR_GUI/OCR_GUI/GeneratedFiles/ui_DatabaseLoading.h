/********************************************************************************
** Form generated from reading UI file 'DatabaseLoading.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASELOADING_H
#define UI_DATABASELOADING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DatabaseLoading
{
public:
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QWidget *DatabaseLoading)
    {
        if (DatabaseLoading->objectName().isEmpty())
            DatabaseLoading->setObjectName(QString::fromUtf8("DatabaseLoading"));
        DatabaseLoading->resize(396, 142);
        label = new QLabel(DatabaseLoading);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 30, 181, 21));
        progressBar = new QProgressBar(DatabaseLoading);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 80, 371, 21));
        progressBar->setValue(0);

        retranslateUi(DatabaseLoading);

        QMetaObject::connectSlotsByName(DatabaseLoading);
    } // setupUi

    void retranslateUi(QWidget *DatabaseLoading)
    {
        DatabaseLoading->setWindowTitle(QApplication::translate("DatabaseLoading", "DatabaseLoading", nullptr));
        label->setText(QApplication::translate("DatabaseLoading", "Chargement de la base de donn\303\251es...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DatabaseLoading: public Ui_DatabaseLoading {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASELOADING_H
