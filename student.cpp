#include "student.h"
#include "ui_student.h"
#include<vector>
#include<QFile>
#include<QTextStream>
#include"settingsmanager.h"
#include<QMessageBox>
#include<QString>
#include<QPixmap>
#include<QPalette>
student::student(QWidget *parent, const string &Name, const string &id, const string &Phone, const string &Email, const string &date,const string& passwd,const vector<Course> &courses) : Person(Name, id, Phone, Email, date,passwd)
    , QWidget(parent)
    , ui(new Ui::student)
{
    homepath=SettingsManager::loadSettings();
    ui->setupUi(this);
    setCourse(courses);
    QString i=QString::fromStdString(id);

    QString addr= homepath+"/users/student/"+i+".txt";
    QFile file(addr);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QString fUllname;
        QString ID;
        QString DAte;
        QString PHone;
        QString EMail;
        // QString Year;
        int line=1;
        QTextStream readfile(&file);
        while(line<6){
            switch (line) {
            case 1:
                fUllname=readfile.readLine();
                line++;
                break;
            case 2:
                ID=readfile.readLine();
                line++;
            case 3:
                EMail=readfile.readLine();
                line++;
            case 4:
                PHone=readfile.readLine();
                line++;
            case 5:
                DAte=readfile.readLine();
                line++;
            default:
                break;
            }
        }
        ui->lineEdit_student_fullname->setText(fUllname);
        ui->lineEdit_student_id->setText(ID);
        ui->lineEdit_student_email->setText(EMail);
        ui->lineEdit_student_phone->setText(PHone);
        ui->lineEdit_student_date->setText(DAte);
        ui->lineEdit_student_id_password->setText(ID);
        setMarks(ID);

        file.close();

        ui->lineEdit_6->setReadOnly(true);
        ui->lineEdit_7->setReadOnly(true);
        ui->lineEdit_18->setReadOnly(true);
        ui->lineEdit_23->setReadOnly(true);
        ui->lineEdit_25->setReadOnly(true);
        ui->lineEdit_36->setReadOnly(true);
        ui->lineEdit_average_1->setReadOnly(true);
        ui->lineEdit_average_2->setReadOnly(true);
        ui->lineEdit_average_3->setReadOnly(true);
        ui->lineEdit_average_4->setReadOnly(true);
        ui->lineEdit_average_5->setReadOnly(true);
        ui->lineEdit_average_6->setReadOnly(true);
        ui->lineEdit_cc_1->setReadOnly(true);
        ui->lineEdit_cc_2->setReadOnly(true);
        ui->lineEdit_cc_3->setReadOnly(true);
        ui->lineEdit_cc_4->setReadOnly(true);
        ui->lineEdit_cc_5->setReadOnly(true);
        ui->lineEdit_cc_6->setReadOnly(true);
        ui->lineEdit_finalexam_1->setReadOnly(true);
        ui->lineEdit_finalexam_2->setReadOnly(true);
        ui->lineEdit_finalexam_3->setReadOnly(true);
        ui->lineEdit_finalexam_4->setReadOnly(true);
        ui->lineEdit_finalexam_5->setReadOnly(true);
        ui->lineEdit_finalexam_6->setReadOnly(true);
        ui->lineEdit_midterm_1->setReadOnly(true);
        ui->lineEdit_midterm_2->setReadOnly(true);
        ui->lineEdit_midterm_3->setReadOnly(true);
        ui->lineEdit_midterm_4->setReadOnly(true);
        ui->lineEdit_midterm_5->setReadOnly(true);
        ui->lineEdit_midterm_6->setReadOnly(true);
        ui->lineEdit_name_1->setReadOnly(true);
        ui->lineEdit_name_2->setReadOnly(true);
        ui->lineEdit_name_3->setReadOnly(true);
        ui->lineEdit_name_4->setReadOnly(true);
        ui->lineEdit_name_5->setReadOnly(true);
        ui->lineEdit_name_6->setReadOnly(true);
        ui->lineEdit_student_date->setReadOnly(true);
        ui->lineEdit_student_email->setReadOnly(true);
        ui->lineEdit_student_fullname->setReadOnly(true);
        ui->lineEdit_student_id->setReadOnly(true);
        ui->lineEdit_student_phone->setReadOnly(true);
        ui->lineEdit_student_year->setReadOnly(true);
    }
    else{
        QMessageBox::about(parent,"Warning", "A problem just accured! try another time");
        return;
    }

    ui->widget->setStyleSheet("background-image: url(:homepath+/assets/calender.jpg);");

}

student::student(const string& Name , const string& id,const string& Phone ,const string& Email ,const string& Date ,const string& passwd,const vector<Course>& courses)
    :Person(Name,id,Phone,Email,Date,passwd)
{
    setCourse(courses);
    homepath=SettingsManager::loadSettings();
    uploadinformation();
}
void student::uploadinformation(){
    QString nameQ = QString::fromStdString(getName());
    QString idQ = QString::fromStdString(getID());
    QString emailQ = QString::fromStdString(getEmail());
    QString phoneQ = QString::fromStdString(getPhone());
    QString dateOfbirthQ = QString::fromStdString(getDateOfBirth());
    QString passwordQ = QString::fromStdString(getPassword());


    QString addr= homepath+"/users/student/"+idQ+".txt";
    QFile file(addr);
    if (!file.open(QIODevice::WriteOnly)){

        QMessageBox::warning(this,"error","An error occurred: " + file.errorString());
    } else {
        QTextStream out(&file);
        out << nameQ << "\n" << idQ << "\n" << emailQ << "\n" << phoneQ << "\n" << dateOfbirthQ << "\n" << passwordQ << "\n";
        // for (int i = 0; i < course_enrolled.size(); i++){
        //     out << course_enrolled[i].getName().c_str() << ',';
        // }
        file.close();
    }
    qDebug()<<"from student";
}

