#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>

#include "DatabaseManager.h"

#include "Entity/User.h"
#include "Entity/Course.h"
#include "Entity/Textbook.h"
#include "Entity/Order.h"
#include "Entity/Chapter.h"
#include "Entity/Section.h"

class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = 0);

    bool getUser(QString, QString, User&, Role&);

    bool addCourse(Course);
    bool addTextbook(Textbook);
    bool addChapter(Chapter);
    bool addSection(Section);

    bool removeCourse(int);
    bool removeTextbook(int);
    bool removeChapter(int);
    bool removeSection(int);

    bool modifyCourse(Course);
    bool modifyTextbook(Textbook);
    bool modifyChapter(Chapter);
    bool modifySection(Section);

    QVector<int> getRequiredTextbooks(int);
    SellableItem getItemDetails(int);
    Textbook getTextbookDetails(int);
    QVector<SellableItem> getTextbookParts(int);

signals:

public slots:

private:
    DatabaseManager* dbManager;

private:
    bool getUserRole(int, Role&);
};

#endif // STORAGE_H
