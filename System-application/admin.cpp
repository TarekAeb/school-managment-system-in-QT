#include "admin.h"
#include "ui_admin.h"
#include<QDir>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include"teacher.h"
#include"student.h"
#include"course.h"
#include<vector>
#include<QCryptographicHash>
#include<QByteArray>
#include"mainwindow.h"
using namespace std;
admin::admin(QWidget *parent,const string &Name, const string &id, const string &Phone, const string &Email,const string& Date,const string& Password)
    : QWidget(parent)
    , ui(new Ui::Admin_dashboard),Person(Name,id,Phone,Email,Date,Password)
{
    ui->setupUi(this);
    homepath=SettingsManager::loadSettings();
    QString dir=homepath+"/users/"+QString::fromStdString(id)+".txt";
    QFile file(dir);
    if (file.open(QIODevice::ReadOnly)){
        QTextStream readfile(&file);
        QString fUllname;
        QString ID;
        QString DAte;
        QString PHone;
        QString EMail;
        int line=1;
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
        ui->lineEdit_admin_fullname->setText(fUllname);
        ui->lineEdit_admin_id->setText(ID);
        ui->lineEdit_admin_email->setText(EMail);
        ui->lineEdit_admin_phone->setText(PHone);
        ui->lineEdit_admin_date->setText(DAte);
        ui->lineEdit_admin_id_update->setText(ID);
        ui->lineEdit_admin_id_update->setReadOnly(true);
        file.close();
    }
    else{
        QMessageBox::warning(this,"Error","A problem just accured, try again!");
    }
}

admin::~admin()
{
    delete ui;

}



// add teacher
void admin::on_teacheraddbtn_clicked()
{
    QString nameQ = ui->lineEdit_teacher_name->text();
    QString idQ = ui->lineEdit_teacher_id->text();
    QString dateQ = ui->lineEdit_teacher_date->text();
    QString emailQ = ui->lineEdit_teacher_email->text();
    QString phoneQ = ui->lineEdit_teacher_phone->text();
    QString passwordQ=ui->lineEdit_teacher_password->text();


    vector<Course> cours;

    std::string name = nameQ.toStdString();
    std::string id = idQ.toStdString();
    std::string date = dateQ.toStdString();
    std::string email = emailQ.toStdString();
    std::string phone = phoneQ.toStdString();
    std::string password =passwordQ.toStdString();
    try{teacher teach(nullptr,name, id, phone, email, date,password, cours,1);}
    catch(invalid_argument &e){QMessageBox::warning(this,"Warning",e.what());return;}

    ui->lineEdit_teacher_name->clear();
    ui->lineEdit_teacher_id->clear();
    ui->lineEdit_teacher_date->clear();
    ui->lineEdit_teacher_email->clear();
    ui->lineEdit_teacher_phone->clear();
    ui->lineEdit_teacher_password->clear();

}
// remove teacher
void admin::on_teacherremovebtn_clicked()
{
    QString idQ=ui->lineEdit_teacher_id_remove->text();
    ui->lineEdit_teacher_id_remove->clear();
    QString addr=homepath+"/users/teacher/"+idQ+".txt";
    QFile file(addr);
    try{
        if(file.exists()){
            file.remove();
        }
        else{
            throw   invalid_argument("no such teacher with this id");
        }
    }

    catch(invalid_argument){
        QMessageBox::warning(this,"Warning","No such teacher with this id, check the id.");
    }
}
// remove Course from teacher
void admin::on_toolButton_2_clicked()
{
    QString idQ = ui->lineEdit_teacher_id_add->text();
    QString cours = ui->lineEdit_teacher_course_add->text();
    ui->lineEdit_teacher_id_add->clear();
    ui->lineEdit_teacher_course_add->clear();
    QString addr = homepath+"/users/teacher/" + idQ + ".txt";
    QFile file(addr);
    if (!file.exists()) {
        QMessageBox::warning(this, "Warning", "No such teacher with this id, check the id.");
        return;
    } else {
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QMessageBox::warning(this, "Warning", "Unable to open file.");
            return;
        }
        QTextStream in(&file);
        QStringList lines;
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }
        file.close();
        for (int i = 0; i < lines.size(); ++i) {
            if (lines[i] == cours) {
                lines.removeAt(i);
                break;
            }
        }
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Warning", "Unable to open file.");
            return;
        }
        QTextStream out(&file);
        for (const QString &line : lines) {
            out << line << "\n";
        }
        file.close();
    }
}
//add course to teacher file
void admin::on_toolButton_clicked()
{
    QString idQ=ui->lineEdit_teacher_id_add->text();
    QString cours=ui->lineEdit_teacher_course_add->text();
    ui->lineEdit_teacher_id_add->clear();
    ui->lineEdit_teacher_course_add->clear();
    QString addr=homepath+"/users/teacher/"+idQ+".txt";
    QFile file(addr);
    try{
        if(!file.exists()|| !file.open(QIODevice::Append | QIODevice::Text)){
            QMessageBox::warning(this,"Warning","No such teacher with this id, check the id.");
            return;
        }
        else{
            file.open(QIODevice::Append | QIODevice::Text);
            QTextStream out(&file);
            out << cours << "\n";
            file.close();
        }
    }

    catch(invalid_argument){
        QMessageBox::warning(this,"Warning","No such teacher with this id, check the id.");
    }
}


