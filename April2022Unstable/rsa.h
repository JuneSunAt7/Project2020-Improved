
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class Crypt : public QMainWindow
{
    Q_OBJECT

public:
    explicit Crypt(QWidget *parent = 0);
    ~Crypt();
         // Функция шифрования
    QString rsa_pri_encrypt_base64(const QByteArray &strClearData);
         // Функция дешифрования
    QString rsa_pub_decrypt_base64(const QByteArray &strDecryptData);
    void cryptFile();
    void decryptFile();
private:

};

#endif // MAINWINDOW_H
