// Class: AddBookControl
// Type: Control
// Description:
//     This class is responsible for invoking the client
//     side API method in the network handler for sellable
//     items into availability.
// Traceability:
//   AddItemControl class in the ContentManagement subsystem
//   This class is a Control proxy to the ContentRequestAPI.

#ifndef ADDBOOKCONTROL_H
#define ADDBOOKCONTROL_H

#include "Defines.h"
#include "ContentRequestAPI.h"
#include "Entity/Textbook.h"
#include "Entity/Chapter.h"
#include "Entity/Section.h"

class AddBookControl {

    private:
        ContentRequestAPI *network;

    public:
        AddBookControl(ContentRequestAPI *);
        ~AddBookControl();

        // Add the book object to the database through the
        // network handler, return the request identifier
        void addBook(QUuid &, Textbook &);
        void addChapter(QUuid &, int, Chapter &);
        void addSection(QUuid &, int, int, Section &);

};

#endif // ADDBOOKCONTROL_H
