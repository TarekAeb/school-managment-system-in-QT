#ifndef STUDENT_H
#define STUDENT_H
#include<QObject>
#include <QWidget>
#include"person.h"
#include"course.h"
#include"settingsmanager.h"
using namespace std;
namespace Ui {
class student;
}

class student : public QWidget,public Person
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = nullptr, const string& ="", const string& ="", const string& ="", const string& ="", const string & ="02/02/00", const string & ="", const vector<Course> & ={});
    student(const string& ="", const string& ="", const string& ="", const string& ="", const string & ="02/02/00", const string & ="", const vector<Course> & ={});
    ~student();
    void setCourse(vector<Course>);
    void retrieveCourse(Course);
    vector<Course> getCourses();
    void uploadinformation();
private slots:
    void on_toolButton_2_clicked();

private:
    void setMarks(const QString&);
    float getAverage(const float&, const float&, const float&)const;
    string output_course();
    Ui::student *ui;
    vector<Course> course_enrolled;
    QString homepath;
};

#endif // STUDENT_H
