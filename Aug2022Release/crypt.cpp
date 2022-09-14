#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QComboBox>
#include <QStorageInfo>
#include <QDebug>
#include <QList>
#include <QStringList>

void MainWindow::on_actionCrypt_file_triggered()
{
    QLineEdit *inputPatch = new QLineEdit(this);
    inputPatch->setGeometry(490, 117, 281, 41);
    inputPatch->show();

    QLabel *textInputPatch = new QLabel(this);
    textInputPatch->setGeometry(490, 69, 161, 61);
    textInputPatch->setText("Input file patch");
    textInputPatch->show();

    QPushButton *cryptBth = new QPushButton(this);
    cryptBth->setGeometry(500, 190, 131, 41);
    cryptBth->setText("Crypt");
    connect(cryptBth, &QPushButton::clicked, this, [=](){
         crypt_file(*inputPatch); });
    cryptBth->show();

}
void MainWindow::on_actionDecrypt_file_triggered()
{

}

void MainWindow::crypt_file(QLineEdit &patchFile)
{
    QFile *fileCrypt = new QFile(patchFile.text().toUtf8());
    fileCrypt->open(QFile::ReadWrite|QIODevice::ReadWrite);

    if(fileCrypt->isOpen() && fileCrypt->size() != 0) {

        cryptAlgorithm(*fileCrypt);

      QMessageBox::information(this,("Info"),("File succesful crypted!"));
      fileCrypt->close();


   } else {
    QMessageBox::critical(this,("Error"),("File not found"));
      }

}


void MainWindow::cryptAlgorithm(QFile &file){



    QByteArray msg;
    msg = file.readAll();


}
