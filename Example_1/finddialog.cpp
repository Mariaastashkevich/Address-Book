#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    findButton = new QPushButton("Find!");
    findButton->show();
    findText = "";
    lineEdit = new QLineEdit;
    QLabel* label = new QLabel("Enter the name of a contact: ");
    QHBoxLayout* layout1 = new QHBoxLayout;
    layout1->addWidget(label);
    layout1->addWidget(lineEdit);
    layout1->addWidget(findButton);
    setLayout(layout1);
    connect(findButton, &QPushButton::clicked, this, &FindDialog::findClicked);
    connect(findButton, &QPushButton::clicked, this, &FindDialog::accept);
}

FindDialog::~FindDialog()
{
    delete ui;
}

QString FindDialog::getFindText()
{
    return findText;
}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    if(text.isEmpty()) {
        QMessageBox::information(this, " ", "Empty string! Enter a NAME.");
        return;
    }
    else{
        findText = text;
        lineEdit->clear();
        hide();
    }
}
