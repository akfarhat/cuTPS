
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

    if (this->addCourseWin != NULL)
        delete this->addCourseWin;

    if (this->addReqBooksWin != NULL)
        delete this->addReqBooksWin;
}

void CourseDetailsWindow::displayCourseList()
{
    if (this->courses != NULL) {
        delete this->courses;
        this->courses = NULL;
    }

    this->courses = new QVector<Course*>();

    /// TODO: This stuff will come from a request to the server for courses ///
    QVector<Textbook*> *books = new QVector<Textbook*>();
    books->append(new Textbook(1, "Crazy Diagrams", 30593, true, "1234567"));
    books->append(new Textbook(2, "Whoa diagrams, bro", 435943, true, "1234568"));
    books->append(new Textbook(3, "More diagrams", 2342356, true, "1234569"));
    Course *c = new Course("Comp 3004", "Advanced Diagrams", *books);
    Course *c2 = new Course("Comp 3005", "Database stuff", *books);
    //////////////////////////////////////////////////////////////////////

    this->courses->append(c);
    this->courses->append(c2);

    this->ui->bookList->clear();
    this->ui->courseList->clear();
    this->ui->deleteBookButton->setEnabled(false);

    for (Course *course: *this->courses) {
        this->ui->courseList->addItem(course->getCourseCode() + "-"
                                    + course->getCourseName());
    }
}

void CourseDetailsWindow::displayCourseDetails(Course *c)
{
    this->ui->deleteBookButton->setEnabled(false);
    this->ui->courseCodeEdit->setEnabled(true);
    this->ui->courseNameEdit->setEnabled(true);
    this->ui->saveCourseButton->setEnabled(true);
    this->ui->addBookButton->setEnabled(true);
    this->ui->deleteCourseButton->setEnabled(true);

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

void CourseDetailsWindow::on_addCourseButton_clicked()
{
    this->addCourseWin = new AddCourseWindow(this);

    connect(addCourseWin, SIGNAL(saveNewCourse(QString,QString)),
            (QObject *)manageCourseCtrl, SLOT(saveNewCourse(QString, QString)));

    this->addCourseWin->setModal(true);
    this->addCourseWin->show();
}

void CourseDetailsWindow::on_saveCourseButton_clicked()
{
    QString code = this->ui->courseCodeEdit->text();
    QString name = this->ui->courseNameEdit->text();

    int index = this->ui->courseList->currentIndex().row();
    int courseId = this->courses->at(index)->getId();

    emit modifyCourse(courseId, code, name);
}

void CourseDetailsWindow::on_bookList_clicked(const QModelIndex &index)
{
    this->ui->deleteBookButton->setEnabled(true);
}

void CourseDetailsWindow::on_deleteCourseButton_clicked()
{
    int index = this->ui->courseList->currentIndex().row();
    int courseId = this->courses->at(index)->getId();

    emit deleteCourse(courseId);
}

void CourseDetailsWindow::on_deleteBookButton_clicked()
{
    int courseIndex = this->ui->courseList->currentIndex().row();

    Course *c = this->courses->at(courseIndex);

    QVector<qint32> *requiredBookIds = c->getRequiredTextsIds();
    int courseId = c->getId();

    int bookIndex = this->ui->bookList->currentIndex().row();

    emit removeRequiredBook((int)requiredBookIds->at(bookIndex), courseId);
}

void CourseDetailsWindow::on_addBookButton_clicked()
{
    int selectedCourseIndex = this->ui->courseList->currentIndex().row();
    int selectedCourseId = this->courses->at(selectedCourseIndex)->getId();

    this->addReqBooksWin = new AddRequiredBookWindow(this,
                                                     this->requestAPI,
                                                     selectedCourseId);

    connect(this->addReqBooksWin, SIGNAL(addRequiredBooks(QVector<int>&,int)),
            (QObject *)this->manageCourseCtrl, SLOT(addRequiredBooks(QVector<int>&, int)));

    this->addReqBooksWin->setModal(true);

    this->addReqBooksWin->show();
}
