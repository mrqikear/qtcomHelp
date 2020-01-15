#include "debug.h"
#include<QDebug>
#include<QString>

debug::debug(QObject *parent) : QObject(parent)
{



}



void debug::debug_str(QByteArray arr)
{
    int size = arr.size();
    if (size == 0)
    {
        return;
    }
    unsigned short i;
    QString str;
    char pHex[4];
    for (i = 0; i < size; i++)
    {
        sprintf(pHex, "%02x ", arr.at(i));
        str.append(pHex);
    }
    qDebug() << str;
}




void debug::debug_str(QString msg, unsigned char *pBuf, unsigned short size) {
    if ((NULL == pBuf) || (0 == size))
    {
        return;
    }
    qDebug() << msg << endl;
    unsigned short i;
    QString str = "";
    char pHex[4];
    for (i = 0; i < size; i++)
    {
        sprintf(pHex, "%02x ", pBuf[i] & 0xff);
        //qDebug()<<"pHex:"<<endl;
        //str += pHex;
        str.append(pHex);
    }
    qDebug() << str;
    qDebug() << msg << endl;
}



void debug::debug_str(QString msg, const unsigned char *pBuf, unsigned short size) {
    if ((NULL == pBuf) || (0 == size))
    {
        return;
    }
    qDebug() << msg << endl;
    unsigned short i;
    QString str = "";
    char pHex[4];
    for (i = 0; i < size; i++)
    {
        sprintf(pHex, "%02x ", pBuf[i] & 0xff);
        //qDebug()<<"pHex:"<<endl;
        //str += pHex;
        str.append(pHex);
    }
    qDebug() << str;
    qDebug() << msg << endl;
}

void debug::debug_str(QString msg, QByteArray arr)
{
    int size = arr.size();
    if (size == 0)
    {
        return;
    }
    unsigned short i, j;
    QString str= "";
    char pHex[4];
    char log[4096];
    int quo = size / 32, rem = size % 32, offset = 0, tmp = 0;
    qDebug() << "start<<<<<<<<<<" << msg << "<<<<<<<<<<" <<  endl;
    qDebug() << "rem:" << rem << " quo:" << quo << endl;
    for (int k = 0; k < size; k++) {
        sprintf(&log[tmp], "%02X ", arr.at(k) & 0xff);
        tmp += 3;
    }
    log[tmp] = '\0';
    qDebug("allstr=%s\r\n", log);
    for (j = 0; j < quo; j++) {
        for (i = 0; i < 32; i++) {
            sprintf(pHex, "%02x ", arr.at(offset++) & 0xff);
            str.append(pHex);
        }
        qDebug() << str << endl;
        str = "";
    }
    for (i = 0; i < rem; i++) {
        sprintf(pHex, "%02x ", arr.at(offset++) & 0xff);
        str.append(pHex);
    }
    if (str != "") {
        qDebug() << str << endl;
    }
    qDebug() << ">>>>>>>>>>" << msg << ">>>>>>>>>>" <<  endl;

}


QString debug::HexToQString(unsigned char *pbuf, unsigned short size){


    if ((NULL == pbuf) || (0 == size))
    {
        return "erro data";
    }
    unsigned short i;
    QString str = "";
    char pHex[4];
    for (i = 0; i < size; i++)
    {
        sprintf(pHex, "%02x ", pbuf[i] & 0xff);
        str.append(pHex);
    }
    return str;
}
