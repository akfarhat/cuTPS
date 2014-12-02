#include "AddCourseTask.h"
#include "TPSNetUtils.h"

#include <QDebug>

AddCourseTask::AddCourseTask(Server* srv)
    : WorkerTask(srv)
{
}

void AddCourseTask::run()
{
    qDebug() << "Add course task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    Course course;

    QDataStream in(iblock, QIODevice::ReadOnly);

    qDebug() << "TPSAddCourseTask about to deserialize";

    TPSNetUtils::DeserializeCourse(&course, &in);

    qDebug() << "TPSAddCourseTask deserialized course:";
    qDebug() << " courseCode = " << course.getCourseCode();
    qDebug() << " course name = " << course.getCourseName();
    qDebug() << " id = " << QString::number(course.getId());

    qDebug() << "TPSAddCourseTask calling server addCourse API";

    ServerResponse r = server->addCourse(sessionId, course);

    qDebug() << "TPSAddCourseTask finished server API call";

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    qDebug() << "TPSAddCourseTask setting up response packet";

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    qDebug() << "TPSAddCourseTask emitting result";

    emit result(response.responseCode, oblock);
}