// add course to student
void admin::on_toolButton_6_clicked()
{
    QString idQ=ui->lineEdit_student_id_add->text();
    QString cours=ui->lineEdit_student_course_add->text();
    ui->lineEdit_student_id_add->clear();
    ui->lineEdit_student_course_add->clear();
    QString addr=homepath+"/users/student/"+idQ+".txt";
    QFile file(addr);
    try{
        if(!file.exists()|| !file.open(QIODevice::Append | QIODevice::Text)){
            QMessageBox::warning(this,"Warning","No such student with this id, check the id.");
            return;
        }
        else{
            file.open(QIODevice::Append | QIODevice::Text);
            QTextStream out(&file);
            out << cours << "\n";
            file.close();
        }
    }

    catch(invalid_argument){
        QMessageBox::warning(this,"Warning","No such student with this id, check the id.");
    }
}
// function to remove a course to a student
void admin::on_toolButton_5_clicked()
{
    QString idQ = ui->lineEdit_student_id_add->text();
    QString cours = ui->lineEdit_student_course_add->text();
    ui->lineEdit_student_id_add->clear();
    ui->lineEdit_student_course_add->clear();
    QString addr = homepath+"/users/student/" + idQ + ".txt";
    QFile file(addr);
    if (!file.exists()) {
        QMessageBox::warning(this, "Warning", "No such student with this id, check the id.");
        return;
    } else {
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QMessageBox::warning(this, "Warning", "Unable to find user.");
            return;
        }
        QTextStream in(&file);
        QStringList lines;
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }
        file.close();
        for (int i = 0; i < lines.size(); ++i) {
            if (lines[i] == cours) {
                lines.removeAt(i);
                break;
            }
        }
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Warning", "Unable to open file.");
            return;
        }
        QTextStream out(&file);
        for (const QString &line : lines) {
            out << line << "\n";
        }
        file.close();
    }
}
//remove student
void admin::on_teacherremovebtn_3_clicked()
{
    QString idQ=ui->lineEdit_student_id_remove->text();
    ui->lineEdit_student_id_remove->clear();
    QString addr=homepath+"/users/student/"+idQ+".txt";
    QFile file(addr);
    try{
        if(file.exists()){
            file.remove();
        }
        else{
            throw   invalid_argument("no such student with this id");
        }
    }

    catch(invalid_argument){
        QMessageBox::warning(this,"Warning","No such student with this id, check the id.");
    }
}
//add student
void admin::on_teacheraddbtn_3_clicked()
{
    QString nameQ = ui->lineEdit_student_name->text();
    QString idQ = ui->lineEdit_student_id->text();
    QString dateQ = ui->lineEdit_student_date->text();
    QString emailQ = ui->lineEdit_student_email->text();
    QString phoneQ = ui->lineEdit_student_phone->text();
    QString passwordQ=ui->lineEdit_student_password->text();

    ui->lineEdit_student_name->clear();
    ui->lineEdit_student_id->clear();
    ui->lineEdit_student_date->clear();
    ui->lineEdit_student_email->clear();
    ui->lineEdit_student_phone->clear();
    ui->lineEdit_student_password->clear();

    vector<Course> cours;

    std::string name = nameQ.toStdString();
    std::string id = idQ.toStdString();
    std::string date = dateQ.toStdString();
    std::string email = emailQ.toStdString();
    std::string phone = phoneQ.toStdString();
    std::string password =passwordQ.toStdString();
    try{student stdn(nullptr,name, id, phone, email, date,password, cours,1);}
    catch(invalid_argument){QMessageBox::warning(this,"Warning","this informations doen't much our credentials");}
}


