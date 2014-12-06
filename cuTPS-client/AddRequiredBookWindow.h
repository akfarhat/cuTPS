#ifndef ADDREQUIREDBOOKWINDOW_H
#define ADDREQUIREDBOOKWINDOW_H

#include <QDialog>
#include <QVector>

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

signals:
    void addRequiredBooks(QVector<int> &, int);

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddRequiredBookWindow *ui;
    QVector<Textbook*> *books;
    CourseRequestAPI *courseRequests;
    void populateBooks();
    int courseID;
};

#endif // ADDREQUIREDBOOKWINDOW_H
