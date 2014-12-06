// Traceability:
//   An extension on the CourseDetailsWindow class
//   in the CourseManagement subsystem

#ifndef ADDCHAPTERWINDOW_H
#define ADDCHAPTERWINDOW_H

#include <QDialog>

namespace Ui {
class AddChapterWindow;
}

class AddChapterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddChapterWindow(QWidget *parent = 0,
                              int bookID = -1);
    ~AddChapterWindow();

signals:
    void addChapter(QString, int, bool, int);

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddChapterWindow *ui;
    int bookId;
};

#endif // ADDCHAPTERWINDOW_H
