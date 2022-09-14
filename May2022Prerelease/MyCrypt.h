#ifndef MYCRYPT_H
#define MYCRYPT_H
#include <QObject>
class Crypt:public QObject
{
public:

    QString cryptString(QString &data)
    {
        QString key[64] = {"a", "'", "[", "]", "{", "}", "!", "@", "#", ",", ":", ";", "=", "+", "-", "_", ")", "(", "*", "&", "/", "?"
                          "^", "%", "$", "`", "~", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r"
                          "s", "t", "u", "v", "w", "x", "y", "z"};//64 bits key for passwords
        QString result = "";

        return result;
    }

    QString decryptString(QString &descryptData)
    {

        QString result = "";
        for(int j = 0; j < descryptData.length(); j++)
        {
            result.append(QString(QChar(descryptData[j] = descryptData[j])));
        }
        return descryptData;
    }
};

#endif // MYCRYPT_H
