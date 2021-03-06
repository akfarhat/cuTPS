#ifndef AVAILABLEITEMWINDOW_H
#define AVAILABLEITEMWINDOW_H

#define MAX_ITEM_DEPTH 2

#include <QDialog>
#include <QMap>
#include <QList>
#include <QModelIndex>

#include "CartRequestsAPI.h"
#include "Entity/SellableItem.h"
#include "Entity/Textbook.h"
#include "Entity/Chapter.h"
#include "Entity/Section.h"
#include "Entity/Course.h"


namespace Ui {
    class AvailableItemWindow;
}

class AvailableItemWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AvailableItemWindow(QWidget *parent = 0, CartRequestsAPI *api = NULL, QMap<Course*, QList<Textbook*>*>* tmap = NULL);
        ~AvailableItemWindow();

    signals:
        void availableItemWindowClosed();

    private slots:
        void on_backButton_clicked();

        void on_contentList_clicked(const QModelIndex &index);

        void on_contentList_doubleClicked(const QModelIndex &index);

        void on_contentBackButton_clicked();

        void on_addToCartButton_clicked();


    private:
        Ui::AvailableItemWindow *ui;

        CartRequestsAPI *requestAPI;

        QMap<Course*, QList<Textbook*>*>* textbookMap;

        QList<Textbook*> *bookList;

        SellableItem * selectedItem;

        int contentDepth;

        // Note these members are here to move on with UI implementation
        // while assuming that it is possible to have null parents for
        // the sellable Items being displayed. These can be removed
        // in the case that we can look it up in the parent attribute
        int bookId;
        int chapterId;

        void displayBookList();
        void displayChapterList(int);
        void displaySectionList(int);

        Textbook* getBookFromList(int &bookId, QList<Textbook*> *books);
        Chapter* getChapterFromList(int &bookId, int &chapterId, QList<Textbook *> *books);

        void setError(QString);
        void setMessage(QString);
};

#endif // AVAILABLEITEMWINDOW_H
