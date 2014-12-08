#include "ModifyItemControl.h"

ModifyItemControl::ModifyItemControl(QObject *parent, ContentRequestAPI *api) :
    QObject(parent),
    requestAPI(api)
{
}

void ModifyItemControl::modifyBook(QUuid &reqId,Textbook &modTextbook)
{
    // TODO: make actual request to network
    // reqId = requestAPI->modifyBook(newTextbook);
}

void ModifyItemControl::modifyChapter(QUuid &reqId, int textId,
                                      Chapter &modChapter)
{
    // TODO: make actual request to network
    // reqId = requestAPI->modifyChapter(textId, newChapter);
}

void ModifyItemControl::modifySection(QUuid &reqId, int bookId,
                                      int chapId, Section &modSection)
{
    // TODO: make actual request to network
    // reqId = requestAPI->modifySection(textId, chapId, newSection);
}
