// Traceability:
//   ManageContentListWindow in the ContentManagement subsystem

#ifndef MANAGECONTENTLISTWINDOW_H
#define MANAGECONTENTLISTWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

#include "ContentRequestAPI.h"

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
                                     ManageContentControl *cmCtr = NULL,
                                     ContentRequestAPI *api = NULL);
    ~ManageContentListWindow();

signals:
    void navigateBack();

private slots:
    void on_backButton_clicked();

    void on_contentList_clicked(const QModelIndex &index);

    void on_contentList_doubleClicked(const QModelIndex &index);

private:
    int contentDepth;

    Ui::ManageContentListWindow *ui;

    ManageContentControl *contentManagementCtrl;

    ContentRequestAPI *requestAPI;

    QVector<SellableItem*> *listedItems;

    void displayBookList();
    void displayChapterList(int);
    void displaySectionList(int);
    void displaySectionData(int);
};

#endif // MANAGECONTENTLISTWINDOW_H
