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
#include <QHash>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
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

   return array[0];
}

void MainWindow::generate_passwords_clicked()
{
    QLabel *lblInputPassInFile = new QLabel();
    lblInputPassInFile->setTextInteractionFlags(Qt::TextSelectableByMouse);
    lblInputPassInFile->setGeometry(780, 300, 500, 40);
    lblInputPassInFile->showNormal();


  QString arrPass;

     arrPass = match_generate();


 lblInputPassInFile->setText(arrPass);


}

void MainWindow::save(QTextEdit &pass, QTextEdit &acc) { //Slot for saving passwords(button slot)


  QFile *fileWithPass = new QFile("lib_ptr.dll");//real file
  QFile *bakFileWithPass = new QFile("libgcc7_snt.dll");//backup file

  fileWithPass->open(QFile::WriteOnly|QFile::ReadOnly|QIODevice::Text| QFile::Append);
  bakFileWithPass->open(QFile::WriteOnly| QIODevice::Text| QFile::Append);

  if (fileWithPass->isOpen()) {
  (QIODevice::WriteOnly  | QIODevice::Append);

  bakFileWithPass->write(pass.toPlainText().toUtf8() + " " + acc.toPlainText().toUtf8() +"\n");
  fileWithPass->write(pass.toPlainText().toUtf8() + " " + acc.toPlainText().toUtf8() +"\n");

  bakFileWithPass->close();
  fileWithPass->close();


  QMessageBox::information(this,("Done"),("Saved succesful"));
  pass.clear();
  acc.clear();

  } else {
  QMessageBox::critical(this,("Error"),("File not found"));
  }



}

void MainWindow::read_pass_in_file_clicked() {//Function shoved passwords of file


  QFile *fileWithPass = new QFile("lib_ptr.dll");
  fileWithPass->open(QFile::ReadWrite|QIODevice::Text);

  if(fileWithPass->isOpen() && fileWithPass->size() != 0) {

  QString data = fileWithPass->readAll();

  QLabel *lyrics = new QLabel(data);
  lyrics->setWindowOpacity(0.87);
  lyrics->setText("" + data + "\n    ");
  lyrics->setFixedSize(700, 470);
  lyrics->setWindowTitle("My passwords");
  lyrics->setTextInteractionFlags(Qt::TextSelectableByMouse);
  lyrics->show();

  fileWithPass->close();


 } else {
  QMessageBox::critical(this,("Error"),("Passwords not found"));
    }


  }

