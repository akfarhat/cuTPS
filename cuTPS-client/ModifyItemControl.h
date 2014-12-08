// traceability:
//   ModifyItemControl class in the ContentManagement subsystem

#ifndef MODIFYITEMCONTROL_H
#define MODIFYITEMCONTROL_H

#include <QObject>

#include "ContentRequestAPI.h"

class ModifyItemControl : public QObject
{
    Q_OBJECT
public:
    explicit ModifyItemControl(QObject *parent = 0,
                               ContentRequestAPI *api = NULL);
    void modifyBook(QUuid &reqId, Textbook &modTextbook);
    void modifyChapter(QUuid &reqId, int textId,
                                          Chapter &modChapter);
    void modifySection(QUuid &reqId, int bookId,
                                          int chapId, Section &modSection);

signals:

public slots:

private:
    ContentRequestAPI *requestAPI;

};

#endif // MODIFYITEMCONTROL_H
