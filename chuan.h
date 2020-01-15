#ifndef CHUAN_H
#define CHUAN_H

#include <QWidget>
#include <QSerialPort>
#include<QSerialPortInfo>
#include <QTimer>
#include<QStandardItem>
#include "proto645.h"


namespace Ui {
class Chuan;
}

class Chuan : public QWidget
{
    Q_OBJECT

public:
    explicit Chuan(QWidget *parent = 0);
    ~Chuan();
    Ui::Chuan *ui;


private slots:
    void on_btnOpen_clicked();
    void readComDataSlot();
    void initPort();
    void on_btnSend_clicked();
    void StringToHex(QString str, QByteArray & senddata);
    char ConvertHexChar(char ch);
    void GetMacAddr(QString macAddr,unsigned char[]);
    void FormatIp(QString ip ,QString port,QByteArray & dataArr);
    void StringToASCAL(QString str,QString port,QByteArray & dataArr);
    void on_ipbtn_clicked();
    void on_macbtn_clicked();
    void ReFindPort();
    void on_searchIp_clicked();
    void on_searchAddr_clicked();

public slots:
      void setIpText(QString ip,QString port);
      void setAddrText(QString addr);
private:
    QTimer *timer;
    QTimer *comTimer;
    QSerialPort *my_serialport;
    bool comIsOpen =false; 
    Proto645 *proto645;
};

#endif // CHUAN_H
