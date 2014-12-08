// Traceability:
//   DeleteItemControl class in the ContentManagement subsystem

#ifndef DELETEITEMCONTROL_H
#define DELETEITEMCONTROL_H

#include "ContentRequestAPI.h"

#include <QObject>

class DeleteItemControl : public QObject
{
    Q_OBJECT
public:
    explicit DeleteItemControl(QObject *parent = 0, ContentRequestAPI *api = NULL);
    void deleteItem(QUuid&, int);

signals:

public slots:

private:
    ContentRequestAPI *requestAPI;

};

#endif // DELETEITEMCONTROL_H
