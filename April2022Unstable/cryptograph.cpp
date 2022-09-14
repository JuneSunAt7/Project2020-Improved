#include "cryptograph.h"
#include "RC5Simple.h"
#define KEY_LEN 128
Cryptograph::Cryptograph(QObject *parent) : QObject(parent)
{

}

void Cryptograph::encrypt() {
    // Define key as array
    unsigned char key[KEY_LEN];
    for(int i=0; i<KEY_LEN; i++)
     key[i]=i*2;
    // Define key as vector
    vector<unsigned char> v_key(KEY_LEN);
    // Convert array to vector

    for(int i=0; i<KEY_LEN; i++)

     v_key[i]=key[i];

    RC5Simple rc5;
    rc5.RC5_SetKey(v_key);


   rc5.RC5_EncryptFile("lib_ptr.dl", "lib_ptr.dll");

}
void Cryptograph::decrypt(){
    unsigned char key[KEY_LEN];
    for(int i=0; i<KEY_LEN; i++)
     key[i]=i*2;
    // Define key as vector
    vector<unsigned char> v_key(KEY_LEN);
    // Convert array to vector

    for(int i=0; i<KEY_LEN; i++)

     v_key[i]=key[i];

    RC5Simple rc5;
    rc5.RC5_SetKey(v_key);
    rc5.RC5_DecryptFile("lib_ptr.dll", "crypt.txt"); //debug name
}
