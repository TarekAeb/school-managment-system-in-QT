// pathselectiondialog.h

#ifndef PATHSELECTIONDIALOG_H
#define PATHSELECTIONDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include<QLabel>

class PathSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PathSelectionDialog(QWidget *parent = nullptr);
    QString getSelectedPath() const;

private slots:
    void browse();

private:
    QString selectedPath;
    QLineEdit *lineEdit;
};

#endif // PATHSELECTIONDIALOG_H
