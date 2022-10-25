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
    ui->label->setVisible(false);
    ui->saveMasterKey->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->lblshortcut->setVisible(false);
    ui->generatedLbl->setVisible(false);
    ui->qrGenBth->setVisible(false);
    ui->generatedLbl->setTextInteractionFlags(Qt::TextSelectableByMouse);



}

MainWindow::~MainWindow() { delete ui; }

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


  QFile *fileWithPass = new QFile("lib_ptr.dll");//real file
  QFile *bakFileWithPass = new QFile("libgcc7_snt.dll");//backup file

  QString dataInfile = pass.toPlainText() + " " + acc.toPlainText();

  fileWithPass->open(QFile::WriteOnly|QFile::ReadOnly|QIODevice::Text| QFile::Append);
  bakFileWithPass->open(QFile::WriteOnly| QIODevice::Text| QFile::Append);

  if (fileWithPass->isOpen()) {
    (QIODevice::WriteOnly  | QIODevice::Append);

    bakFileWithPass->write(crypt_file(dataInfile));

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

  QFile *fileWithPass = new QFile("lib_ptr.dll");
  fileWithPass->open(QFile::WriteOnly|QIODevice::Text);//Delete file containing passwords
  fileWithPass->write("");
  QMessageBox *delitefileSuccesful = new QMessageBox(this);

  if (fileWithPass->size() == 0) {

  delitefileSuccesful->setWindowTitle("Mandarin4ik");
  delitefileSuccesful->setGeometry(800, 500, 100, 40);
  delitefileSuccesful->setText("Passwords delete succesful.");
  delitefileSuccesful->show();

   }  else  {
        QMessageBox::critical(this, ("Error"), ("Failed to remove passwords"));

   }

    delete fileWithPass;
}

void MainWindow::on_actionDelete_some_Passwords_triggered()
{

  QLabel *lblInputSomePassInFile = new QLabel;
  lblInputSomePassInFile->setWindowOpacity(0.0);
  lblInputSomePassInFile->setFixedSize(700, 470);
  lblInputSomePassInFile->setWindowTitle("Mandarin4ik");
  lblInputSomePassInFile->show();

  QStatusBar *textManual = new QStatusBar(lblInputSomePassInFile);
  textManual->setGeometry(40, 40, 250, 40);
  textManual->showMessage("Edit passwords in  this window: ");
  textManual->show();

  QFile *filePass = new QFile("lib_ptr.dll");
  filePass->open(QFile::ReadOnly);


  QString listWordsInFile = filePass->readAll();

  QTextEdit *inputPassKey = new QTextEdit(lblInputSomePassInFile);//Window in that edit users passwords
  inputPassKey->setGeometry(40, 120, 390, 290);
  inputPassKey->setText(listWordsInFile);
  inputPassKey->show();

  QPushButton *savepass = new QPushButton(lblInputSomePassInFile);
  savepass->setText("Save edit");
  savepass->setGeometry(450, 400, 150, 50);
  connect(savepass, &QPushButton::clicked, this, [=](){remove_some_passwords_bth(*inputPassKey);});//Standart function for saving edit
  savepass->show();
  filePass->close();
  filePass->remove();

  delete filePass;

}
void MainWindow::remove_some_passwords_bth(QTextEdit &deleteThisText){

  QFile *filePass = new QFile("lib_ptr.dll");
  filePass->open(QFile::WriteOnly);

  if(filePass->isOpen()){

  filePass->write(deleteThisText.toPlainText().toUtf8());
  filePass->close();
  QMessageBox::information(this,("Done"),("Edit saved succesful"));

    } else{
        QMessageBox::critical(this,("Error"),("Failed to save edit passwords"));
    }
   filePass->remove();
  delete filePass;

}


void MainWindow::save_all_master_key(QByteArray newpass){

  QFile *settingsPass = new QFile("settingsPass.ini");
  settingsPass->open(QFile::WriteOnly);// Remove old password

  QByteArray hashedNewPass = QCryptographicHash::hash(newpass, QCryptographicHash::Sha256).toHex();
  qDebug() << hashedNewPass;

  settingsPass->write(hashedNewPass);
  if(hashedNewPass == QCryptographicHash::hash(newpass, QCryptographicHash::Sha256).toHex()){
      QMessageBox::information(this, ("Done!"), ("Password changed succesfuly!"));
  }
  else{ QMessageBox::information(this, ("Error"), ("Password don't changed")); }
  settingsPass->close();
}

