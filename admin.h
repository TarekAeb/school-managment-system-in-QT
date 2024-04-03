#ifndef ADMIN_H
#define ADMIN_H
#include "person.h"
#include"settingsmanager.h"
#include <QWidget>
#include<chrono>
// #include<string>
using std::string;
namespace Ui {
class Admin_dashboard;
}

class admin : public QWidget,public Person
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr, const string &Name="tarek sib", const string &id="1234567891", const string &Phone="0657500473", const string &Email="tarek@ensia.edu.dz", const string& Date="2000-02-02", const string &Password="admin");
    ~admin();

private slots:

    void on_teacheraddbtn_clicked();

    void on_teacherremovebtn_clicked();



    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_5_clicked();

    void on_teacherremovebtn_3_clicked();

    void on_teacheraddbtn_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_7_clicked();

private:
    Ui::Admin_dashboard *ui;
    QString homepath;
    void createCourse(const QString& , const QString& );
};

#endif // ADMIN_H
