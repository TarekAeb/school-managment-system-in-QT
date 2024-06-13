#ifndef STUDENT_H
#define STUDENT_H
#include"person.h"
#include"course.h"
#include"settingsmanager.h"
#include<QObject>
#include <QWidget>
#include<vector>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QString>
#include<QPixmap>
#include<QPalette>
#include<QDir>
using namespace std;
namespace Ui {
class student;
}

class student : public QWidget,public Person
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = nullptr, const string& ="", const string& ="", const string& ="", const string& ="", const string & ="02/02/00", const string & ="", const vector<Course> & ={},int =0);
    ~student();
    void setCourse(vector<Course>);
    void retrieveCourse(Course);
    vector<Course> getCourses();
    void uploadinformation();
    void loadImages();
private slots:
    void on_toolButton_2_clicked();

private:
    void setMarks(const QString&);
    float getAverage(const float&, const float&, const float&)const;
    string output_course();
    Ui::student *ui;
    vector<Course> course_enrolled;

};

#endif // STUDENT_H