void MainWindow::about_encryption(){

  QLabel *aboutWind = new QLabel;
  aboutWind->setWindowOpacity(0.0);
  aboutWind->setFixedSize(700, 470);
  aboutWind->setWindowTitle("Mandarin4ik");
  aboutWind->setText("              RC5 is a symmetric key block " "\n"
  "              encryption algorithm designed by Ron" "\n"
  "              Rivest in 1994. It is notable for being simple,""\n"
  "              fast (on account of using only primitive ""\n"
  "              computer operations like XOR, shift, etc.) and consumes less memory.");
  aboutWind->show();

}

void MainWindow::on_commandLinkButton_clicked()
{
    ui->label_2->setVisible(false);
    QLabel *lblInputPassInFile = new QLabel(this);
    lblInputPassInFile->setWindowOpacity(0.0);
    lblInputPassInFile->setGeometry(380, 80, 550, 359);
    lblInputPassInFile->setText( "                Input passwords and URL ");
    lblInputPassInFile->setWindowTitle("Mandarin4ik");
    lblInputPassInFile->showNormal();


    QStatusBar *lyricsInputPass = new QStatusBar(lblInputPassInFile);
    QStatusBar *lyricsInputAccount = new QStatusBar(lblInputPassInFile);

    lyricsInputPass->setGeometry(120, 12, 170, 40);
    lyricsInputAccount->setGeometry(120, 70, 170, 40);

    lyricsInputPass->showMessage("Password: ");
    lyricsInputAccount->showMessage("URL: ");

    lyricsInputPass->show();
    lyricsInputAccount->show();

    QTextEdit *txtetInputPass = new QTextEdit(lblInputPassInFile);//Input passwords in file
    QTextEdit *txtetInputKey = new QTextEdit(lblInputPassInFile);

    txtetInputPass->setGeometry(120, 40, 500, 40);
    txtetInputKey->setGeometry(120, 100, 500, 40);

    txtetInputPass->show();
    txtetInputKey->show();

    QPushButton *savepass = new QPushButton(lblInputPassInFile);
    savepass->setText("Save");
    savepass->setGeometry(250, 250, 150, 50);

    connect(savepass, &QPushButton::clicked, this, [=](){
          save (*txtetInputPass, *txtetInputKey
                ); });

    savepass->show();

    QPushButton *closeInput = new QPushButton(lblInputPassInFile);
    closeInput->setText("Back");
    closeInput->setGeometry(100, 250, 150, 50);

    closeInput->show();


}



void MainWindow::on_changeMasterKey_clicked()
{
     ui->qrGenBth->setVisible(true);
    ui->label_2->setVisible(false); // Close qr-code
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
    ui->qrGenBth->setVisible(true);
    ui->label_2->setVisible(false);// add button for scanning qr

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
    qDebug() << returnedCount;
    return returnedCount;
}

QByteArray MainWindow::decrypt_file(){

    Network cryptoclass;
    QByteArray returnedCount;
    QString clear;

    QFile *file = new QFile("lib_ptr.dll");
    file->open(QFile::ReadOnly | QIODevice::Text);
    if(file->isOpen()){
        while(!file->atEnd())
              {
                  //читаем строку
                  QString str = file->readLine();
                    clear.append(cryptoclass.rsa_pub_decrypt_base64(str) + "\n");
              }

        returnedCount = clear.toUtf8();

    }
    else{
         QMessageBox::warning(this, ("Error"), ("No found file"));
    }

     file->close();
    return returnedCount;
}


void MainWindow::on_viewPasswdsBth_clicked()
{

    QFile *passwdFile = new QFile("lib_ptr.dll");
    passwdFile->open(QFile::ReadOnly);
    if(passwdFile->size() != 0){

    QByteArray data = decrypt_file();
    qDebug() << data;
    QString userView = data;
    QLabel *lyrics = new QLabel;
    lyrics->setText(userView);
    lyrics->setFixedSize(700, 470);
    lyrics->setWindowTitle("Mandarin4ik");
    lyrics->setTextInteractionFlags(Qt::TextSelectableByMouse);
    lyrics->show();

    }

    else{
        QMessageBox::warning(this, ("Error"), ("File not found"));
    }

}

