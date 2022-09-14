#ifndef CRYPTOGRAPH_H
#define CRYPTOGRAPH_H

#include <QObject>
#include <QByteArray>
class Cryptograph : public QObject
{
    Q_OBJECT
public:
    explicit Cryptograph(QObject *parent = nullptr);
public slots:
    void encrypt();
    void decrypt();

signals:

};

#endif // CRYPTOGRAPH_H
