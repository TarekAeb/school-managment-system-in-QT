#ifndef TEACHER_H
#define TEACHER_H
#include"person.h"
#include <QWidget>
#include"course.h"
#include<QDir>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<string>
#include"settingsmanager.h"

using namespace std;
namespace Ui {
class teacher;
}

class teacher : public QWidget, public Person
{
    Q_OBJECT

public:
    explicit teacher(QWidget *parent = nullptr, const string&  ="", const string&  ="", const string&  ="", const string&  ="", const string&  ="02/02/00", const string & ="", const vector<Course>& ={});
    teacher(const string&  ="", const string&  ="", const string&  ="", const string&  ="", const string&  ="02/02/00", const string & ="", const vector<Course>& ={});
    ~teacher();

    void setCourse(vector<Course>);
    void uploadinformation();
private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::teacher *ui ;
    vector<Course> courses_taught;
    float setMark(const QString &);
    bool check(const string &,const string& );
    bool check1(const string &,const string& );
    QString homepath;
};

#endif // TEACHER_H
