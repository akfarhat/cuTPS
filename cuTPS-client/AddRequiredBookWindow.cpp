#include "AddRequiredBookWindow.h"
#include "ui_AddRequiredBookWindow.h"

AddRequiredBookWindow::AddRequiredBookWindow(QWidget *parent,
                                             CourseRequestAPI *api,
                                             int courseId) :
    QDialog(parent),
    ui(new Ui::AddRequiredBookWindow),
    courseRequests(api)
{
    ui->setupUi(this);

    this->courseID = courseId;

    this->populateBooks();
}

void AddRequiredBookWindow::populateBooks()
{
    this->books = new QVector<Textbook*>();

    // TODO: request books from the CourseRequestAPI
    /////Pretending for now..//////
    Textbook *b1 = new Textbook(1, "Book name", 55352, true, "1234567");
    Textbook *b2 = new Textbook(2, "Another book", 2523, true, "1234568");
    Textbook *b3 = new Textbook(3, "Book here", 8384, true, "1234569");
    Textbook *b4 = new Textbook(4, "Why so many books already", 88374, true, "1234570");
    this->books->append(b1); this->books->append(b2); this->books->append(b3); this->books->append(b4);
    ////////////////////////////////

    for (Textbook *b: *(this->books)) {
        this->ui->bookList->addItem(b->getTitle());
    }
}

AddRequiredBookWindow::~AddRequiredBookWindow()
{
    delete ui;

    if (this->books != NULL)
        delete this->books;
}

void AddRequiredBookWindow::on_cancelButton_clicked()
{
    this->close();
}

void AddRequiredBookWindow::on_addButton_clicked()
{
    // Build up a vector of all selected books to add
    QVector<int> bookIds;

    QList<QListWidgetItem*> selectedItems = this->ui->bookList->selectedItems();
    for (QListWidgetItem *item: selectedItems) {
        int bookID = this->books->at( item->listWidget()->row(item) )->getId();
        bookIds.append( bookID );
    }

    emit addRequiredBooks(bookIds, this->courseID);

    this->close();
}
