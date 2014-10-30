#ifndef CHAPTER_H
#define CHAPTER_H

#include "SellableItem.h"
#include "Textbook.h"
#include <QString>

class Chapter: public SellableItem {

    private:
        Textbook* parentTextbook;
        int number;


    public:
        Chapter();
        Chapter(int, Textbook*, int, QString, float, bool);
        Chapter(Textbook*, int, QString, float);
        ~Chapter();

        Textbook* getParentTextbook();
        void setParentTextbook(Textbook*);

        int getChapterNumber();
        void setChapterNumber(int);

        QString getType();

};

#endif // CHAPTER_H
