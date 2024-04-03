#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include <QSysInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "pathselectiondialog.h"
#include "mainwindow.h"

QString createFoldersAndFile(const QString &selectedPath) {
    // Set base folder path
    QString baseFolderPath = selectedPath + "/StudentManagement";


    // Create the base folder
    QDir baseDir(baseFolderPath);
    if (!baseDir.exists()) {
        baseDir.mkpath(".");
    }

    // Create subfolders
    QStringList subfolders;
    subfolders << "users/student" << "users/teacher" << "courses" << "assets";

    foreach (const QString &folder, subfolders) {
        QDir subDir(baseDir.absolutePath() + "/" + folder);
        if (!subDir.exists()) {
            subDir.mkpath(".");
        }
    }

    // Create and write to file
    QFile file(baseFolderPath + "/users/0000000001.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "admin admin"<<"\n"<<"0000000001"<<"\n"<<"admin@ensia.edu.dz"<<"\n"<<"0123456789"<<"\n"<<"2001-01-01"<<"\n"<<"8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918"<<"\n";
        file.close();
        qDebug() << "File created and written successfully.";
    } else {
        qDebug() << "Error creating or writing to the file.";
    }
    return baseFolderPath;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Check if it's the first run of the application
    QSettings settings;

    bool isFirstRun = !settings.contains("firstRun");

    // Show path selection dialog if it's the first run
    if (isFirstRun) {
        PathSelectionDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            QString selectedPath = dialog.getSelectedPath();
            QMessageBox::information(nullptr, "Welcome", "Thanks for choosing our application!\nPlease read the documentation provided with the application.");
            selectedPath=createFoldersAndFile(selectedPath);
            settings.setValue("dataPath", selectedPath);
            settings.setValue("firstRun", false); // Set firstRun flag to false
        } else {
            // Handle if user cancels path selection
            QMessageBox::critical(nullptr, "Error", "Path selection canceled. The application will now exit.");
            return 1; // Exit application
        }
    }

    MainWindow w;
    w.show();
    return a.exec();
}
