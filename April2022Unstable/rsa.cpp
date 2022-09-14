#include "rsa.h"

#include <QDebug>
#include <QFile>

Crypt::Crypt(QWidget *parent)
    : QMainWindow(parent)

{


   // cryptFile();
   // decryptFile();
}

Crypt::~Crypt()
{

}



QString Crypt::rsa_pri_encrypt_base64 (const QByteArray& strClearData)
{
         // Длина закрытого ключа 512 (используйте открытый ключ, сгенерированный вами)
    char private_key[] = "-----BEGIN PRIVATE KEY-----\n"\
            "MIIBVgIBADANBgkqhkiG9w0BAQEFAASCAUAwggE8AgEAAkEAzpXEGSjFGDRdr4Gp\n"\
            "k/impFrqxw0JUs7oUwTheJgqNIfCJfw00PHOKmIDI9UoS+E3Ozs1reMP1r0IuUys\n"\
            "zX5LGwIDAQABAkEAhUCjcdsTbu5wM8H+QT0VOFSQtf5ZsjlWMB6o1SHJr4Fs8UEE\n"\
            "7JHUTGrlUopMrhQDfYxGqDUAXykca99xu8e1QQIhAPPdcze2DeV5X9a8bcd3VEzK\n"\
            "Luy6SMOtomEMUKPlYEa7AiEA2N1puJwKEulYWaHywLwhA8tM08YFsFqh18JsUbP5\n"\
            "NyECIQCtuykXGnLB9XsqfyjyPnfnEO7nJTsrdGrHGr/kU0gIewIgVWqYGntzSFGa\n"\
            "V+t+psUyp8DqaLslQHniJw5QBbpCXaECIQDgDWRfFb7h68XMi2fpkd727YDpl64p\n"\
            "fb2H/qFyq3xBDw==\n"\
            "-----END PRIVATE KEY-----";

         // Загружаем строковый ключ в био объект
    BIO* pKeyBio = BIO_new_mem_buf(private_key, strlen(private_key));
    if (pKeyBio == NULL){
        return "";
    }
    RSA* pRsa = RSA_new();
    pRsa = PEM_read_bio_RSAPrivateKey(pKeyBio, &pRsa, NULL, NULL);
    if ( pRsa == NULL ){
         BIO_free_all(pKeyBio);
         return "";
    }
    int nLen = RSA_size(pRsa);
    char* pEncryptBuf = new char[nLen];
    memset(pEncryptBuf, 0, nLen);
    int nClearDataLen = strClearData.length();
    uchar* pClearData = (uchar*)strClearData.data();
    int nSize = RSA_private_encrypt(nClearDataLen,
                                    pClearData,
                                    (uchar*)pEncryptBuf,
                                    pRsa,
                                    RSA_PKCS1_PADDING);

    QString strEncryptData = "";
    if ( nSize >= 0 ){
         QByteArray arry(pEncryptBuf, nSize);
         strEncryptData = arry.toBase64();
    }
         // освобождаем память
    delete[] pEncryptBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);
    return strEncryptData;
}


QString Crypt::rsa_pub_decrypt_base64(const QByteArray& strDecryptData)
{

         // Расшифровка открытого ключа
    char public_key[] = "-----BEGIN PUBLIC KEY-----\n"\
            "MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAM6VxBkoxRg0Xa+BqZP4pqRa6scNCVLO\n"\
            "6FME4XiYKjSHwiX8NNDxzipiAyPVKEvhNzs7Na3jD9a9CLlMrM1+SxsCAwEAAQ==\n"\
            "-----END PUBLIC KEY-----";

         // Загружаем строковый ключ в био объект
    BIO* pKeyBio = BIO_new_mem_buf(public_key, strlen(public_key));
    if (pKeyBio == NULL){
        return "";
    }

    RSA* pRsa = RSA_new();

    pRsa = PEM_read_bio_RSA_PUBKEY(pKeyBio, &pRsa, NULL, NULL);


    if ( pRsa == NULL ){
        BIO_free_all(pKeyBio);
        return "";
    }
    int nLen = RSA_size(pRsa);
    char* pClearBuf = new char[nLen];
    memset(pClearBuf, 0, nLen);
         // Расшифровать
    //strDecryptData = QByteArray::fromBase64(strDecryptData);
    int nDecryptDataLen = strDecryptData.length();
    uchar* pDecryptData = (uchar*)strDecryptData.data();
    int nSize = RSA_public_decrypt(nDecryptDataLen,
                                   pDecryptData,
                                   (uchar*)pClearBuf,
                                   pRsa,
                                   RSA_PKCS1_PADDING);
    QString strClearData = "";
    if ( nSize >= 0 ){
        strClearData = QByteArray(pClearBuf, nSize);
    }

         // освобождаем память
    delete[] pClearBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);
    return strClearData;
}

void Crypt::cryptFile(){
    QFile *file = new QFile("hero.docx");
    QFile *filenew = new QFile("myfile.enc");

      QString data;
     QByteArray arr;

    file->open(QFile::ReadWrite);

    if(file->isOpen()){

     data = rsa_pri_encrypt_base64(file->readAll());
       arr = data.toUtf8();


       filenew->open(QFile::ReadWrite);
        if(filenew->isOpen())
        {
            filenew->write(arr);
          filenew->close();
        }
        file->close();

    }

   file->remove();
}
void Crypt::decryptFile(){
    QFile *file = new QFile("myfile.enc");
    QFile *filenew = new QFile("hero.docx");//dont decrypt all

    QString *decData = new QString;
    QByteArray byt;

    file->open(QFile::ReadWrite);

    if(file->isOpen()){
        *decData = rsa_pub_decrypt_base64(file->readAll());
        byt = decData->toUtf8();


           filenew->open(QFile::ReadWrite);
           if(file->isOpen()){
               filenew->write(byt);
               filenew->close();
           }
       file->close();
    }

   file->remove();
}