void MainWindow::on_actionNew_Password_triggered()
{


  QLabel *lblInputPassInFile = new QLabel(this);
  lblInputPassInFile->setWindowOpacity(0.87);
  lblInputPassInFile->setGeometry(380, 80, 550, 359);
  lblInputPassInFile->setText( "                Input passwords and data in english. ");
  lblInputPassInFile->setWindowTitle("My Passwords");
  lblInputPassInFile->showNormal();


  QStatusBar *lyricsInputPass = new QStatusBar(lblInputPassInFile);
  QStatusBar *lyricsInputAccount = new QStatusBar(lblInputPassInFile);

  lyricsInputPass->setGeometry(120, 12, 200, 40);
  lyricsInputAccount->setGeometry(120, 70, 200, 40);

  lyricsInputPass->showMessage("Password: ");
  lyricsInputAccount->showMessage("Data: ");

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
void MainWindow::on_actionDelete_all_Passwords_triggered()
{

  QFile *fileWithPass = new QFile("lib_ptr.dll");
  fileWithPass->open(QFile::WriteOnly|QIODevice::Text);//Delete file containing passwords
  fileWithPass->write("");
  QMessageBox *delitefileSuccesful = new QMessageBox(this);

  if (fileWithPass->size() == 0) {

  delitefileSuccesful->setWindowTitle("My passwords");
  delitefileSuccesful->setGeometry(800, 500, 100, 40);
  delitefileSuccesful->setText("Passwords delete succesful.");
  delitefileSuccesful->show();

   }  else  {
        QMessageBox::critical(this, ("Error"), ("Failed to remove passwords"));

   }

    delete fileWithPass;
}

void MainWindow::on_actionDark_Material_triggered()

{
  QSettings settings("settings.ini",QSettings::IniFormat);

  QPalette *darkPalette = new QPalette;//Dark pallete
  darkPalette->setColor(QPalette::Window, QColor(53, 53, 53));
  darkPalette->setColor(QPalette::WindowText, Qt::black);
  darkPalette->setColor(QPalette::Base, QColor(25, 25, 25));
  darkPalette->setColor(QPalette::AlternateBase, QColor(53, 53, 53));
  darkPalette->setColor(QPalette::ToolTipBase, Qt::white);
  darkPalette->setColor(QPalette::ToolTipText, Qt::white);
  darkPalette->setColor(QPalette::Text, Qt::white);
  darkPalette->setColor(QPalette::Button, QColor(153, 255, 204));
  darkPalette->setColor(QPalette::ButtonText, Qt::black);
  darkPalette->setColor(QPalette::BrightText, Qt::red);
  darkPalette->setColor(QPalette::Link, QColor(30, 230, 0));
  darkPalette->setColor(QPalette::Highlight, QColor(30, 230, 0));
  darkPalette->setColor(QPalette::HighlightedText, Qt::black);

  qApp->setPalette(*darkPalette);

  settings.setValue("settings/theme", true);
  settings.endGroup();

  delete darkPalette;

}

void MainWindow::on_actionLight_triggered()
{

  qApp->setPalette(style()->standardPalette());// Return light theme

  QSettings *settings = new QSettings("settings.ini",QSettings::IniFormat);
  settings->setValue("settings/theme", false);
  settings->endGroup();

  delete settings;

}

void MainWindow::on_actionDelete_some_Passwords_triggered()
{

  QLabel *lblInputSomePassInFile = new QLabel;
  lblInputSomePassInFile->setWindowOpacity(0.87);
  lblInputSomePassInFile->setFixedSize(700, 470);
  lblInputSomePassInFile->setWindowTitle("My Passwords");
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

void MainWindow::on_actionMaster_key_triggered()
{

  QLabel *lblSettings = new QLabel;
  lblSettings->setWindowOpacity(0.87);
  lblSettings->setFixedSize(700, 470);
  lblSettings->setWindowTitle("My passwords");
  lblSettings->setTextInteractionFlags(Qt::TextSelectableByMouse);

  QPushButton *changePass = new QPushButton(lblSettings);
  changePass->setGeometry(40, 120, 170, 40);
  changePass->setText("Change master-key");
  connect(changePass, &QPushButton::clicked, this,[=](){change_master_key_bth(*lblSettings);});
  lblSettings->show();

  QPushButton *changeLang = new QPushButton(lblSettings);
  changeLang->setGeometry(40, 180, 200, 40);
  changeLang->setText("Language version: english");
  changeLang->show();

  QPushButton *forEncryption = new QPushButton(lblSettings);
  forEncryption->setGeometry(40, 70, 170, 40);
  forEncryption->setText("About encryption");
  connect(forEncryption, &QPushButton::clicked, this, &MainWindow::about_encryption);
  forEncryption->show();


}

void MainWindow::change_master_key_bth(QLabel &lbl){

  QStatusBar *oldPass = new QStatusBar(&lbl);
  oldPass->showMessage("Input new master-key:");
  oldPass->setGeometry(250, 110, 170, 40);
  oldPass->show();

  QLineEdit *inputPassKey = new QLineEdit(&lbl);//New key
  inputPassKey->setGeometry(250, 150, 170, 40);
  inputPassKey->show();

  QPushButton *changePass = new QPushButton(&lbl);
  changePass->setGeometry(400, 344, 170, 40);
  changePass->setText("Save all");
  connect(changePass, &QPushButton::clicked, this,[=](){save_all_master_key(inputPassKey->text().toUtf8());});
  changePass->show();


}

void MainWindow::save_all_master_key(const QString &newpass){

  QSettings *settings = new QSettings("settings.ini",QSettings::IniFormat);
  QHash <QString, int> hash;//hashing pass

  settings->setValue("settings/masterKey",newpass.toUtf8() );
  settings->endGroup();

  delete settings;
}

void MainWindow::about_encryption(){

  QLabel *aboutWind = new QLabel;
  aboutWind->setWindowOpacity(0.87);
  aboutWind->setFixedSize(700, 470);
  aboutWind->setWindowTitle("My passwords");
  aboutWind->setText("              RC5 is a symmetric key block " "\n"
  "              encryption algorithm designed by Ron" "\n"
  "              Rivest in 1994. It is notable for being simple,""\n"
  "              fast (on account of using only primitive ""\n"
  "              computer operations like XOR, shift, etc.) and consumes less memory.");
  aboutWind->show();

}




