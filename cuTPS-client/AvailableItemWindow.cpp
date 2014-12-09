#include "AvailableItemWindow.h"
#include "ui_AvailableItemWindow.h"

#include <QDebug>

AvailableItemWindow::AvailableItemWindow(QWidget *parent, CartRequestsAPI *api, QVector<Textbook*> *books) :
    QDialog(parent),
    requestAPI(api),
    listedBooks(books),
    ui(new Ui::AvailableItemWindow)
{
    ui->setupUi(this);
    ui->addToCartButton->setEnabled(false);

    this->contentDepth = 0;

    this->bookId = -1;
    this->chapterId = -1;


    this->displayBookList();
}

AvailableItemWindow::~AvailableItemWindow()
{
    delete ui;
}


void AvailableItemWindow::setError(QString message) {
    ui->message->setStyleSheet("QLabel { color : red; }");
    ui->message->setText(message);
    ui->message->show();
}

void AvailableItemWindow::setMessage(QString message) {
    ui->message->setStyleSheet("QLabel { color : green; }");
    ui->message->setText(message);
    ui->message->show();
}

Textbook* AvailableItemWindow::getBookFromList(int bookId, QVector<Textbook *> *books)
{
    for (Textbook *book: *books) {
        if (book->getId() == bookId) {
            return book;
        }
    }

    return NULL;
}

Chapter* AvailableItemWindow::getChapterFromList(int bookId, int chapterId, QVector<Textbook *> *books)
{
    Textbook *theBook = getBookFromList(bookId, books);

    for (Chapter* chapter: theBook->getChapterList()) {
        if (chapter->getId() == chapterId) {
            return chapter;
        }
    }

    return NULL;
}


void AvailableItemWindow::displayBookList()
{
    qDebug() << "Displaying book list";
    ui->addToCartButton->setEnabled(false);


    // Display the books
    this->ui->contentList->clear();
    for (Textbook *book: *listedBooks) {
        this->ui->contentList->addItem(book->getTitle());
    }

}

void AvailableItemWindow::displayChapterList(int bookId)
{
    qDebug() << "Displaying chapter list for bookId = " << bookId;
    ui->addToCartButton->setEnabled(false);

    this->bookId = bookId;


    // Get the book with the specified book ID from the list of books
    Textbook *theBook = getBookFromList(bookId, listedBooks);


    // Display the Chapters
    this->ui->contentList->clear();
    for (Chapter *chapter: theBook->getChapterList()) {
        qDebug() << "adding chapter ptr: " << chapter;
        qDebug() << "its id is " << chapter->getId();
        this->ui->contentList->addItem(chapter->getTitle());
    }
}

void AvailableItemWindow::displaySectionList(int chapterId)
{
    qDebug() << "Displaying section list for chapterId = " << chapterId;
    ui->addToCartButton->setEnabled(false);

    this->chapterId = chapterId;


    // Get the chapter of the book associated with the sections
    Chapter *theChapter = getChapterFromList(this->bookId, chapterId, listedBooks);

    // Display the sections
    this->ui->contentList->clear();
    for (Section *section: theChapter->getSectionList()) {
        this->ui->contentList->addItem(section->getTitle());
    }
}



void AvailableItemWindow::on_backButton_clicked()
{
    requestAPI = NULL;
    listedBooks = NULL;
    selectedItem = NULL;
    this->close();
    emit availableItemWindowClosed();
}

void AvailableItemWindow::on_contentList_clicked(const QModelIndex &index)
{
    qDebug() << "Single click on item at index: " << QString::number(index.row());

    ui->addToCartButton->setEnabled(true);

    if (contentDepth == 0) {
        selectedItem = this->listedBooks->at(index.row());
    } else if (contentDepth == 1) {
        Textbook *theBook = getBookFromList(bookId, listedBooks);
        selectedItem = theBook->getChapterList().at(index.row());
    } else if (contentDepth == 2) {
        Chapter *theChapter = getChapterFromList(bookId, chapterId, listedBooks);
        selectedItem = theChapter->getSectionList().at(index.row());
    }


    qDebug() << "Selected item details: " << selectedItem->getDetails();

    this->ui->metadataView->setText(selectedItem->getDetails());
}


void AvailableItemWindow::on_contentList_doubleClicked(const QModelIndex &index)
{
    if (this->contentDepth >= MAX_ITEM_DEPTH)
        return;

    if (contentDepth == 0) {
        selectedItem = this->listedBooks->at(index.row());
    } else if (contentDepth == 1) {
        Textbook *theBook = getBookFromList(bookId, listedBooks);
        selectedItem = theBook->getChapterList().at(index.row());
    } else if (contentDepth == 2) {
        Chapter *theChapter = getChapterFromList(bookId, chapterId, listedBooks);
        selectedItem = theChapter->getSectionList().at(index.row());
    }

    this->contentDepth++;

    this->ui->contentBackButton->setEnabled(true);

    this->ui->metadataView->setText("");

    if (this->contentDepth == 1)
        this->displayChapterList(selectedItem->getId());
    else if(this->contentDepth == 2)
        this->displaySectionList(selectedItem->getId());
}



void AvailableItemWindow::on_contentBackButton_clicked()
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
        this->displayChapterList(bookId);
}


void AvailableItemWindow::on_addToCartButton_clicked()
{
    qDebug() << "Add to cart button clicked for item " + selectedItem->getId();

    SellableItem *newItem;

    if (selectedItem->getType() == "Textbook") {
        newItem = new Textbook(selectedItem->getId(), selectedItem->getName(), "", "", selectedItem->getPriceCents(), selectedItem->getAvailability(), "");
    } else if (selectedItem->getType() == "Chapter") {
        newItem = new Chapter(selectedItem->getId(), NULL, NULL, selectedItem->getName(), selectedItem->getPriceCents(), selectedItem->getAvailability());
    } else if (selectedItem->getType() == "Section") {
        newItem = new Section(selectedItem->getId(), NULL, NULL, selectedItem->getName(), selectedItem->getPriceCents(), selectedItem->getAvailability());
    }

    requestAPI->getStudent()->getCart()->addItem(newItem);

    setMessage("The item has been added to your shopping cart");
}
