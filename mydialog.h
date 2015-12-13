#ifndef MYDIALOG_H
#define MYDIALOG_H
#include "mainwindow.h"
#include "world.h"
#include <QDialog>
#include <QColorDialog>
#include "lib/glm/glm/glm.hpp"
namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();

private slots:
    void on_rend_clicked();

    void on_pushButton_clicked();

private:
    glm::vec3 color;
    Ui::MyDialog *ui;
    MainWindow *mainialog;
    QColorDialog *colorDialog;
    QMainWindow *app;
    MainWindow *testwindow;
};

#endif // MYDIALOG_H
