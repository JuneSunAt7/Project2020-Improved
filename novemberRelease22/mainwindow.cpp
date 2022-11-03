#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStatusBar>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QSettings>
#include <QComboBox>
#include <QTextBrowser>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QCryptographicHash>
#include "network.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
     ui->setupUi(this);
     setWindowIcon(QIcon("mandarin.ico"));
    setUi();
    ui->generatedLbl->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->label_2->setVisible(true);


}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setUi(){
    ui->label->setVisible(false);
    ui->saveMasterKey->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->lblshortcut->setVisible(false);
    ui->generatedLbl->setVisible(false);
    ui->qrGenBth->setVisible(false);
    ui->passwdFrame->setVisible(false);
    ui->usersPasswdTedit->setVisible(false);
    ui->label_2->setVisible(false);
}

QString MainWindow::match_generate(){

    srand(time(NULL));

    QString *mainarr = new QString[20]; //Passwords


    QString buff;


    int *arrintrand = new int[1000]; //random numbers
    QString *arrconvertint = new QString[1000];

    for(int i = 0; i < 1000; i++){
        arrintrand[i] = rand() % 1000;
        arrconvertint[i] = QString::number(arrintrand[i]);
    }


    char *mass = new char[26]; //random charsters

    for(int i = 0; i <26; i++) {
        mass[i] = rand()   %26+0x61;
    }

    for(int i = 0; i < 20; i = i+2){


        int j = rand() % 1;

        if(j == 0)
        {
            mainarr[i] = mass[rand() % 26];
            mainarr[i+1] = arrconvertint[rand() % 1000 ];

        }

    }

      QString array[20];

          for(int j = 0; j < 20; j++){

                  for(int i = 0 ; i < 20; i++){
                      buff.append(mainarr[i]);
                   }

              array[j] = buff;
      }

   return array[rand() % 19];
}



void MainWindow::save(QTextEdit &pass, QTextEdit &acc) { //Slot for saving passwords(button slot)


  QFile *fileWithPass = new QFile("lib_ptr.pw");//real file
  QFile *bakFileWithPass = new QFile("libgcc7_snt.pw");//backup file

  QString dataInfile = pass.toPlainText() + " " + acc.toPlainText();

  fileWithPass->open(QFile::WriteOnly|QFile::ReadOnly|QIODevice::Text| QFile::Append);
  bakFileWithPass->open(QFile::WriteOnly| QIODevice::Text| QFile::Append);

  if (fileWithPass->isOpen()) {
    (QIODevice::WriteOnly  | QIODevice::Append);

    bakFileWithPass->write(crypt_file(dataInfile) + "\n");

    fileWithPass->write(crypt_file(dataInfile) + "\n");

    bakFileWithPass->close();
    fileWithPass->close();



    QMessageBox::information(this,("Done"),("Saved succesful"));
    pass.clear();
    acc.clear();

  } else {
  QMessageBox::critical(this,("Error"),("File not found"));
  }


}





void MainWindow::on_actionDelete_all_Passwords_triggered()
{

  QFile *fileWithPass = new QFile("lib_ptr.pw");
  fileWithPass->open(QFile::WriteOnly|QIODevice::Text);//Delete file containing passwords
  fileWithPass->write("");

  if (fileWithPass->size() == 0) {
    QMessageBox::information(this, ("Done"), ("Passwords delete!"));
   }  else  {
        QMessageBox::critical(this, ("Error"), ("Failed to remove passwords"));

   }

    fileWithPass->close();
    delete fileWithPass;
}



void MainWindow::save_all_master_key(QByteArray newpass){

  QFile *settingsPass = new QFile("settingsPass.ini");
  settingsPass->open(QFile::WriteOnly);// Remove old password

  QByteArray hashedNewPass = QCryptographicHash::hash(newpass, QCryptographicHash::Sha256).toHex();

  settingsPass->write(hashedNewPass);
  if(hashedNewPass == QCryptographicHash::hash(newpass, QCryptographicHash::Sha256).toHex()){
      QMessageBox::information(this, ("Done!"), ("Password changed succesfuly!"));
  }
  else{ QMessageBox::information(this, ("Error"), ("Password don't changed")); }
  settingsPass->close();
  delete settingsPass;
}



