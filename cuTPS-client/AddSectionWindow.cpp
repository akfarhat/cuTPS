#include "AddSectionWindow.h"
#include "ui_AddSectionWindow.h"

AddSectionWindow::AddSectionWindow(QWidget *parent, int chapID) :
    QDialog(parent),
    chapterId(chapID),
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

    emit addSection(name, priceCents, available, this->chapterId);

    this->close();
}
