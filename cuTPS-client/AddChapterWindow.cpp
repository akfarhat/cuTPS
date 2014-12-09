#include "AddChapterWindow.h"
#include "ui_AddChapterWindow.h"

AddChapterWindow::AddChapterWindow(QWidget *parent, int bookID, int chapID) :
    QDialog(parent),
    bookId(bookID),
    chapId(chapID),
    ui(new Ui::AddChapterWindow)
{
    ui->setupUi(this);
}

AddChapterWindow::~AddChapterWindow()
{
    delete ui;
}

void AddChapterWindow::on_cancelButton_clicked()
{
    this->close();
}

void AddChapterWindow::on_addButton_clicked()
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

    emit addChapter(name, chapId, priceCents, available, bookId);

    this->close();
}

void AddChapterWindow::populateValues(Chapter *chapter)
{
    this->ui->nameEdit->setText(chapter->getName());
    this->ui->priceEdit->setText(QString::number(
                                     chapter->getPriceCents() / 100));
    this->ui->avaiBox->setChecked(chapter->getAvailability());
}
