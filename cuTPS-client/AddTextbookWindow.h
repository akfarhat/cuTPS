// Traceability:
//   An window extension on the ManageContentListWindow class.
//   provides a GUI dialog for inputting values for a new textbook.

#ifndef ADDTEXTBOOKWINDOW_H
#define ADDTEXTBOOKWINDOW_H

#include <QDialog>

#include "Entity/Textbook.h"

namespace Ui {
class AddTextbookWindow;
}

class AddTextbookWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddTextbookWindow(QWidget *parent = 0, int bookId = -1);
    ~AddTextbookWindow();

    void populateValues(Textbook *);

signals:
    void addTextbook(QString, int, int, bool, QString);

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddTextbookWindow *ui;
    int bookId; // in case of modify
};

#endif // ADDTEXTBOOKWINDOW_H
