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
#include <QClipboard>
#include <QProcess>

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

void on_actionDelete_some_Passwords_triggered();


void about_encryption();

void save_all_master_key(QByteArray newpass);

void save(QTextEdit &pass, QTextEdit &acc );

void remove_some_passwords_bth(QTextEdit &deleteThisText);

QByteArray crypt_file(QString &data);

QByteArray decrypt_file();


void check_password_in_master_label(QLabel &deleteLabelCheck, QLineEdit &password);


private slots:

void on_commandLinkButton_clicked();
void on_changeMasterKey_clicked();

void on_qrGenBth_clicked();
void on_generate_passwdBth_clicked();
void on_actionHome_Wi_Fi_triggered();
void on_actionOthers_triggered();
void on_actionReestablish_triggered();
void on_actionStart_over_triggered();
void on_actionRegenerate_qr_triggered();
void on_actionWrite_support_triggered();
void on_viewPasswdsBth_clicked();
};


#endif // MAINWINDOW_H

