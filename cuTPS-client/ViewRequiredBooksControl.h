// Class: ViewRequiredBooksControl
// Type: Control
// Description:
//     This class is responsible for invoking the client
//     side API method in the network handler for requesting
//     the list of available books for the current user

#ifndef VIEWREQUIREDBOOKSCONTROL_H
#define VIEWREQUIREDBOOKSCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"

class ViewRequiredBooksControl {

    private:
        ClientNetworkHandler &network;

    public:
        ViewRequiredBooksControl(ClientNetworkHandler &);
        ~ViewRequiredBooksControl();

        // Get the list of required books for this user,
        // store the request identifier
        void getRequiredBooks(QUuid &, QString&);

};

#endif // VIEWREQUIREDBOOKSCONTROL_H
