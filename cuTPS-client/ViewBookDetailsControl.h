// Class: ViewBookDetailsControl
// Type: Control
// Description:
//     This class is responsible for invoking the client
//     side API method in the network handler for requesting
//     the details of a specific book

#ifndef VIEWBOOKDETAILSCONTROL_H
#define VIEWBOOKDETAILSCONTROL_H

#include "Defines.h"
#include "ClientNetworkHandler.h"
#include "Entity/Textbook.h"

class ViewBookDetailsControl{

    private:
        ClientNetworkHandler &network;

    public:
        ViewBookDetailsControl(ClientNetworkHandler &);
        ~ViewBookDetailsControl();

        // Request details for the book provided, store the
        // request identifier
        void getBookDetails(QUuid &, int);
};

#endif // VIEWBOOKDETAILSCONTROL_H
