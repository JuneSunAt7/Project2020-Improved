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
#include "unit_test.h"


class Master : public MainWindow{//Class for check Master-password
public:
    Master(QWidget *parent = 0);
};

Master::Master(QWidget *parent) : MainWindow(parent)
{


    QLabel *masterWindowTmp = new QLabel;
    masterWindowTmp->setFixedSize(700, 470);
    masterWindowTmp->show();

    QStatusBar *textDataPass = new QStatusBar(masterWindowTmp);
    textDataPass->showMessage("Enter master-key. Default key =  'admin'");
    textDataPass->setGeometry(100, 50, 350, 40);
    textDataPass->show();

    QLineEdit *lineCheckPassword = new QLineEdit(masterWindowTmp);
    lineCheckPassword->setGeometry(40, 120, 300, 40);
    lineCheckPassword->setEchoMode(QLineEdit::Password);
    lineCheckPassword->show();

    QPushButton *checkMasterPass = new QPushButton(masterWindowTmp);
    checkMasterPass->setText("Enter");
    checkMasterPass->setGeometry(250, 250, 150, 50);
    connect(checkMasterPass, &QPushButton::clicked, this, [=](){
        check_password_in_master_label(*masterWindowTmp ,*lineCheckPassword); //belong passwords with password that save in program
    });
    checkMasterPass->show();

}

void MainWindow::check_password_in_master_label(QLabel &deleteLabelCheck, QLineEdit &password){
    QSettings settings( "settings.ini", QSettings::IniFormat );
    settings.beginGroup( "settings" );

    QString datacomp = settings.value("masterKey", "admin").toString();
    settings.endGroup();



    if(password.text().toUtf8() == datacomp){

    deleteLabelCheck.hide();


    Test_Smart sm;
    sm.test_object_transf();
    sm.trfals();

    MainWindow *mainWinApp = new MainWindow;
    mainWinApp->setWindowTitle("Marssword");
    mainWinApp->setFixedSize(1000, 600);
    mainWinApp->setWindowOpacity(0.97);


    QCommandLinkButton *generatePassBth= new QCommandLinkButton(mainWinApp);
    generatePassBth->setText("Generate password");

    generatePassBth->setGeometry(0, 50, 300, 50);
    generatePassBth->show();

    QCommandLinkButton *viewUserPassBth = new QCommandLinkButton( mainWinApp);
    viewUserPassBth->setText("View passwords");

    viewUserPassBth->setGeometry(0, 150, 300, 50);
    viewUserPassBth->show();

    connect(generatePassBth, &QPushButton::clicked, this, &MainWindow::generate_passwords_clicked);
    connect(viewUserPassBth, &QPushButton::clicked, this, &MainWindow::read_pass_in_file_clicked);

    mainWinApp->show();



    }

   else{
        QMessageBox *errorIfPassDontFitMbox = new QMessageBox();
        errorIfPassDontFitMbox->setWindowTitle("Marssword");
        errorIfPassDontFitMbox->setGeometry(250, 200, 1000, 140);
        errorIfPassDontFitMbox->setText(
            "Incorrect password.");
        errorIfPassDontFitMbox->show();
    }
}


int main(int argc, char *argv[]) {

    QCoreApplication::setOrganizationName("JunSun");
     QCoreApplication::setOrganizationDomain("jprogram@bk.ru");
     QCoreApplication::setApplicationName("Marssword");
  QApplication a(argc, argv);
   QApplication::applicationVersion() = "3.9.9";


  Master pumpkin; 
  pumpkin.setFixedSize(1000, 500);
  pumpkin.setWindowTitle("Marssword");
  pumpkin.setWindowIcon(QIcon("iconqt.ico"));


  return a.exec();
}
