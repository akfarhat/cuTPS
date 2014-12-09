
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
    this->addCourseWin = NULL;
    this->addReqBooksWin = NULL;

    this->refreshCourseList();
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

void CourseDetailsWindow::refreshCourseList()
{
    // TODO: we should store the most recent requestId to ensure
    // that we are always receiving the most up to date data
    this->requestAPI->getAllCourses();

    /*
    /////////// TODO: uncomment above call, remove this stuff////////
    QVector<int> books;
    books.append(1);
    books.append(2);
    books.append(3);
    Course *c = new Course("Comp 3004", "Advanced Diagrams");
    c->setId(4); // simulating actual course from DB, will have id
    Course *c2 = new Course("Comp 3005", "Database stuff");
    c2->setId(7);
    c->addRequiredTextIds(books);
    c2->addRequiredTextIds(books);

    QList<Course*> *courseL = new QList<Course*>();
    courseL->append(c);
    courseL->append(c2);
    //////////////////////////////////////////////////////////////////////

    QUuid uid;
    this->courseListReceived(uid, 0, courseL);
    */
}

void CourseDetailsWindow::textbookListReceived(QUuid requestId, int code,
                          QList<Textbook*> *bookList)
{
    if (bookList == NULL) return;

    if (this->addReqBooksWin != NULL && !this->addReqBooksWin->isHidden()) {
        qDebug() << "All books are going to the reqAddBookWin";

        this->addReqBooksWin->populateBooks(bookList);

        return;
    }

    qDebug() << "CourseDetailsWindow::textbookListReceived(" << requestId
             << ", " << code << ", size=" <<bookList->size() << ")";

    this->ui->bookList->clear();

    for (Textbook *book: *bookList) {
        this->ui->bookList->addItem(book->getTitle());
    }

    this->ui->deleteBookButton->setEnabled(false);

    delete bookList;
}

void CourseDetailsWindow::courseListReceived(QUuid requestId, int code,
                        QList<Course*> *courseList)
{
    if (this->courses != NULL) {
        delete this->courses;
        this->courses = NULL;
    }

    qDebug() << "CourseDetailsWindow::courseListReceived(" << requestId
             << ", " << code << ", size=" << courseList->size() << ")";
    this->courses = courseList;

    this->displayCourseList();
}

void CourseDetailsWindow::displayCourseList()
{

    this->ui->bookList->clear();
    this->ui->courseList->clear();
    this->ui->deleteBookButton->setEnabled(false);

    for (Course *course: *(this->courses)) {
        this->ui->courseList->addItem(course->getCourseCode() + "-"
                                    + course->getCourseName());
    }
}

void CourseDetailsWindow::displayCourseDetails(Course *c)
{
    // Enable course related UI elements
    this->ui->courseCodeEdit->setEnabled(true);
    this->ui->courseNameEdit->setEnabled(true);
    this->ui->saveCourseButton->setEnabled(true);
    this->ui->addBookButton->setEnabled(true);
    this->ui->deleteCourseButton->setEnabled(true);

    this->ui->courseCodeEdit->setText(c->getCourseCode());
    this->ui->courseNameEdit->setText(c->getCourseName());

    // TODO: we should store the most recent requestID to ensure
    // that we are using up to date response data
    this->requestAPI->getBookDetails(c->getRequiredTextIds()); // TODO: use this instead of next block

    /*
    ///////////// TODO: remove this when requests are tested /////////////////
    Textbook *t1 = new Textbook(5, "book 1 name", "1st edition", "jimmy", 34534, true, "12345667");
    Textbook *t2 = new Textbook(8, "second book name", "84sth edition", "william", 363646346346, true, "12345668");
    QList<Textbook*> *bList = new QList<Textbook*>();
    bList->append(t1); bList->append(t2);

    QUuid reqId;
    this->textbookListReceived(reqId, 0, bList);
    //////////////////////////////////////////////////////////////////////////
    */
}

void CourseDetailsWindow::on_backButton_clicked()
{
    this->close();
    emit courseNavigateBack();
}

void CourseDetailsWindow::updateCompleted(QUuid requestId, int code,
                     InvocationDescriptor invo, qint32 id)
{
    qDebug() << "CourseDetailsWindow::updateCompleted! "
             << requestId << " code=" << code;

    this->refreshCourseList();
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
    int courseId = this->getSelectedCourse()->getId();

    emit modifyCourse(courseId, code, name);
}

void CourseDetailsWindow::on_bookList_clicked(const QModelIndex &index)
{
    this->ui->deleteBookButton->setEnabled(true);
}

void CourseDetailsWindow::on_deleteCourseButton_clicked()
{
    int courseId = this->getSelectedCourse()->getId();

    emit deleteCourse(courseId);
}

void CourseDetailsWindow::on_deleteBookButton_clicked()
{
    Course *c = this->getSelectedCourse();
    int courseId = c->getId();

    const QVector<qint32>& requiredBookIds = c->getRequiredTextIds();

    int bookIndex = this->ui->bookList->currentIndex().row();

    emit removeRequiredBook((int)requiredBookIds.at(bookIndex), courseId);
}

void CourseDetailsWindow::on_addBookButton_clicked()
{
    int selectedCourseId = this->getSelectedCourse()->getId();

    this->addReqBooksWin = new AddRequiredBookWindow(this,
                                                     this->requestAPI,
                                                     selectedCourseId);

    connect(this->addReqBooksWin, SIGNAL(addRequiredBooks(QVector<int>&,int)),
            (QObject *)this->manageCourseCtrl, SLOT(addRequiredBooks(QVector<int>&, int)));

    this->addReqBooksWin->setModal(true);

    this->addReqBooksWin->show();
}

void CourseDetailsWindow::on_courseList_currentRowChanged(int currentRow)
{
    // Handle disabling actions that required a selection when the
    // widget loses focus/selection
    if (currentRow < 0) {
        this->ui->deleteCourseButton->setEnabled(false);
        this->ui->saveCourseButton->setEnabled(false);
    }
}

Course* CourseDetailsWindow::getSelectedCourse()
{
    int courseIndex = this->ui->courseList->currentIndex().row();
    return this->courses->at(courseIndex);
}
