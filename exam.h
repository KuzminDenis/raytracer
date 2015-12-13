#ifndef EXAM_H
#define EXAM_H

#include <QDialog>

namespace Ui {
class exam;
}

class exam : public QDialog
{
    Q_OBJECT

public:
    explicit exam(QWidget *parent = 0);
    ~exam();

private:
    Ui::exam *ui;
};

#endif // EXAM_H
