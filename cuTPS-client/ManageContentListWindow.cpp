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

    this->textbookList = NULL;
    this->chapterList = NULL;
    this->sectionList = NULL;

    this->addBookWin = NULL;
    this->addChapterWin = NULL;
    this->addSectionWin = NULL;

    this->bookId = -1;
    this->chapterId = -1;

    this->refreshContents();

    /*
    // Request all sections (id, title) from server for chapterId
    ////////// pretend for now that this list represents actual data: /////////
    Section *s1 = new Section(9, NULL, 1, "Section One", 325, true);
    Section *s2 = new Section(10, NULL, 2, "Section Two", 354, true);
    Section *s3 = new Section(11, NULL, 3, "Section Three", 311, true);
    Section *s4 = new Section(12, NULL, 4, "Section Four", 166, true);
    /////////////////////////////////////////////////////////////////////////

    ////////// pretend for now that this list represents actual data: /////////
    Chapter *c1 = new Chapter(5, NULL, 1, "Chapter One", 432, true);
    Chapter *c2 = new Chapter(6, NULL, 2, "Chapter Two", 2345, true);
    Chapter *c3 = new Chapter(7, NULL, 3, "Chapter Three", 234, true);
    Chapter *c4 = new Chapter(8, NULL, 4, "Chapter Four", 123, true);
    /////////////////////////////////////////////////////////////////////////

    ////////// pretend for now that this list represents actual data: /////////
    QList<Textbook*> *books = new QList<Textbook*>();
    Textbook *t1 = new Textbook(1, "The First Book", "1st", "Some Dorc", 554563, 1, "123456678");
    Textbook *t2 = new Textbook(2, "The Second Book", "2nd", "Some Corc", 34536, 1, "123456679");
    Textbook *t3 = new Textbook(3, "The Third Book", "3rd", "Some Borc", 2345, 1, "123456680");
    Textbook *t4 = new Textbook(4, "The Fourth Book", "999th", "Some Pork :D", 2234556, 1, "123456681");
    books->append(t1); books->append(t2); books->append(t3); books->append(t4);
    /////////////////////////////////////////////////////////////////////////

    c1->addSection(*s1); //c1->addSection(*s2); c1->addSection(*s3); c1->addSection(*s4);
    c2->addSection(*s2); //c2->addSection(*s2); c2->addSection(*s3); c2->addSection(*s4);
    c3->addSection(*s3); //c3->addSection(*s2); c3->addSection(*s3); c3->addSection(*s4);
    c4->addSection(*s4); //c4->addSection(*s2); c4->addSection(*s3); c4->addSection(*s4);

    t1->addChapter(*c1); //t1->addChapter(*c2); t1->addChapter(*c3); t1->addChapter(*c4);
    t2->addChapter(*c2); //t2->addChapter(*c2); t2->addChapter(*c3); t2->addChapter(*c4);
    t3->addChapter(*c3); //t3->addChapter(*c2); t3->addChapter(*c3); t3->addChapter(*c4);
    t4->addChapter(*c4); //t4->addChapter(*c2); t4->addChapter(*c3); t4->addChapter(*c4);

    QUuid uid;
    this->textbookListReceived(uid, 0, books);
    */
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

    // Clear the containers
    this->clearSections();
    this->clearChapters();

    // Deep delete on textbook container and all contents.
    // This will propogate down to the chapters and sections
    if (this->textbookList != NULL) {
        int size = this->textbookList->size();
        for (int i = 0; i < size; i++)
            delete this->textbookList->at(i);

        delete this->textbookList;
        this ->textbookList = NULL;
    }
}

void ManageContentListWindow::on_backButton_clicked()
{
    this->close();
    emit navigateBack();
}

void ManageContentListWindow::refreshContents()
{
    this->requestAPI->getAllBooks();
}

void ManageContentListWindow::textbookListReceived(
        QUuid reqId, int code,
        QList<Textbook*>* bookList)
{
    qDebug() << "ManageContentListWindow::TextbookListReceived "
             << "num books: " << bookList->size();

    this->clearTextbooks();

    // Fill the text list from the QList
    this->textbookList = new QVector<Textbook*>(); // current display
    for (Textbook *book: *bookList)
        this->textbookList->append(book);

    this->displayBookList();
}

void ManageContentListWindow::clearTextbooks()
{
    if (this->textbookList != NULL) {
        qDebug() << "clearing textbookList";

        delete this->textbookList;
        this->textbookList = NULL;
    }
}

