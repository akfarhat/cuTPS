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

        void addBook(QUuid &, Textbook &);

};

#endif // ADDBOOKCONTROL_H
