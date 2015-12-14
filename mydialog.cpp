#include "mydialog.h"
#include "ui_mydialog.h"
#include "mainwindow.h"
#include <QApplication>
#include <qpushbutton.h>
#include <qapplication.h>
#include "qlabel.h"
#include "dialog.h"
#include "ui_mydialog.h"
#include <mydialog.h>
#include <QColorDialog>
#include <QDebug>
#include <qcolor.h>
#include <QtOpenGL/QGLWidget>
#include <QColor>
#include <QColormap>
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>

#include "lib/glm/glm/glm.hpp"
//#include "L3DS/src/lib3ds.h"

#include "types.h"

#include "renderer.h"
#include "world.h"
#include "camera.h"
#include "tracer.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    app=new MainWindow();
        testwindow=new MainWindow();
        ui->setupUi(this);
    color = glm::vec3(0, 0, 0);
    connect(ui->rend, SIGNAL(click()), this, SLOT(on_rend_clicked()));
    connect(ui->pushButton, SIGNAL(click()), this, SLOT(on_pushButton_clicked()));
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_rend_clicked()
{
    ui->label_7->setText("Rendering...Please wait");
    World world;
    int hei=ui->spinBox->value();
    int wid=ui->spinBox_2->value();
    int lev=ui->spinBox_3->value();
    int angle=ui->spinBox_4->value();
    std::string name=ui->lineEdit->text().toStdString();
    int a1=ui->textEdit->toPlainText().toInt();
    int a2=ui->textEdit_2->toPlainText().toInt();
    int a3=ui->textEdit_3->toPlainText().toInt();
    glm::vec3 camera_pos = glm::vec3(a1, a2, a3);
    a1=ui->textEdit_4->toPlainText().toInt();
    a2=ui->textEdit_5->toPlainText().toInt();
    a3=ui->textEdit_6->toPlainText().toInt();
    glm::vec3 camera_dir_for = glm::vec3(a1, a2, a3);
    a1=ui->textEdit_7->toPlainText().toInt();
    a2=ui->textEdit_8->toPlainText().toInt();
    a3=ui->textEdit_9->toPlainText().toInt();
    glm::vec3 camera_dir_upw = glm::vec3(a1, a2, a3);
    Render_settings settings=Render_settings(hei,wid,lev,(float)angle,name,color,camera_pos,camera_dir_for,camera_dir_upw);

    renderer = Renderer::Instance(settings);
    Tracer tracer(settings);
    Camera camera(settings);

    renderer->render_image(world, camera, tracer,ui);
    renderer->save_image(camera);
    ui->label_7->setText("Image successfully saved!");

    testwindow->show();
}

void MyDialog::on_pushButton_clicked()
{

       QColorDialog *colorDialog = new QColorDialog();
       colorDialog->setWindowFlags(Qt::Widget);
       colorDialog->setOptions(

                   QColorDialog::DontUseNativeDialog

                   | QColorDialog::NoButtons
       );

    QColor my_col =  colorDialog->getColor();
    color = glm::vec3(my_col.red(), my_col.green(), my_col.blue());
}