void ManageContentListWindow::clearChapters()
{
    if (this->chapterList != NULL) {
        qDebug() << "Clearing chapterList";

        delete this->chapterList;
        this->chapterList = NULL;
    }
}

void ManageContentListWindow::clearSections()
{
    if (this->sectionList != NULL) {
        qDebug() << "Clearing sectionList";

        delete this->sectionList;
        this->sectionList = NULL;
    }
}

void ManageContentListWindow::displayBookList()
{
    qDebug() << "Displaying book list";

    this->contentDepth = 0;

    this->ui->modifyItemButton->setEnabled(false);
    this->ui->deleteItemButton->setEnabled(false);

    // Clear lower level content lists
    this->clearChapters();
    this->clearSections();

    // Display the books in the item list.
    this->ui->contentList->clear();
    for (Textbook *book: *(this->textbookList)) {
        this->ui->contentList->addItem(book->getTitle());
    }

}

void ManageContentListWindow::displayChapterList(Textbook *book)
{
    qDebug() << "Displaying chapter list for bookId = " << bookId;

    this->ui->modifyItemButton->setEnabled(false);
    this->ui->deleteItemButton->setEnabled(false);

    // Clean up memory for lower level content lists
    this->clearSections();

    this->bookId = -1;

    if (this->chapterList == NULL) {
        this->chapterList = new QVector<Chapter*>(book->getChapterList());
        this->bookId = book->getId();
    }

    // Display the books in the item list.
    this->ui->contentList->clear();
    for (Chapter *chapter: *(this->chapterList)) {
        qDebug() << "adding chapter ptr: " << chapter;
        qDebug() << "its id is " << chapter->getId();
        this->ui->contentList->addItem(chapter->getTitle());
    }
}

void ManageContentListWindow::displaySectionList(Chapter *chapter)
{
    qDebug() << "Displaying section list for chapterId = " << chapterId;

    this->ui->modifyItemButton->setEnabled(false);
    this->ui->deleteItemButton->setEnabled(false);

    this->chapterId = -1;

    if (this->sectionList == NULL) { // re-use if not null
        this->sectionList = new QVector<Section*>(chapter->getSectionList());
        this->chapterId = chapter->getId();
    }

    // Display the books in the item list.
    this->ui->contentList->clear();
    for (Section *section: *(this->sectionList)) {
        this->ui->contentList->addItem(section->getTitle());
    }
}

void ManageContentListWindow::on_contentList_clicked(const QModelIndex &index)
{
    this->ui->modifyItemButton->setEnabled(true);
    this->ui->deleteItemButton->setEnabled(true);

    qDebug() << "Single click on item at index: " << QString::number(index.row());

    SellableItem *selectedItem = this->getSelectedItem(index.row());

    qDebug() << "Selected item details: " << selectedItem->getDetails();

    this->ui->metadataView->setText(selectedItem->getDetails());
}

void ManageContentListWindow::on_contentList_doubleClicked(const QModelIndex &index)
{
    if (this->contentDepth >= MAX_ITEM_DEPTH)
        return;

    SellableItem *selectedItem = this->getSelectedItem(index.row());

    this->contentDepth++;

    this->ui->contentBackButton->setEnabled(true);

    this->ui->metadataView->setText("");

    if (this->contentDepth == 1)
        this->displayChapterList(dynamic_cast<Textbook*>(selectedItem));
    else if(this->contentDepth == 2)
        this->displaySectionList(dynamic_cast<Chapter*>(selectedItem));
}

