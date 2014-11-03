#ifndef VIEWBOOKDETAILSCONTROL_H
#define VIEWBOOKDETAILSCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"
#include "Entity/Textbook.h"

class ViewBookDetailsControl{

    private:
        ClientNetworkHandler &network;

    public:
        ViewBookDetailsControl(ClientNetworkHandler &);
        ~ViewBookDetailsControl();

        void getBookDetails(QUuid &, Textbook &);
};

#endif // VIEWBOOKDETAILSCONTROL_H
