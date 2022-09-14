#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QAction>
#include <QTextEdit>
#include <QFile>
#include <QPushButton>
#include <QLabel>
#include <QUrl>
#include <QLineEdit>
#include <ctime>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent =0);
    ~MainWindow();
    unsigned char StringToChar(QString *str);

Ui::MainWindow *ui;


public slots:

QString match_generate();

void on_actionDelete_all_Passwords_triggered();

void on_actionDark_Material_triggered();

void on_actionLight_triggered();

void on_actionDelete_some_Passwords_triggered();

void on_actionMaster_key_triggered();

void about_encryption();

void save_all_master_key(const QString &newpass);

void generate_passwords_clicked();

void change_master_key_bth(QLabel &lbl);

void read_pass_in_file_clicked();

void save(QTextEdit &pass, QTextEdit &acc );

void remove_some_passwords_bth(QTextEdit &deleteThisText);

public slots:

void check_password_in_master_label(QLabel &deleteLabelCheck, QLineEdit &password);

private slots:

void on_commandLinkButton_clicked();
};


#endif // MAINWINDOW_H

