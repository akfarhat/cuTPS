#include "ManageContentListWindow.h"
#include "ui_ManageContentListWindow.h"
#include "ManageContentControl.h"
#include "Entity/Textbook.h"
#include "Entity/Chapter.h"
#include "Entity/Section.h"


#include <QDebug>

ManageContentListWindow::ManageContentListWindow(QWidget *parent,
                                                 ManageContentControl *cmCtr,
                                                 ContentRequestAPI *api) :
    QMainWindow(parent),
    requestAPI(api),
    contentManagementCtrl(cmCtr),
    ui(new Ui::ManageContentListWindow)
{
    ui->setupUi(this);

    this->contentDepth = 0;

    this->listedItems = NULL;

    this->displayBookList();
}

ManageContentListWindow::~ManageContentListWindow()
{
    delete ui;
}

void ManageContentListWindow::on_backButton_clicked()
{
    this->close();
    emit navigateBack();
}

void ManageContentListWindow::displayBookList()
{
    qDebug() << "Displaying book list";

    // Request all books (id, title) from server
    ////////// pretend for now that this list represents actual data: /////////
    QVector<SellableItem*> *books = new QVector<SellableItem*>();
    Textbook *t1 = new Textbook(1, "The First Book", 554563, 1, "123456678");
    Textbook *t2 = new Textbook(2, "The Second Book", 34536, 1, "123456679");
    Textbook *t3 = new Textbook(3, "The Third Book", 2345, 1, "123456680");
    Textbook *t4 = new Textbook(4, "The Fourth Book", 2234556, 1, "123456681");
    books->append(t1); books->append(t2); books->append(t3); books->append(t4);
    /////////////////////////////////////////////////////////////////////////

    // Update the window's item list vector
    if (this->listedItems != NULL) {
        //for (int i = 0; i < books->size(); i++)
        //    delete books->at(i);

        //delete this->listedItems;
    }

    this->listedItems = books;

    // Display the books in the itemList.
    this->ui->contentList->clear();
    for (SellableItem *book: *books) {
        this->ui->contentList->addItem(book->getTitle());
    }

}

void ManageContentListWindow::displayChapterList(int bookId)
{
    qDebug() << "Displaying chapter list for bookId = " << bookId;

    // Request all chapters (id, title) from server for bookId
    ////////// pretend for now that this list represents actual data: /////////
    QVector<SellableItem*> *chapters = new QVector<SellableItem*>();
    Chapter *c1 = new Chapter(5, NULL, 1, "Chapter One", 432, true);
    Chapter *c2 = new Chapter(6, NULL, 2, "Chapter Two", 2345, true);
    Chapter *c3 = new Chapter(7, NULL, 3, "Chapter Three", 234, true);
    Chapter *c4 = new Chapter(8, NULL, 4, "Chapter Four", 123, true);
    chapters->append(c1); chapters->append(c2); chapters->append(c3); chapters->append(c4);
    /////////////////////////////////////////////////////////////////////////

    // Update the window's item list vector
    if (this->listedItems != NULL) {
        //for (int i = 0; i < chapters->size(); i++)
        //    delete chapters->at(i);

        //delete this->listedItems;
    }

    this->listedItems = chapters;

    // Display the books in the itemList.
    this->ui->contentList->clear();
    for (SellableItem *chapter: *chapters) {
        this->ui->contentList->addItem(chapter->getTitle());
    }

    // Display the chapters in the itemList.
}

void ManageContentListWindow::displaySectionList(int chapterId)
{
    qDebug() << "Displaying section list for chapterId = " << chapterId;

    // Request all sections (id, title) from server for chapterId

    // Display the sections in the itemList.
}

void ManageContentListWindow::on_contentList_clicked(const QModelIndex &index)
{
    qDebug() << "Single click on item at index: " << QString::number(index.row());

    SellableItem *selectedItem = this->listedItems->at(index.row());

    qDebug() << "Selected item details: " << selectedItem->getDetails();

    this->ui->metadataView->setText(selectedItem->getDetails());
}

void ManageContentListWindow::on_contentList_doubleClicked(const QModelIndex &index)
{
    SellableItem *selectedItem = this->listedItems->at(index.row());

    this->contentDepth++;

    if (this->contentDepth == 1)
        this->displayChapterList(selectedItem->getId());
    else if(this->contentDepth == 2)
        this->displaySectionList(selectedItem->getId());
}
