// Class: AddBookControl
// Type: Control
// Description:
//     This class is responsible for invoking the client
//     side API method in the network handler for adding
//     a book into availability.

#ifndef ADDBOOKCONTROL_H
#define ADDBOOKCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"
#include "Entity/Textbook.h"

class AddBookControl {

    private:
        ClientNetworkHandler &network;

    public:
        AddBookControl(ClientNetworkHandler &);
        ~AddBookControl();

        // Add the book object to the database through the
        // network handler, return the request identifier
        void addBook(QUuid &, Textbook &);

};

#endif // ADDBOOKCONTROL_H