void MainWindow::on_commandLinkButton_clicked()
{
    setUi();
    ui->passwdFrame->setVisible(true);

}



void MainWindow::on_changeMasterKey_clicked()
{
   setUi();
     ui->qrGenBth->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->label->setVisible(true);
    ui->saveMasterKey->setVisible(true);

    connect(ui->saveMasterKey, &QPushButton::clicked, this, [=](){save_all_master_key(ui->lineEdit->text().toUtf8());});
}


void MainWindow::on_qrGenBth_clicked()
{
// python script for generate qr for mobile app
    QProcess process;
    QString file = "python qrScript.py";
    process.start();


}


void MainWindow::on_generate_passwdBth_clicked()
{
    setUi();
    ui->qrGenBth->setVisible(true);


    ui->lblshortcut->setVisible(true);

    ui->generatedLbl->setVisible(true);
    QString genPass = match_generate();

    genPass.resize(25);


    QClipboard *clipboard = QApplication::clipboard(); // add password in clipboard
    clipboard->setText(genPass);

    QMessageBox::information(this, ("Done"), ("Password copied in clipboard!"));



    ui->generatedLbl->setText(genPass + "\n");

}

QByteArray MainWindow::crypt_file(QString &data){// запись масива битов в файл, возвращаем его
    Network cryptoclass;
    QString newData;

    newData = cryptoclass.rsa_pri_encrypt_base64(data);


    QByteArray returnedCount;
    returnedCount = newData.toUtf8();
    return returnedCount;
}

QByteArray MainWindow::decrypt_file(){

    Network cryptoclass;
    QByteArray returnedCount;
    QString clear;

    QFile *file = new QFile("lib_ptr.pw");
    file->open(QFile::ReadOnly | QIODevice::Text);
    if(file->isOpen() && file->size() != 0){
        while(!file->atEnd())
              {
                  //читаем строку
                  QString str = file->readLine();
                    clear.append(cryptoclass.rsa_pub_decrypt_base64(str) + "\n");
              }

        returnedCount = clear.toUtf8();

    }
    else{
         QMessageBox::warning(this, ("Error"), ("No found file or file is empty"));
    }

     file->close();
     delete file;
    return returnedCount;
}


void MainWindow::on_viewPasswdsBth_clicked()
{


    QFile *passwdFile = new QFile("lib_ptr.pw");
    passwdFile->open(QFile::ReadOnly);
    if(passwdFile->size() != 0){

    QByteArray data = decrypt_file();
    qDebug() << data;
    QString userView = data;

       setUi();
    ui->usersPasswdTedit->setVisible(true);
    ui->usersPasswdTedit->setText(userView);
    ui->usersPasswdTedit->setTextInteractionFlags(Qt::TextSelectableByMouse);


    }

    else{
        QMessageBox::warning(this, ("Error"), ("File is empty"));
    }

}


void MainWindow::on_saveBth_clicked()
{
    QFile *fileWithPass = new QFile("lib_ptr.pw");//real file
    QFile *bakFileWithPass = new QFile("libgcc7_snt.pw");//backup file

    QString dataInfile = ui->passLine->text() + " " + ui->urlLine->text();

    fileWithPass->open(QFile::WriteOnly|QFile::ReadOnly|QIODevice::Text| QFile::Append);
    bakFileWithPass->open(QFile::WriteOnly| QIODevice::Text| QFile::Append);

    if (fileWithPass->isOpen()) {
      (QIODevice::WriteOnly  | QIODevice::Append);

      bakFileWithPass->write(crypt_file(dataInfile));

      fileWithPass->write(crypt_file(dataInfile) + "\n");

      bakFileWithPass->close();
      fileWithPass->close();



      QMessageBox::information(this,("Done"),("Saved succesful"));
      ui->passLine->clear();
      ui->urlLine->clear();

    } else {
    QMessageBox::critical(this,("Error"),("File not found"));
    }
}

