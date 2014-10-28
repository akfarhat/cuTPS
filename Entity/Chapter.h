#ifndef CHAPTER_H
#define CHAPTER_H

#include "SellableItem.h"
#include "Textbook.h"

class Chapter: public SellableItem {

    private:
        Textbook* parentTextbook;
        int chNumber;


    public:
        Chapter(Textbook*, int, QString, float);
        ~Chapter();
        Textbook* getParentTextbook();
        int getChapterNumber();

};

#endif // CHAPTER_H