void admin::on_toolButton_4_clicked() {
    QString courseName = ui->lineEdit_course_add->text();
    QString schedule = ui->lineEdit_schedule->text(); // Assuming you have a QLineEdit for entering the schedule

    createCourse(courseName, schedule);
}

void admin::on_toolButton_3_clicked() {
    QString courseName = ui->lineEdit_course_add->text();
    QString dir = homepath + "/courses/" + courseName + ".txt";
    QFile file(dir);

    if (file.exists()) {
        if (file.remove()) {
            QMessageBox::information(this, "Success", "Course removed successfully!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to remove the course. Please make sure the file is not being used by another process or run the program with appropriate permissions.");
        }
    } else {
        QMessageBox::warning(this, "Warning", "Course with this name does not exist!");
    }
}

void admin::createCourse(const QString& courseName, const QString& schedule) {
    QString dir = homepath + "/courses/" + courseName + ".txt";
    QFile file(dir);

    if (file.exists()) {
        QMessageBox::warning(this, "Warning", "A course with this name already exists!");
    } else {
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << courseName << ' ' << schedule << "\n";
            file.close();
            QMessageBox::information(this, "Success", "Course created successfully!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to create the course. Please make sure no course with the same name exists or run the program with appropriate permissions.");
        }
    }
}



void admin::on_toolButton_7_clicked()
{
    QString newName = ui->lineEdit_admin_name_update->text();
    QString newEmail = ui->lineEdit_admin_email_update->text();
    QString newPassword = ui->lineEdit_admin_newpassword->text();
    QString newPhone = ui->lineEdit_admin_phone_update->text();
    QString newDate = ui->lineEdit_admin_date_update->text();
    QString oldPassword = ui->lineEdit_admin_oldpassword->text();
    QByteArray hashedPassword = QCryptographicHash::hash(oldPassword.toUtf8(), QCryptographicHash::Sha256).toHex();

    qDebug()<<"hashed password:"<<hashedPassword;

    QString adminFilePath = homepath + "/users/"+QString::fromStdString(getID())+".txt";
    QFile file(adminFilePath);

    // Open the file in ReadWrite mode
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&file);

        // Read existing admin information
        for (int i = 0; i < 5; ++i) in.readLine(); // Skip first 5 lines
        const QString storedHashedPassword = in.readLine().trimmed();
        qDebug()<<"stored hashed password"<<storedHashedPassword;
        // Check if the old password matches the existing password
        if (storedHashedPassword.toUtf8() == hashedPassword) {
            try{
                setName(newName.toStdString());
                setEmail(newEmail.toStdString());
                setPhone(newPhone.toStdString());
                setDateOfBirth(newDate.toStdString());
                setPassword(newPassword.toStdString());
                uploadinformation();
                MainWindow *i= new MainWindow(nullptr);
                i->show();
                this->close();
            }
            catch(invalid_argument& e){
                QMessageBox::warning(nullptr,"Warning",e.what());
                return;
            }
            QMessageBox::information(this, "Success", "Admin information updated successfully!");
        } else {
            ui->label_wrong_pass->setText("Old password does not match!");
        }

        file.close();
    } else {
        QMessageBox::critical(this, "Error", "Failed to open admin file for updating!");
    }
}
void admin::uploadinformation(){
    QString nameQ = QString::fromStdString(getName());
    QString idQ = QString::fromStdString(getID());
    QString emailQ = QString::fromStdString(getEmail());
    QString phoneQ = QString::fromStdString(getPhone());
    QString dateOfbirthQ = QString::fromStdString(getDateOfBirth());
    QString passwordQ = QString::fromStdString(getPassword());


    QString addr= homepath+"/users/"+idQ+".txt";
    QFile file(addr);
    if (!file.open(QIODevice::WriteOnly)){

        QMessageBox::warning(this,"error","An error occurred: " + file.errorString());
    } else {
        QTextStream out(&file);
        out << nameQ << "\n" << idQ << "\n" << emailQ << "\n" << phoneQ << "\n" << dateOfbirthQ << "\n" << passwordQ << "\n";
        file.close();
    }
}

