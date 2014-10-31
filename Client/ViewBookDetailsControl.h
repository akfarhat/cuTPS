#ifndef VIEWBOOKDETAILSCONTROL_H
#define VIEWBOOKDETAILSCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"
#include "Entity/Textbook.h"

class ViewBookDetailsControl{

    private:
        ClientNetworkHandler network;

    public:
        ViewBookDetailsControl();
        ~ViewBookDetailsControl();

        void getBookDetails(SessionCredentials *, Textbook *, ServerResponse *);
};

#endif // VIEWBOOKDETAILSCONTROL_H
