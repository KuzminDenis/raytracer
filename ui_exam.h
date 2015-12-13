/********************************************************************************
** Form generated from reading UI file 'exam.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAM_H
#define UI_EXAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_exam
{
public:

    void setupUi(QDialog *exam)
    {
        if (exam->objectName().isEmpty())
            exam->setObjectName(QStringLiteral("exam"));
        exam->resize(400, 300);

        retranslateUi(exam);

        QMetaObject::connectSlotsByName(exam);
    } // setupUi

    void retranslateUi(QDialog *exam)
    {
        exam->setWindowTitle(QApplication::translate("exam", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class exam: public Ui_exam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAM_H
