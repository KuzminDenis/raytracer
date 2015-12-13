#include "exam.h"
#include "ui_exam.h"

exam::exam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exam)
{
    ui->setupUi(this);
}

exam::~exam()
{
    delete ui;
}
