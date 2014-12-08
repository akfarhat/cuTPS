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
    this->addBookWin = NULL;
    this->addChapterWin = NULL;
    this->addSectionWin = NULL;

    this->bookId = -1;
    this->chapterId = -1;

    this->displayBookList();
}

ManageContentListWindow::~ManageContentListWindow()
{
    delete ui;

    if (this->addBookWin != NULL)
        delete this->addBookWin;

    if (this->addChapterWin != NULL)
        delete this->addChapterWin;

    if (this->addSectionWin != NULL)
        delete this->addSectionWin;
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
        for (int i = 0; i < books->size(); i++)
            delete this->listedItems->at(i);

        delete this->listedItems;
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

    this->bookId = bookId;

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
        for (int i = 0; i < chapters->size(); i++)
            delete this->listedItems->at(i);

        delete this->listedItems;
    }

    this->listedItems = chapters;

    // Display the books in the itemList.
    this->ui->contentList->clear();
    for (SellableItem *chapter: *chapters) {
        qDebug() << "adding chapter ptr: " << chapter;
        qDebug() << "its id is " << chapter->getId();
        this->ui->contentList->addItem(chapter->getTitle());
    }
}

void ManageContentListWindow::displaySectionList(int chapterId)
{
    qDebug() << "Displaying section list for chapterId = " << chapterId;

    this->chapterId = chapterId;

    // Request all sections (id, title) from server for chapterId
    ////////// pretend for now that this list represents actual data: /////////
    QVector<SellableItem*> *sections = new QVector<SellableItem*>();
    Section *s1 = new Section(9, NULL, 1, "Section One", 325, true);
    Section *s2 = new Section(10, NULL, 2, "Section Two", 354, true);
    Section *s3 = new Section(11, NULL, 3, "Section Three", 311, true);
    Section *s4 = new Section(12, NULL, 4, "Section Four", 166, true);
    sections->append(s1); sections->append(s2); sections->append(s3); sections->append(s4);
    /////////////////////////////////////////////////////////////////////////

    // Update the window's item list vector
    if (this->listedItems != NULL) {
        for (int i = 0; i < sections->size(); i++)
            delete this->listedItems->at(i);

        delete this->listedItems;
    }

    this->listedItems = sections;

    // Display the books in the itemList.
    this->ui->contentList->clear();
    for (SellableItem *section: *sections) {
        this->ui->contentList->addItem(section->getTitle());
    }
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
    if (this->contentDepth >= MAX_ITEM_DEPTH)
        return;

    SellableItem *selectedItem = this->listedItems->at(index.row());

    this->contentDepth++;

    this->ui->contentBackButton->setEnabled(true);

    this->ui->metadataView->setText("");

    if (this->contentDepth == 1)
        this->displayChapterList(selectedItem->getId());
    else if(this->contentDepth == 2)
        this->displaySectionList(selectedItem->getId());
}

void ManageContentListWindow::on_contentBackButton_clicked()
{
    if (this->contentDepth <= 0)
        return;

    if (this->contentDepth == 1)
        this->ui->contentBackButton->setEnabled(false);

    this->contentDepth--;

    this->ui->metadataView->setText("");

    // TODO: Depending on whether the parents are guaranteed to be defined,
    // we can get the ID that way, or store it as a temp value when descending.
    if (this->contentDepth == 0)
        this->displayBookList();
    else if(this->contentDepth == 1)
        this->displayChapterList(-1);
}

void ManageContentListWindow::on_newContentButton_clicked()
{
    switch (this->contentDepth) {
        case (0):
            this->addTextbook();
            break;
        case (1):
            this->addChapter();
            break;
        case (2):
            this->addSection();
            break;
    }
}

void ManageContentListWindow::addTextbook()
{
    qDebug() << "ManageContentListWindow::addTextbook";
    this->addBookWin = new AddTextbookWindow(this);

    connect(this->addBookWin, SIGNAL(addTextbook(QString,int,bool,QString)),
            this->contentManagementCtrl, SLOT(addTextbook(QString,int,bool,QString)));

    this->addBookWin->setModal(true);
    this->addBookWin->show();
}

void ManageContentListWindow::addChapter()
{
    qDebug() << "ManageContentListWindow::addChapter";

    this->addChapterWin = new AddChapterWindow(this, this->bookId);

    connect(this->addChapterWin, SIGNAL(addChapter(QString,int,bool,int)),
            this->contentManagementCtrl, SLOT(addChapter(QString,int,bool,int)));

    this->addChapterWin->setModal(true);
    this->addChapterWin->show();
}

void ManageContentListWindow::addSection()
{
   qDebug() << "ManageContentListWindow::addSection()";

   this->addSectionWin = new AddSectionWindow(this, this->chapterId);

   connect(this->addSectionWin, SIGNAL(addSection(QString,int,bool,int)),
           this->contentManagementCtrl, SLOT(addSection(QString,int,bool,int)));

   this->addSectionWin->setModal(true);
   this->addSectionWin->show();
}
