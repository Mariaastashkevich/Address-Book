#ifndef FINDDIALOG_H
#define FINDDIALOG_H
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
#include <QDialog>

namespace Ui {
class FindDialog;
}
class QLineEdit;
class QPushButton;
class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();
    QString getFindText();
public slots:
    void findClicked();
private:
    Ui::FindDialog *ui;
    QPushButton* findButton;
    QLineEdit* lineEdit;
    QString findText;
};

#endif // FINDDIALOG_H
