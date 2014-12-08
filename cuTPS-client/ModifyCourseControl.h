#ifndef MODIFYCOURSECONTROL_H
#define MODIFYCOURSECONTROL_H

#include <QObject>

#include "CourseRequestAPI.h"

class ModifyCourseControl : public QObject
{
    Q_OBJECT

public:
    ModifyCourseControl(CourseRequestAPI *);
    void modifyCourse(QUuid &, Course &);

private:
    CourseRequestAPI *requestAPI;
};

#endif // MODIFYCOURSECONTROL_H
