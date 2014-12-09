// Traceability:
//   ManageContentListWindow in the ContentManagement subsystem

#ifndef MANAGECONTENTLISTWINDOW_H
#define MANAGECONTENTLISTWINDOW_H
#define MAX_ITEM_DEPTH 2

#include <QMainWindow>
#include <QModelIndex>

#include "ContentRequestAPI.h"
#include "AddTextbookWindow.h"
#include "AddChapterWindow.h"
#include "AddSectionWindow.h"

#include "Entity/Section.h"
#include "Entity/Chapter.h"
#include "Entity/Textbook.h"

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

    void refreshContents();

signals:
    void navigateBack();
    void deleteItem(int, QString);

public slots:
    // Response from networking for getAllBooks()
    void textbookListReceived(QUuid,int,QList<Textbook*>*);
    void updateCompleted(QUuid requestId, int code,
                         InvocationDescriptor invo, qint32 id);

private slots:
    void on_backButton_clicked();

    void on_contentList_clicked(const QModelIndex &index);

    void on_contentList_doubleClicked(const QModelIndex &index);

    void on_contentBackButton_clicked();

    void on_newContentButton_clicked();

    void on_deleteItemButton_clicked();

    void on_modifyItemButton_clicked();

private:
    int contentDepth;

    Ui::ManageContentListWindow *ui;

    ManageContentControl *contentManagementCtrl;

    ContentRequestAPI *requestAPI;

    // There is probably a much nicer approach to this
    // using polymorphism. Taking a shortcut to get a P.O.C.
    QVector<Textbook*> *textbookList;
    QVector<Chapter*> *chapterList;
    QVector<Section*> *sectionList;

    AddTextbookWindow *addBookWin;

    AddChapterWindow *addChapterWin;

    AddSectionWindow *addSectionWin;

    // Note these members are here to move on with UI implementation
    // while assuming that it is possible to have null parents for
    // the sellable Items being displayed. These can be removed
    // in the case that we can look it up in the parent attribute
    int bookId;
    int chapterId;

    SellableItem *getSelectedItem();
    SellableItem *getSelectedItem(int);
    void displayBookList();
    void displayChapterList(Textbook*);
    void displaySectionList(Chapter*);
    void addTextbook();
    void addChapter();
    void addSection();
    void modTextbook();
    void modChapter();
    void modSection();
    void clearTextbooks();
    void clearChapters();
    void clearSections();
};

#endif // MANAGECONTENTLISTWINDOW_H
