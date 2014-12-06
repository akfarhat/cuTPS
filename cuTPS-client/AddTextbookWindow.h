// Traceability:
//   An window extension on the ManageContentListWindow class.
//   provides a GUI dialog for inputting values for a new textbook.

#ifndef ADDTEXTBOOKWINDOW_H
#define ADDTEXTBOOKWINDOW_H

#include <QDialog>

namespace Ui {
class AddTextbookWindow;
}

class AddTextbookWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddTextbookWindow(QWidget *parent = 0);
    ~AddTextbookWindow();

signals:
    void addTextbook(QString, int, bool, QString);
private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddTextbookWindow *ui;
};

#endif // ADDTEXTBOOKWINDOW_H