void ManageContentListWindow::on_contentBackButton_clicked()
{
    if (this->contentDepth <= 0)
        return;

    if (this->contentDepth == 1)
        this->ui->contentBackButton->setEnabled(false);

    this->contentDepth--;

    this->ui->metadataView->setText("");

    if (this->contentDepth == 0)
        this->displayBookList();
    else if(this->contentDepth == 1)
        this->displayChapterList(NULL);
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

void ManageContentListWindow::updateCompleted(QUuid requestId, int code, InvocationDescriptor invo, qint32 id)
{
    qDebug() << "ManageContentListWindow::updateCompleted!! "
             << requestId << " code=" << code;

    this->refreshContents();
}

void ManageContentListWindow::addTextbook()
{
    qDebug() << "ManageContentListWindow::addTextbook";
    this->addBookWin = new AddTextbookWindow(this, -1);

    connect(this->addBookWin, SIGNAL(addTextbook(QString,QString,QString,int,int,bool,QString)),
            this->contentManagementCtrl, SLOT(addTextbook(QString,QString,QString,int,int,bool,QString)));

    this->addBookWin->setModal(true);
    this->addBookWin->show();
}

void ManageContentListWindow::addChapter()
{
    qDebug() << "ManageContentListWindow::addChapter";

    this->addChapterWin = new AddChapterWindow(this, this->bookId, -1);

    connect(this->addChapterWin, SIGNAL(addChapter(QString,int,int,bool,int)),
            this->contentManagementCtrl, SLOT(addChapter(QString,int,int,bool,int)));

    this->addChapterWin->setModal(true);
    this->addChapterWin->show();
}

void ManageContentListWindow::addSection()
{
   qDebug() << "ManageContentListWindow::addSection()";

   this->addSectionWin = new AddSectionWindow(this, this->bookId, this->chapterId, -1);

   connect(this->addSectionWin, SIGNAL(addSection(QString,int,int,bool,int,int)),
           this->contentManagementCtrl, SLOT(addSection(QString,int,int,bool,int,int)));

   this->addSectionWin->setModal(true);
   this->addSectionWin->show();
}

void ManageContentListWindow::on_modifyItemButton_clicked()
{
    switch (this->contentDepth) {
        case (0):
            this->modTextbook();
            break;
        case (1):
            this->modChapter();
            break;
        case (2):
            this->modSection();
            break;
    }
}

void ManageContentListWindow::modTextbook()
{
    qDebug() << "ManageContentListWindow::modTextbook";

    Textbook *item = dynamic_cast<Textbook *>(this->getSelectedItem());
    if (item == NULL) return;

    this->addBookWin = new AddTextbookWindow(this, item->getId());

    this->addBookWin->setWindowTitle("Modify Textbook");

    this->addBookWin->populateValues(item);

    connect(this->addBookWin, SIGNAL(addTextbook(QString,QString,QString,int,int,bool,QString)),
            this->contentManagementCtrl, SLOT(addTextbook(QString,QString,QString,int,int,bool,QString)));

    this->addBookWin->setModal(true);
    this->addBookWin->show();
}

void ManageContentListWindow::modChapter()
{
    qDebug() << "ManageContentListWindow::modChapter";

    Chapter *item = dynamic_cast<Chapter *>(this->getSelectedItem());
    if (item == NULL) return;

    this->addChapterWin = new AddChapterWindow(this, this->bookId, item->getId());

    this->addChapterWin->setWindowTitle("Modify Chapter");

    this->addChapterWin->populateValues(item);

    connect(this->addChapterWin, SIGNAL(addChapter(QString,int,int,bool,int)),
            this->contentManagementCtrl, SLOT(addChapter(QString,int,int,bool,int)));

    this->addChapterWin->setModal(true);
    this->addChapterWin->show();
}

void ManageContentListWindow::modSection()
{
    qDebug() << "ManageContentListWindow::modSection()";

    Section *item = dynamic_cast<Section *>(this->getSelectedItem());
    if (item == NULL) return;

    this->addSectionWin = new AddSectionWindow(this, this->bookId,
                                               this->chapterId, item->getId());

    this->addSectionWin->setWindowTitle("Modify Section");

    this->addSectionWin->populateValues(item);

    connect(this->addSectionWin, SIGNAL(addSection(QString,int,int,bool,int,int)),
            this->contentManagementCtrl, SLOT(addSection(QString,int,int,bool,int,int)));

    this->addSectionWin->setModal(true);
    this->addSectionWin->show();
}

void ManageContentListWindow::on_deleteItemButton_clicked()
{
    // This request could be implemented in a
    // way that's ignorant of item type.

    int itemId = this->getSelectedItem()->getId();
    QString type = "";

    switch (this->contentDepth) {
        case (0):
            type = "textbook";
            break;
        case (1):
            type = "chapter";
            break;
        case (2):
            type = "section";
            break;
    }
    emit deleteItem(itemId, type);
}

SellableItem* ManageContentListWindow::getSelectedItem(int index)
{
    // this is kind of ugly.. As mentioned in header
    SellableItem *item;

    switch (this->contentDepth) {
        case 0:
            item = this->textbookList->at(index);
            break;
        case 1:
            item = this->chapterList->at(index);
            break;
        case 2:
            item = this->sectionList->at(index);
            break;
    }
    return item;
}

SellableItem* ManageContentListWindow::getSelectedItem()
{
    int index = this->ui->contentList->currentIndex().row();
    return this->getSelectedItem(index);
}
