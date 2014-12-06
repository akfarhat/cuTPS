#ifndef ADDSECTIONWINDOW_H
#define ADDSECTIONWINDOW_H

#include <QDialog>

namespace Ui {
class AddSectionWindow;
}

class AddSectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddSectionWindow(QWidget *parent = 0, int chapId = -1);
    ~AddSectionWindow();

signals:
    void addSection(QString, int, bool, int);

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddSectionWindow *ui;
    int chapterId;
};

#endif // ADDSECTIONWINDOW_H
