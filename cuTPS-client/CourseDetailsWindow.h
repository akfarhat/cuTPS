// Traceability:
//   CourseDetailsWindow class
//   in the CourseManagement subsystem

#ifndef COURSEDETAILSWINDOW_H
#define COURSEDETAILSWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

#include "CourseRequestAPI.h"
#include "AddCourseWindow.h"
#include "AddRequiredBookWindow.h"

// Forward reference to avoid circular deps
class ManageCourseControl;

namespace Ui {
class CourseDetailsWindow;
}

class CourseDetailsWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void courseNavigateBack();
    void modifyCourse(int, QString, QString);
    void deleteCourse(int);
    void removeRequiredBook(int, int);

public:
    explicit CourseDetailsWindow(QWidget *parent = 0,
                                 ManageCourseControl *ctrl = NULL,
                                 CourseRequestAPI *api = NULL);
    ~CourseDetailsWindow();

    void refreshCourseList();

public slots:
    // server responses with requested data
    void textbookListReceived(QUuid requestId, int code, QList<Textbook*>*);
    void courseListReceived(QUuid requestId, int code, QList<Course*>*);
    void updateCompleted(QUuid requestId, int code,
                         InvocationDescriptor invo, qint32 id);


private slots:
    void on_backButton_clicked();

    void on_courseList_clicked(const QModelIndex &index);

    void on_addCourseButton_clicked();

    void on_saveCourseButton_clicked();

    void on_bookList_clicked(const QModelIndex &index);

    void on_deleteCourseButton_clicked();

    void on_deleteBookButton_clicked();

    void on_addBookButton_clicked();

    void on_courseList_currentRowChanged(int currentRow);

private:
    Ui::CourseDetailsWindow *ui;
    ManageCourseControl *manageCourseCtrl;
    CourseRequestAPI *requestAPI;
    AddCourseWindow *addCourseWin;
    AddRequiredBookWindow *addReqBooksWin;

    QList<Course*> *courses;

    void displayCourseDetails(Course *);
    Course *getSelectedCourse();
    void displayCourseList();
};

#endif // COURSEDETAILSWINDOW_H
