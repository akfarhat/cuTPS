// Traceability:
//   ManageContentListWindow in the ContentManagement subsystem

#ifndef MANAGECONTENTLISTWINDOW_H
#define MANAGECONTENTLISTWINDOW_H
#define MAX_ITEM_DEPTH 2

#include <QMainWindow>
#include <QModelIndex>

#include "ContentRequestAPI.h"
#include "AddTextbookWindow.h"

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

    void on_contentBackButton_clicked();

    void on_newContentButton_clicked();

private:
    int contentDepth;

    Ui::ManageContentListWindow *ui;

    ManageContentControl *contentManagementCtrl;

    ContentRequestAPI *requestAPI;

    QVector<SellableItem*> *listedItems;

    AddTextbookWindow *addBookWin;

    void displayBookList();
    void displayChapterList(int);
    void displaySectionList(int);
    void addTextbook();
    void addChapter();
    void addSection();
};

#endif // MANAGECONTENTLISTWINDOW_H
