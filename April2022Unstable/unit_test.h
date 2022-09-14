#ifndef UNIT_TEST_H
#define UNIT_TEST_H


#include <QObject>

class Test_Smart : public QObject
{
    Q_OBJECT
public:
    explicit Test_Smart(QObject *parent = 0);

public slots:
    void max();// for all functions
    void test_object_transf();// transfer random objects
    bool trfals();// true or false
    void super_load(); //max load
};


#endif // UNIT_TEST_H
