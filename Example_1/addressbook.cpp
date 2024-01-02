#include "addressbook.h"
#include "ui_addressbook.h"

AddressBook::AddressBook(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddressBook)
{
    ui->setupUi(this);
    QLabel* nameLabel = new QLabel(tr("Name: "));
    nameLine = new QLineEdit();
    nameLine->setReadOnly(true);
    QLabel* addressLabel = new QLabel(tr("Address: "));
    addressText = new QTextEdit();
    addressText->setReadOnly(true);
    setWindowTitle(tr("Simple Address Book"));
    addButton = new QPushButton("Add");
    addButton->show();
    submitButton = new QPushButton("Submit");
    submitButton->hide();
    cancelButton = new QPushButton("Cancel");
    cancelButton->hide();
    nextButton = new QPushButton("Next");
    nextButton->setEnabled(false);
    nextButton->show();
    previousButton = new QPushButton("Previous");
    previousButton->setEnabled(false);
    previousButton->show();
    editButton = new QPushButton("Edit");
    editButton->setEnabled(false);

    removeButton = new QPushButton("Remove");
    removeButton->setEnabled(false);
    findButton = new QPushButton("Find");
    findButton->setEnabled(false);
    dialog = new FindDialog(this);
    connect(addButton, &QPushButton::clicked, this, &AddressBook::addContact);
    connect(submitButton, &QPushButton::clicked, this, &AddressBook::submitContact);
    connect(cancelButton, &QPushButton::clicked, this, &AddressBook::cancel);
    connect(nextButton, &QPushButton::clicked, this, &AddressBook::next);
    connect(previousButton, &QPushButton::clicked, this, &AddressBook::previous);
    connect(editButton, &QPushButton::clicked, this, &AddressBook::editContact);
    connect(removeButton,&QPushButton::clicked, this, &AddressBook::removeContact);
    connect(findButton, &QPushButton::clicked, this, &AddressBook::findContact);
    QVBoxLayout* buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton, Qt::AlignTop);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
     buttonLayout1->addWidget(findButton);
    buttonLayout1->addStretch();
    QHBoxLayout* buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(nextButton);
    buttonLayout2->addWidget(previousButton);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0); // Layout заполняется как табличка, т.е. идем по строкам и столбцам
    mainLayout->addWidget(nameLine, 0, 1);
    mainLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(addressText, 1, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addLayout(buttonLayout2, 2, 1);
    setLayout(mainLayout);
}

AddressBook::~AddressBook()
{
    delete ui;
}

void AddressBook::updateInterface(Mode mode)
{
    if(mode==NavigatingMode){
        cur_mode=NavigatingMode;
        addButton->setEnabled(true);
        addButton->show();
        removeButton->setEnabled(contacts.size()>=1);
        //removeButton->show();
        editButton->setEnabled(contacts.size()>=1);
        //editButton->show();
        nextButton->setEnabled(contacts.size()>1);
        previousButton->setEnabled(contacts.size()>1);
        findButton->show();
        findButton->setEnabled(true);
        cancelButton->hide();
        submitButton->hide();
    }
    else if(mode==EditingMode){
        cur_mode= EditingMode;
        nameLine->setReadOnly(false);
        addressText->setReadOnly(false);
        submitButton->setEnabled(true);
        submitButton->show();
        addButton->setEnabled(false);
        cancelButton->setEnabled(false);
        removeButton->setEnabled(false);
        editButton->setEnabled(false);
        nextButton->setEnabled(false);
        previousButton->setEnabled(false);
    }
    else if(mode==AdditingMode){
        cur_mode=AdditingMode;

    }

}

void AddressBook::addContact()

{   nextButton->setEnabled(false);
    previousButton->setEnabled(false);
    oldName = nameLine->text();
  oldAddress = addressText->toPlainText(); // toPlainText() возвращает текст с textedit'а
  nameLine->clear();
  addressText->clear();
  nameLine->setReadOnly(false);
  nameLine->setFocus(Qt::OtherFocusReason);
  addressText->setReadOnly(false);
  addButton->setEnabled(false);
  submitButton->show();
  cancelButton->show();
  updateInterface(AdditingMode);

}

void AddressBook::submitContact()
{
  int number = contacts.size();
  nextButton->setEnabled(number > 1);
  previousButton->setEnabled(number > 1);
  QString name = nameLine->text();
  QString address = addressText->toPlainText();
  if(name.isEmpty() || address.isEmpty()){
      QMessageBox::information(this, "Empty fields!", "Enter name and address");
      return;
  }
  if(cur_mode==AdditingMode){
  if(!contacts.contains(name)){
    contacts.insert(name, address);
    QMessageBox::information(this, "Ok!", "Contact has been added");
  }
  else QMessageBox::information(this, "Ok!", "Contact already exists in your book");
  }
  else if(cur_mode==EditingMode){
  if(oldName!=name) {
    if(!contacts.contains(name)) {
    contacts.remove(oldName);
    contacts.insert(name, address);
    QMessageBox::information(this, " ", "Name has been edited");}
  else {
  QMessageBox::information(this, " ", "Sorry,Your NAME is in contacts already");
  }
  }
  else if(oldAddress!=address){
  contacts[name]=address;
  QMessageBox::information(this, " ", "Address has been edited");
  }
  }
  updateInterface(NavigatingMode);
//  if(contacts.isEmpty()){
//    nameLine->clear();
//    addressText->clear();
//  }
//  nameLine->setReadOnly(true);
//  addressText->setReadOnly(true);
//  addButton->setEnabled(true);
//  submitButton->hide();
//  cancelButton->hide();
}

void AddressBook::cancel() // хз нах надо просто блокирует ввод
{ int number = contacts.size();
  nextButton->setEnabled(number > 1);
  previousButton->setEnabled(number > 1);
  nameLine->setText(oldName);
  nameLine->setReadOnly(true);

  addressText->setText(oldAddress);
  addressText->setReadOnly(true);

  addButton->setEnabled(true);
  submitButton->hide();
  cancelButton->hide();
}

void AddressBook::next()
{

  QString name = nameLine->text();
  QMap<QString,QString>::iterator i = contacts.find(name);
  if(i!=contacts.end()) ++i;
  if(i==contacts.end()) i = contacts.begin();
  nameLine->setText(i.key());
  addressText->setText(i.value());
}

void AddressBook::previous()
{

  QString name = nameLine->text();
  QMap<QString,QString>::iterator i = contacts.find(name);
  if(i==contacts.end()){
    nameLine->clear();
    addressText->clear();
    return;
  }
  if(i==contacts.begin()){
    i=contacts.end();
  }
  --i;
  nameLine->setText(i.key());
  addressText->setText(i.value());
}
void AddressBook::removeContact()
{
  QString name = nameLine->text();
  if(contacts.contains(name)){
    contacts.remove(name);
    QMessageBox::information(this, " ", "Contact was removed from your book!");
    previous();
  }
 updateInterface(NavigatingMode);
}
void AddressBook::editContact(){
  oldName = nameLine->text();
  oldAddress = addressText->toPlainText();
  updateInterface(EditingMode);
}

void AddressBook::findContact()
{ dialog->show();
  if(dialog->exec() == QDialog::Accepted){
   QString findName = dialog->getFindText();
   if(contacts.contains(findName)){
   nameLine->setText(findName);
   addressText->setText(contacts.value(findName));
   }
   else {
    QMessageBox::information(this, " ", "Sorry, contact is not in your address book:(");
   return;
  }
  }
  updateInterface(NavigatingMode);
  }

