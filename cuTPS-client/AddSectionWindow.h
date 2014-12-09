// Traceability:
//   An extention on the ManageableContentListWindow
//   class in the ContentManagement subsystem.
//   Provides a dialog to add section details to a chapter

#ifndef ADDSECTIONWINDOW_H
#define ADDSECTIONWINDOW_H

#include <QDialog>

#include "Entity/Section.h"

namespace Ui {
class AddSectionWindow;
}

class AddSectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddSectionWindow(QWidget *parent = 0,
                              int textId = -1,
                              int chapId = -1,
                              int sectId = -1);
    ~AddSectionWindow();

    void populateValues(Section *);

signals:
    void addSection(QString, int, int, bool, int, int);

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddSectionWindow *ui;
    int chapterId;
    int bookId;
    int secId; // in case of modify
};

#endif // ADDSECTIONWINDOW_H
