#include "course.h"

Course::Course(const std::string& name, const std::string&id, const float& midterm, const float& final, const float& cc)
    : name(name), schedule(schedule), midterm(validateMark(midterm)), final(validateMark(final)), cc(validateMark(cc)) {
    homepath=SettingsManager::loadSettings();
    storeInfo(id);
}

Course::~Course() {}

void Course::setName(const std::string& name) {
    this->name = name;
}

std::string Course::getName() const {
    return name;
}

void Course::setSchedule(const QDateTime& schedule) {
    this->schedule = schedule;
}

QDateTime Course::getSchedule() const {
    return schedule;
}

void Course::setMidterm(const float& midterm) {
    this->midterm = validateMark(midterm);
}

float Course::getMidterm() const {
    return midterm;
}

void Course::setFinal(const float& final) {
    this->final = validateMark(final);
}

float Course::getFinal() const {
    return final;
}

void Course::setCc(const float& cc) {
    this->cc = validateMark(cc);
}

float Course::getCc() const {
    return cc;
}

bool Course::operator==(const Course& other) const {
    return (name == other.name && schedule == other.schedule && midterm == other.midterm && final == other.final && cc == other.cc);
}

float Course::validateMark(const float& mark) const {
    if ((mark < 0.0 )|| (mark > 20.0)) {
        throw std::invalid_argument("Invalid mark value. Marks must be between 0 and 20.");
    }
    return mark;
}

void Course::storeInfo(const std::string &id) const{
    QString i = QString::fromStdString(id);
    QString dir = homepath+"/courses/" + QString::fromStdString(name) + ".txt";
    QFile file(dir);
    QString courseMid = QString::number(midterm, 'f', 2);
    QString courseFinal = QString::number(final, 'f', 2);
    QString courseCc = QString::number(cc, 'f', 2);

    QStringList lines;

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString content = in.readLine();
            QStringList parts = content.split(' ');
            if (parts.size() == 4) {
                QString studentId = parts[0].trimmed();
                if (studentId == i) {
                    continue;
                }
            }
            lines.append(content);
        }
        file.close();
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString &line : lines) {
            out << line << "\n";
        }

        out << i << ' ' << courseMid << ' ' << courseFinal << ' ' << courseCc << "\n";
        file.close();
    }
}
