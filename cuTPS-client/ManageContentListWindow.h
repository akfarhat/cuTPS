#ifndef MANAGECONTENTLISTWINDOW_H
#define MANAGECONTENTLISTWINDOW_H

#include <QMainWindow>

// Forward decleration to avoid circular dep
class ManageContentControl;

namespace Ui {
class ManageContentListWindow;
}

class ManageContentListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManageContentListWindow(QWidget *parent = 0,
                                     ManageContentControl *cmCtr = NULL);
    ~ManageContentListWindow();

signals:
    void navigateBack();

private slots:
    void on_backButton_clicked();

private:
    Ui::ManageContentListWindow *ui;
    ManageContentControl *contentManagementCtrl;

    void displayBookList();
    void displayChapterList(int);
    void displaySectionList(int);
    void displaySectionData(int);
};

#endif // MANAGECONTENTLISTWINDOW_H
