#include "AddSectionWindow.h"
#include "ui_AddSectionWindow.h"

AddSectionWindow::AddSectionWindow(QWidget *parent, int bookID, int chapID, int sectID) :
    QDialog(parent),
    bookId(bookID),
    chapterId(chapID),
    secId(sectID),
    ui(new Ui::AddSectionWindow)
{
    ui->setupUi(this);
}

AddSectionWindow::~AddSectionWindow()
{
    delete ui;
}

void AddSectionWindow::on_cancelButton_clicked()
{
    this->close();
}

void AddSectionWindow::on_addButton_clicked()
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

    emit addSection(name, secId, priceCents, available, this->bookId, this->chapterId);

    this->close();
}

void AddSectionWindow::populateValues(Section *section)
{
    this->ui->nameEdit->setText(section->getName());
    this->ui->priceEdit->setText(QString::number(
                                     section->getPriceCents() / 100));
    this->ui->avaiBox->setChecked(section->getAvailability());
}
