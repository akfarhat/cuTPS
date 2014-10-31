#ifndef ADDBOOKCONTROL_H
#define ADDBOOKCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"
#include "Entity/Textbook.h"


class AddBookControl {

    private:
        ClientNetworkHandler network;

    public:
        AddBookControl();
        ~AddBookControl();

        void addBook(SessionCredentials *, Textbook *, ServerResponse *);

};

#endif // ADDBOOKCONTROL_H
