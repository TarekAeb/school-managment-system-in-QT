#include "teacher.h"
#include "ui_teacher.h"
#include<QRegularExpression>
#include<QString>
#include<string>
teacher::teacher(QWidget *parent,const string& Name , const string& id,const string& Phone ,const string& Email ,const string& Date ,const string& passwd,const vector<Course>& courses)
    :Person(Name,id,Phone,Email,Date,passwd)
    ,QWidget(parent)
    , ui(new Ui::teacher)
{
    homepath= SettingsManager::loadSettings();
    ui->setupUi(this);
    setCourse(courses);

    QString i=QString::fromStdString(id);
    QString addr= homepath+"/users/teacher/"+i+".txt";
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
        ui->lineEdit_teacher_fullname->setText(fUllname);
        ui->lineEdit_teacher_id->setText(ID);
        ui->lineEdit_teacher_email->setText(EMail);
        ui->lineEdit_teacher_phone->setText(PHone);
        ui->lineEdit_teacher_date->setText(DAte);
        ui->lineEdit_teacher_id_password->setText(ID);

        file.close();

        ui->lineEdit_2->setReadOnly(true);
        ui->lineEdit_3->setReadOnly(true);
        ui->lineEdit_4->setReadOnly(true);
    }
    else{
        QMessageBox::about(parent,"Warning", "A problem just accured! try another time");
        return;
    }
}
teacher::teacher(const string& Name , const string& id,const string& Phone ,const string& Email ,const string& Date ,const string& passwd,const vector<Course>& courses)
    :Person(Name,id,Phone,Email,Date,passwd)
{
    setCourse(courses);
    homepath= SettingsManager::loadSettings();
    uploadinformation();
}
teacher::~teacher()
{
    delete ui;
}
void teacher::setCourse(vector<Course>courses){
    courses_taught=courses;
}

void teacher::uploadinformation(){
    QString nameQ = QString::fromStdString(getName());
    QString idQ = QString::fromStdString(getID());
    QString emailQ = QString::fromStdString(getEmail());
    QString phoneQ = QString::fromStdString(getPhone());
    QString dateOfbirthQ = QString::fromStdString(getDateOfBirth());
    QString passwordQ = QString::fromStdString(getPassword());


    QString addr=homepath+"/users/teacher/"+idQ+".txt";
    qDebug()<<homepath;
    qDebug()<<addr;
    QFile file(addr);
    if (!file.open(QIODevice::WriteOnly)){

        QMessageBox::warning(this,"error","An error occurred: " + file.errorString());
    } else {
        QTextStream out(&file);
        out << nameQ << "\n" << idQ << "\n" << emailQ << "\n" << phoneQ << "\n" << dateOfbirthQ << "\n" << passwordQ << "\n";
        // for (int i = 0; i < courses_taught.size(); i++){
        //     out << courses_taught[i].getName().c_str() << ',';
        // }
        file.close();
    }
}


void teacher::on_toolButton_clicked()
{
    string id= (ui->lineEdit_teacher_id_add->text()).toStdString();
    float CC = setMark(ui->lineEdit_teacher_cc_add->text());
    float Mid= setMark(ui->lineEdit_teacher_midterm_add->text());
    float Final=setMark(ui->lineEdit_teacher_final_add->text());
    string courseName =(ui->lineEdit_teacher_course_add->text()).toStdString();
    if(check(courseName,getID())&&check1(courseName,id)){

        Course cours (courseName,id,Mid,Final,CC);

    }
    else if (check(courseName,getID())&&!check1(courseName,id)){
        QMessageBox::warning(this,"be caution","the id just entered is not enrolled in this course");
    }
    else QMessageBox::warning(this,"be caution","this teacher haven't access to this course");
}

float teacher::setMark(const QString & m){
    return  m.toFloat();
}
bool teacher::check1(const string & courseName,const string & id){
    QString dir =homepath+"/users/student/"+QString::fromStdString(id)+".txt";
    qDebug()<<dir;
    QString coursename=QString::fromStdString(courseName);
    QFile file(dir);
    QTextStream readline(&file);
    int line=1;
    if (file.open(QIODevice::ReadOnly)){

        while(!readline.atEnd()){
            if(line>6){
                if (readline.readLine()==coursename)return true;
            }
            line++;
        }
        // return false;
        file.close();
    }
    else QMessageBox::warning(this,"Sorry","unkown problem accured, try another time.");
    return false;
}

bool teacher::check (const string & courseName,const string & id){
    QString dir =homepath+"/users/teacher/"+QString::fromStdString(id)+".txt";
    qDebug()<<dir;
    QString coursename=QString::fromStdString(courseName);
    QFile file(dir);
    QTextStream readline(&file);
    int line=1;
    if (file.open(QIODevice::ReadOnly)){

        while(!readline.atEnd()){
            if(line>6){
                if (readline.readLine()==coursename)return true;
            }
            line++;
        }
        file.close();
    }
    else QMessageBox::warning(this,"Sorry","unkown problem accured, try another time.");
    return false;

}


void teacher::on_toolButton_2_clicked() {
    QString id = QString::fromStdString(getID());
    QString dir = homepath+"/users/teacher/" + id + ".txt";
    QString oldPass = ui->lineEdit_teacher_oldpassword->text();
    QString newPass = ui->lineEdit_teacher_newpassword->text();

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
                ui->label_wrong_pass->setText("Password updated successfully.");
                return;
            } else {
                ui->label_wrong_pass->setText("Wrong password!");
                return;
            }
        }
        ++line;
    }
    ui->label_wrong_pass->setText("Error: Password wrong.");
}
