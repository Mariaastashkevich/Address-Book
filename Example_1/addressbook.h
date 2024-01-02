#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMap>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "finddialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class AddressBook; }
QT_END_NAMESPACE
enum Mode {NavigatingMode, EditingMode, AdditingMode};
class AddressBook : public QWidget
{
    Q_OBJECT

public:
    AddressBook(QWidget *parent = nullptr);
    ~AddressBook();
    void updateInterface(Mode mode);

public slots:
    void addContact();
    void submitContact();
    void cancel();
    void next();
    void previous();
    void removeContact();
    void editContact();
    void findContact();
private:
    Ui::AddressBook *ui;
    QTextEdit* addressText;
    QLineEdit* nameLine;
    QPushButton* addButton;
    QPushButton* submitButton;
    QPushButton* cancelButton;
    QPushButton* nextButton;
    QPushButton* previousButton;
    QPushButton* removeButton;
    QPushButton* editButton;
    QPushButton* findButton;
    QMap<QString,QString> contacts;
    QString oldName;
    QString oldAddress;

    Mode cur_mode;

    FindDialog* dialog;
};


#endif // ADDRESSBOOK_H
