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

        void getRequiredBooks(QUuid &);

};

#endif // VIEWREQUIREDBOOKSCONTROL_H
