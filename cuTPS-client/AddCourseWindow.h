#ifndef ADDCOURSEWINDOW_H
#define ADDCOURSEWINDOW_H

#include <QDialog>

namespace Ui {
class AddCourseWindow;
}

class AddCourseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddCourseWindow(QWidget *parent = 0);
    ~AddCourseWindow();

signals:
    void saveNewCourse(QString, QString);

private slots:
    void on_cancelButton_clicked();

    void on_saveCourseButton_clicked();

private:
    Ui::AddCourseWindow *ui;
};

#endif // ADDCOURSEWINDOW_H
