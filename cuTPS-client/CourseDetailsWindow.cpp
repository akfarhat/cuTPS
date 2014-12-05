#include "CourseDetailsWindow.h"
#include "ui_CourseDetailsWindow.h"

CourseDetailsWindow::CourseDetailsWindow(QWidget *parent,
                                         ManageCourseControl *ctrl,
                                         CourseRequestAPI *api) :
    manageCourseCtrl(ctrl),
    requestAPI(api),
    QMainWindow(parent),
    ui(new Ui::CourseDetailsWindow)
{
    ui->setupUi(this);

    this->courses = NULL;

    this->displayCourseList();
}

CourseDetailsWindow::~CourseDetailsWindow()
{
    delete ui;

    if (this->courses != NULL)
        delete this->courses;
}

void CourseDetailsWindow::displayCourseList()
{
    if (this->courses != NULL)
        delete this->courses;

    this->courses = new QVector<Course*>();

    /// This stuff will come from a request to the server for courses ///
    QVector<Textbook*> *books = new QVector<Textbook*>();
    books->append(new Textbook(1, "Crazy Diagrams", 30593, true, "1234567"));
    books->append(new Textbook(2, "Whoa diagrams, bro", 435943, true, "1234568"));
    books->append(new Textbook(3, "More diagrams", 2342356, true, "1234569"));
    Course *c = new Course("Comp 3004", "Advanced Diagrams", *books);
    Course *c2 = new Course("Comp 3005", "Database stuff", *books);
    //////////////////////////////////////////////////////////////////////

    this->courses->append(c);
    this->courses->append(c2);

    this->ui->courseList->clear();
    for (Course *course: *this->courses) {
        this->ui->courseList->addItem(course->getCourseCode() + "-"
                                    + course->getCourseName());
    }
}

void CourseDetailsWindow::displayCourseDetails(Course *c)
{
    this->ui->courseCodeEdit->setText(c->getCourseCode());
    this->ui->courseNameEdit->setText(c->getCourseName());

    this->ui->bookList->clear();
    for (Textbook *book: *(c->getRequiredTexts())) {
        this->ui->bookList->addItem(book->getTitle());
    }
}

void CourseDetailsWindow::on_backButton_clicked()
{
    this->close();
    emit courseNavigateBack();
}

void CourseDetailsWindow::on_courseList_clicked(const QModelIndex &index)
{
    this->displayCourseDetails(this->courses->at(index.row()));
}
