#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPixmap>
#include <QMainWindow>
#include <QCryptographicHash>
#include "admin.h"
#include "teacher.h"
#include "student.h"
#include "settingsmanager.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_login_button_clicked();

private:
    Ui::MainWindow *ui;
    admin *adm;
    student *stdn;
    teacher *tech;
    QString homePath;

    bool authenticateUser(const QString& filePath, const QString& password);
    void openAdminWindow(const QString &, const string &, const std::string& , const string &, const string &, const string &, const string &);
    void openStudentWindow(const QString &, const string &, const std::string& , const string &, const string &, const string &, const string &, const std::vector<Course>& );
    void openTeacherWindow(const QString &, const string &, const std::string& , const string &, const string &, const string &, const string &, const std::vector<Course>& );
    void loadImages();
};

#endif // MAINWINDOW_H
