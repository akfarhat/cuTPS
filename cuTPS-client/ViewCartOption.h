// Class: ViewCartOption
// Type: Boundary
// Description:
//     this class provides student users with the option to view/manage their cart
//
// Traceability: ViewCartOption class in the StudentInterface subsystem

#ifndef VIEWCARTOPTION_H
#define VIEWCARTOPTION_H

#include <QWidget>

namespace Ui {
    class ViewCartOption;
}

class ViewCartOption : public QWidget {
    Q_OBJECT

    public:
        explicit ViewCartOption(QWidget *parent = 0);
        ~ViewCartOption();

    private slots:
        void on_viewCartButton_clicked();

    private:
        Ui::ViewCartOption *ui;
};

#endif // VIEWCARTOPTION_H
