#ifndef NETWORK_H
#define NETWORK_H
#include <QString>

class Network
{
public:
    Network();
    QString rsa_pri_encrypt_base64(const QString &strClearData);

    QString rsa_pub_decrypt_base64(const QString &strDecryptData);

};

#endif // NETWORK_H
