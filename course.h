#ifndef COURSE_H
#define COURSE_H


#include <string>
#include <sstream>
#include <ctime>
#include <QDateTime> // Include QDateTime for handling dates and times
#include <QFile>
#include<QTextStream>
#include"settingsmanager.h"

class Course {
public:
    Course(const std::string& name, const std::string& id, const float& midterm, const float& final, const float& cc);
    ~Course();

    void setName(const std::string& name);
    std::string getName() const;

    void setSchedule(const QDateTime& schedule);
    QDateTime getSchedule() const;

    void setMidterm(const float& midterm);
    float getMidterm() const;

    void setFinal(const float& final);
    float getFinal() const;

    void setCc(const float& cc);
    float getCc() const;

    bool operator==(const Course& other) const;

private:
    std::string name;
    QDateTime schedule; // Change type to QDateTime
    float midterm;
    float final;
    float cc;
    QString homepath;
    float validateMark(const float& mark) const;
    void storeInfo(const std::string& id) const;
};

#endif // COURSE_H
