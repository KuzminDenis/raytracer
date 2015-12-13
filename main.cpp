#include "mainwindow.h"
#include <QApplication>
#include <qpushbutton.h>
#include <qapplication.h>
#include "qlabel.h"
#include "dialog.h"
#include "ui_mydialog.h"
#include <mydialog.h>
#include <QColorDialog>

#include <stdio.h>
#include <stdlib.h>

#include "lib/glm/glm/glm.hpp"

#include "types.h"

#include "renderer.h"
#include "world.h"
#include "camera.h"
#include "tracer.h"

#include <omp.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyDialog * win = new MyDialog();
    win->show();

    return a.exec();
}
