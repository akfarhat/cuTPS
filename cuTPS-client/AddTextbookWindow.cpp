#include "AddTextbookWindow.h"
#include "ui_AddTextbookWindow.h"

#include <QDebug>

AddTextbookWindow::AddTextbookWindow(QWidget *parent, int bookID) :
    QDialog(parent),
    bookId(bookID),
    ui(new Ui::AddTextbookWindow)
{
    ui->setupUi(this);
}

AddTextbookWindow::~AddTextbookWindow()
{
    delete ui;
}

void AddTextbookWindow::on_cancelButton_clicked()
{
    this->close();
}

void AddTextbookWindow::on_addButton_clicked()
{
    QString name = this->ui->nameEdit->text();

    QString priceStr = this->ui->priceEdit->text();
    int priceCents = (int)(priceStr.toDouble() * 100.0f);
    if (priceCents == 0) {
        this->ui->priceEdit->setStyleSheet("QLineEdit{background: #B20000; "
                                           "color: white;}");
        return; // Reject submission
    }

    bool available = this->ui->avaiBox->isChecked();

    QString isbn = this->ui->isbnEdit->text();

    emit addTextbook(name, bookId, priceCents, available, isbn);

    this->close();
}

void AddTextbookWindow::populateValues(Textbook *book)
{
    this->ui->nameEdit->setText(book->getName());
    this->ui->isbnEdit->setText(book->getISBN());
    this->ui->priceEdit->setText(QString::number(
                                     book->getPriceCents() / 100));
    this->ui->avaiBox->setChecked(book->getAvailability());
}
