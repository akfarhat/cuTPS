#include "ModifyItemControl.h"

ModifyItemControl::ModifyItemControl(QObject *parent, ContentRequestAPI *api) :
    QObject(parent),
    requestAPI(api)
{
}

void ModifyItemControl::modifyBook(QUuid &reqId,Textbook &modTextbook)
{
    reqId = requestAPI->modifyBook(modTextbook);
}

void ModifyItemControl::modifyChapter(QUuid &reqId, int textId,
                                      Chapter &modChapter)
{
    reqId = requestAPI->modifyChapter(textId, modChapter);
}

void ModifyItemControl::modifySection(QUuid &reqId, int textId,
                                      int chapId, Section &modSection)
{
    reqId = requestAPI->modifySection(textId, chapId, modSection);
}
