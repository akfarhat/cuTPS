#include "ManageContentListWindow.h"
#include "ui_ManageContentListWindow.h"
#include "ManageContentControl.h"

#include <QDebug>

ManageContentListWindow::ManageContentListWindow(QWidget *parent,
                                                 ManageContentControl *cmCtr) :
    QMainWindow(parent),
    contentManagementCtrl(cmCtr),
    ui(new Ui::ManageContentListWindow)
{
    ui->setupUi(this);

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

    // Display the books in the itemList.

    // setup onitemclick -> displayChapterList(bookId)

    // Hide the metadata section
}

void ManageContentListWindow::displayChapterList(int bookId)
{
    qDebug() << "Displaying chapter list for bookId = " << bookId;

    // Request all chapters (id, title) from server for bookId

    // Display the chapters in the itemList.

    // setup onitemclick -> displaySectionList(chapterId)

    // request bookDetails(chapterId), display it the metadata section
}

void ManageContentListWindow::displaySectionList(int chapterId)
{
    qDebug() << "Displaying section list for chapterId = " << chapterId;

    // Request all sections (id, title) from server for chapterId

    // Display the sections in the itemList.

    // setup onitemclick -> displaySectionData(sectionId)

    // request chapterDetails(chapterId), display it the metadata section
}

void ManageContentListWindow::displaySectionData(int sectionId)
{
    qDebug() << "Displaying section data for sectionId = " << sectionId;

    // hide the itemList widget

    // request chapterDetails(chapterId), display it the metadata section
}
