#include "mainwindow.h"
#include <QAction>
#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QCommandLinkButton>
#include <QRadioButton>
#include <QStatusBar>
#include <QMessageBox>
#include <QSettings>
#include <QKeyEvent>
#include "unit_test.h"
#include <QCryptographicHash>
#include <QDebug>
class Master : public MainWindow{//Class for check Master-password
public:
    Master(QWidget *parent = 0);
};

Master::Master(QWidget *parent) : MainWindow(parent)
{


    QLabel *masterWindowTmp = new QLabel;
    masterWindowTmp->setWindowOpacity(0.87);
    masterWindowTmp->setFixedSize(700, 470);
    masterWindowTmp->setStyleSheet("background-color: rgba(83, 83, 83, 80); color: rgb(255, 128, 0);font: 700 12pt 'Segoe UI';");
    masterWindowTmp->show();

    QStatusBar *textDataPass = new QStatusBar(masterWindowTmp);
    textDataPass->showMessage("Enter master-key. Default key =  'admin'");
    textDataPass->setGeometry(130, 50, 450, 40);
    textDataPass->show();

    QLineEdit *lineCheckPassword = new QLineEdit(masterWindowTmp);
    lineCheckPassword->setGeometry(200, 120, 300, 40);
    lineCheckPassword->setEchoMode(QLineEdit::Password);
    lineCheckPassword->show();

    QPushButton *checkMasterPass = new QPushButton(masterWindowTmp);
    checkMasterPass->setText("&Enter");
    checkMasterPass->setGeometry(350, 250, 150, 50);
    checkMasterPass->setShortcut(QKeySequence(Qt::Key_Enter)); // add hotkey
    connect(checkMasterPass, &QPushButton::clicked, this, [=](){
        check_password_in_master_label(*masterWindowTmp ,*lineCheckPassword); //belong passwords with password that save in program
    });


    checkMasterPass->show();

    QPushButton *forgotKey = new QPushButton(masterWindowTmp);
    forgotKey->setText("Forgot key");
    forgotKey->setGeometry(170, 250, 150, 50);
    forgotKey->show();


}

void MainWindow::check_password_in_master_label(QLabel &deleteLabelCheck, QLineEdit &password){


   QFile *passFile = new QFile("settingsPass.ini");
   passFile->open(QFile::ReadOnly);

   QByteArray datacomp = passFile->readAll();

   passFile->close();

    QByteArray hashedInput = QCryptographicHash::hash(password.text().toUtf8(), QCryptographicHash::Sha256).toHex();

    if(hashedInput == datacomp){

    deleteLabelCheck.hide();


    Test_Smart sm;
    sm.test_object_transf();
    sm.trfals();

    MainWindow *mainWinApp = new MainWindow;
    mainWinApp->setWindowTitle("Mandarin4ik");
    mainWinApp->setFixedSize(1000, 600);
    mainWinApp->setWindowOpacity(0.87);


    mainWinApp->show();

    }

   else{
        QMessageBox::warning(this, ("Error"), ("Incorrect password"));
    }
}


int main(int argc, char *argv[]) {

    QCoreApplication::setOrganizationName("JunSun");
     QCoreApplication::setOrganizationDomain("jprogram@bk.ru");
     QCoreApplication::setApplicationName("Madarin4ik");
  QApplication a(argc, argv);
   QApplication::applicationVersion() = "3.9.9";


  Master pumpkin; 
  pumpkin.setFixedSize(1000, 500);
  pumpkin.setWindowTitle("Madarin4ik");
  pumpkin.setWindowIcon(QIcon("mandarin.ico"));


  return a.exec();
}
