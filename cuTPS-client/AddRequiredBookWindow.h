// Traceability:
//   An extension on the CourseDetailsWindow in the ManageCourses
//   subsystem. Provides a dialog to allow selected textbooks to
//   be added as required for the selected course.

#ifndef ADDREQUIREDBOOKWINDOW_H
#define ADDREQUIREDBOOKWINDOW_H

#include <QDialog>
#include <QVector>
#include <QList>

#include "Entity/Textbook.h"
#include "CourseRequestAPI.h"

namespace Ui {
class AddRequiredBookWindow;
}

class AddRequiredBookWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddRequiredBookWindow(QWidget *parent = 0,
                                   CourseRequestAPI * = NULL,
                                   int courseId = -1);
    ~AddRequiredBookWindow();

    void populateBooks(QList<Textbook*>*);

signals:
    void addRequiredBooks(QVector<int> &, int);

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddRequiredBookWindow *ui;
    QList<Textbook*> *books;
    CourseRequestAPI *courseRequests;
    int courseID;
};

#endif // ADDREQUIREDBOOKWINDOW_H
