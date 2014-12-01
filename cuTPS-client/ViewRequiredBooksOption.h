#ifndef VIEWREQUIREDBOOKSOPTION_H
#define VIEWREQUIREDBOOKSOPTION_H

#include <QWidget>

namespace Ui {
    class ViewRequiredBooksOption;
}

class ViewRequiredBooksOption : public QWidget {
    Q_OBJECT

    public:
        explicit ViewRequiredBooksOption(QWidget *parent = 0);
        ~ViewRequiredBooksOption();

    private slots:
        void on_viewBooksButton_clicked();

    private:
        Ui::ViewRequiredBooksOption *ui;
};

#endif // VIEWREQUIREDBOOKSOPTION_H