student::~student()
{
    delete ui;
}
void student::setCourse(vector<Course> courses)
{
    course_enrolled=courses;

}
string student::output_course( ) {
    return getName();
}


vector<Course> student::getCourses() { return course_enrolled; }

float student::getAverage(const float& midterm, const float& final, const float& cc)const{
    return (midterm*2+final*3+cc)/6;
}

void student::setMarks(const QString &id) {
    QString dir = homepath+"/users/student/" + id + ".txt";
    QFile file(dir);
    QTextStream readline(&file);
    if (file.open(QIODevice::ReadOnly)) {
        int line = 1;
        int n = 1;
        while (!readline.atEnd()) {
            if (line > 6) {
                QString coursename = readline.readLine();
                QString course_dir = homepath+"/courses/" + coursename + ".txt";
                QFile coursefile(course_dir);
                int c_line = 1;
                QTextStream readline1(&coursefile);
                if (coursefile.open(QIODevice::ReadOnly)) {

                    while (!readline1.atEnd()) {
                        QString content = readline1.readLine();
                        QStringList parts = content.split(' ');
                        if (parts.size() == 4) {
                            QString courseID = parts[0].trimmed();
                            if (courseID == id) {
                                QString coursemidterm = parts[1].trimmed();
                                QString coursefinal = parts[2].trimmed();
                                QString courseccmark = parts[3].trimmed();
                                float mid=coursemidterm.toFloat();
                                float final=coursefinal.toFloat();
                                float Cc=courseccmark.toFloat();
                                float average = getAverage(mid,final,Cc);
                                QString aver = QString::number(average);
                                switch(n){
                                case 1 :
                                    ui->lineEdit_name_1->setText(coursename);
                                    ui->lineEdit_midterm_1->setText(coursemidterm);
                                    ui->lineEdit_finalexam_1->setText(coursefinal);
                                    ui->lineEdit_cc_1->setText(courseccmark);
                                    ui->lineEdit_average_1->setText(aver);
                                    break;
                                case 2 :
                                    ui->lineEdit_name_2->setText(coursename);
                                    ui->lineEdit_midterm_2->setText(coursemidterm);
                                    ui->lineEdit_finalexam_2->setText(coursefinal);
                                    ui->lineEdit_cc_2->setText(courseccmark);
                                    ui->lineEdit_average_2->setText(aver);
                                    break;
                                case 3 :
                                    ui->lineEdit_name_3->setText(coursename);
                                    ui->lineEdit_midterm_3->setText(coursemidterm);
                                    ui->lineEdit_finalexam_3->setText(coursefinal);
                                    ui->lineEdit_cc_3->setText(courseccmark);
                                    ui->lineEdit_average_3->setText(aver);
                                    break;
                                case 4 :
                                    ui->lineEdit_name_4->setText(coursename);
                                    ui->lineEdit_midterm_4->setText(coursemidterm);
                                    ui->lineEdit_finalexam_4->setText(coursefinal);
                                    ui->lineEdit_cc_4->setText(courseccmark);
                                    ui->lineEdit_average_4->setText(aver);
                                    break;
                                case 5 :
                                    ui->lineEdit_name_5->setText(coursename);
                                    ui->lineEdit_midterm_5->setText(coursemidterm);
                                    ui->lineEdit_finalexam_5->setText(coursefinal);
                                    ui->lineEdit_cc_5->setText(courseccmark);
                                    ui->lineEdit_average_5->setText(aver);
                                    break;
                                case 6 :
                                    ui->lineEdit_name_6->setText(coursename);
                                    ui->lineEdit_midterm_6->setText(coursemidterm);
                                    ui->lineEdit_finalexam_6->setText(coursefinal);
                                    ui->lineEdit_cc_6->setText(courseccmark);
                                    ui->lineEdit_average_6->setText(aver);
                                    break;
                                default:
                                    break;
                                }
                                n++;
                                break;
                            }
                        }
                        c_line++;
                    }
                    coursefile.close();
                }
            }
            line++;
        }
        file.close();
    }
    else{
        QMessageBox::warning(this,"error","A problem just accured");
    }
}

void student::on_toolButton_2_clicked() {
    QString id = QString::fromStdString(getID());
    QString dir = homepath+"/users/student/" + id + ".txt";
    QString oldPass = ui->lineEdit_student_oldpassword->text();
    QString newPass = ui->lineEdit_student_newpassword->text();

    QFile file(dir);
    if (!file.open(QIODevice::ReadOnly)) {
        ui->label_wrong_pass->setText("Error: Could not open file.");
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    QStringList lines = fileContent.split("\n");
    file.close();

    int line = 1;
    foreach(const QString &lineContent, lines) {
        if (line == 6) {
            if (oldPass == lineContent.trimmed()) {
                lines[line - 1] = newPass;
                if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                    ui->label_wrong_pass->setText("Error: Could not open file for writing.");
                    return;
                }
                QTextStream out(&file);
                out << lines.join("\n");
                file.close();
                QMessageBox::information(this,"Password changed","Password updated successfully.");
                return;
            } else {
                ui->label_wrong_pass->setText("Wrong password!");
                return;
            }
        }
        ++line;
    }
    ui->label_wrong_pass->setText("Error: Password not found in file.");
}

