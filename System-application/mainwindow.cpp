#include "mainwindow.h"
#include "ui_mainwindow.h" // Corrected the include path

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    homePath = SettingsManager::loadSettings();
    loadImages();
}

MainWindow::~MainWindow() {
    delete ui;
    delete adm;
    delete stdn;
    delete tech;
}

void MainWindow::loadImages() {
    QPixmap pix(QDir(homePath + "/assets/").filePath("ensialogo.png"));
    ui->label_2->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));

    QPixmap pix1(QDir(homePath + "/assets/").filePath("hero.png"));
    ui->label_3->setPixmap(pix1.scaled(290, 290));
}

void MainWindow::on_login_button_clicked() {
    QString id = ui->id->text();
    QString password = ui->password->text();

    const QString adminFilePath = QDir(homePath + "/users/").filePath(id+".txt");
    const QString studentFilePath = QDir(homePath + "/users/student/").filePath(id + ".txt");
    const QString teacherFilePath = QDir(homePath + "/users/teacher/").filePath(id + ".txt");

    if (QFile::exists(adminFilePath)) {
        if (authenticateUser(adminFilePath, password)) {
            openAdminWindow(id, "John Doe", id.toStdString(), "0551234567", "john.doe@ensia.edu.dz", "2023-05-01", "securepassword");
            return;
        }
    } else if (QFile::exists(studentFilePath)) {
        if (authenticateUser(studentFilePath, password)) {
            openStudentWindow(id, "John Doe", id.toStdString(), "0551234567", "john.doe@ensia.edu.dz", "2023-05-01", "securepassword", {});
            return;
        }
    } else if (QFile::exists(teacherFilePath)) {
        if (authenticateUser(teacherFilePath, password)) {
            openTeacherWindow(id, "John Doe", id.toStdString(), "0551234567", "john.doe@ensia.edu.dz", "2023-05-01", "securepassword", {});
            return;
        }
    }

    QMessageBox::warning(this, "Error", "Username or password not found");
}



bool MainWindow::authenticateUser(const QString& filePath, const QString& password) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Failed to open file: " + file.errorString());
        return false;
    }

    QTextStream in(&file);
    for (int i = 0; i < 5; ++i) in.readLine(); // Skip first 5 lines
    const QString storedHashedPassword = in.readLine().trimmed();
    // Hash the provided password
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    qDebug()<<"stored password"<<storedHashedPassword;
    qDebug()<<"hashedPassword"<< hashedPassword;

    qDebug()<< (hashedPassword == storedHashedPassword.toUtf8());
    if (hashedPassword == storedHashedPassword.toUtf8()) {
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Incorrect password");
        return false;
    }
}


void MainWindow::openAdminWindow(const QString& id, const std::string& Name, const std::string& Id, const std::string& Phone, const std::string& Email, const std::string& Date, const std::string& Password) {
    adm = new admin(nullptr, Name, Id, Phone, Email, Date, Password);
    adm->show();
    adm->setWindowTitle("ENSIA-Admin Dashboard");
    this->close();
}

void MainWindow::openStudentWindow(const QString& id, const std::string& Name, const std::string& Id, const std::string& Phone, const std::string& Email, const std::string& Date, const std::string& Password, const std::vector<Course>& Courses) {
    stdn = new student(nullptr, Name, Id, Phone, Email, Date, Password, Courses);
    stdn->show();
    stdn->setWindowTitle("ENSIA-Student interface");
    this->close();
}

void MainWindow::openTeacherWindow(const QString& id, const std::string& Name, const std::string& Id, const std::string& Phone, const std::string& Email, const std::string& Date, const std::string& Password, const std::vector<Course>& Courses) {
    tech = new teacher(nullptr, Name, Id, Phone, Email, Date, Password, Courses);
    tech->show();
    tech->setWindowTitle("ENSIA-Teacher interface");
    this->close();
}
