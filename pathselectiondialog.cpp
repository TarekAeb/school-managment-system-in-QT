#include "pathselectiondialog.h"

PathSelectionDialog::PathSelectionDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create label
    QLabel *label = new QLabel("Please select a directory:", this);

    lineEdit = new QLineEdit(this);
    QPushButton *browseButton = new QPushButton("Browse", this);
    QPushButton *okButton = new QPushButton("OK", this);

    connect(browseButton, &QPushButton::clicked, this, &PathSelectionDialog::browse);
    connect(okButton, &QPushButton::clicked, this, &PathSelectionDialog::accept);

    layout->addWidget(label); // Add label to layout
    layout->addWidget(lineEdit);
    layout->addWidget(browseButton);
    layout->addWidget(okButton);

    setLayout(layout);
}

QString PathSelectionDialog::getSelectedPath() const
{
    return selectedPath;
}

void PathSelectionDialog::browse()
{
    selectedPath = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
    lineEdit->setText(selectedPath);
}
