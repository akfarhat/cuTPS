// Traceability:
//   An extension on the CourseDetailsWindow class
//   in the CourseManagement subsystem

#ifndef ADDCHAPTERWINDOW_H
#define ADDCHAPTERWINDOW_H

#include <QDialog>

#include "Entity/Chapter.h"

namespace Ui {
class AddChapterWindow;
}

class AddChapterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddChapterWindow(QWidget *parent = 0,
                              int bookID = -1,
                              int chapId = -1);
    ~AddChapterWindow();

    void populateValues(Chapter *); // for modify

signals:
    void addChapter(QString, int, int, bool, int);

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddChapterWindow *ui;
    int bookId;
    int chapId; // in case of modify
};

#endif // ADDCHAPTERWINDOW_H
