#ifndef VIEWREQUIREDBOOKSCONTROL_H
#define VIEWREQUIREDBOOKSCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"

class ViewRequiredBooksControl {

    private:
        ClientNetworkHandler network;

    public:
        ViewRequiredBooksControl();
        ~ViewRequiredBooksControl();

        void getRequiredBooks(SessionCredentials *, ServerResponse *);

};

#endif // VIEWREQUIREDBOOKSCONTROL_H
