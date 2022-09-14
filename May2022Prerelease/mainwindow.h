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
void on_actionNew_Password_triggered();

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

void crypt_file(QLineEdit &patchFile);

void cryptAlgorithm(QFile &file);

public slots:

void check_password_in_master_label(QLabel &deleteLabelCheck, QLineEdit &password);

private slots:
void on_networkBth_clicked();
void on_browserBth_clicked();
void on_actionCrypt_file_triggered();

void on_actionDecrypt_file_triggered();
};


#endif // MAINWINDOW_H

