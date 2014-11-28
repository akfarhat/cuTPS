#ifndef CONTENTMANAGEMENTINTERFACE_H
#define CONTENTMANAGEMENTINTERFACE_H

#include <QDialog>

namespace Ui {
class ContentManagementInterface;
}

class ContentManagementInterface : public QDialog
{
    Q_OBJECT

public:
    explicit ContentManagementInterface(QWidget *parent = 0);
    ~ContentManagementInterface();

private slots:
    void on_addCourseButton_clicked();

    void on_modifyCourseButton_clicked();

    void on_manageContentButton_clicked();

private:
    Ui::ContentManagementInterface *ui;
};

#endif // CONTENTMANAGEMENTINTERFACE_H
