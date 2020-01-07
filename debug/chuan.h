#ifndef CHUAN_H
#define CHUAN_H

#include <QWidget>
#include <QSerialPort>
#include<QSerialPortInfo>
#include <QTimer>
#include<QStandardItem>


namespace Ui {
class Chuan;
}

class Chuan : public QWidget
{
    Q_OBJECT

public:
    explicit Chuan(QWidget *parent = 0);
    ~Chuan();


private slots:
    void on_btnOpen_clicked();
    void readComDataSlot();
    void initPort();
    void on_btnSend_clicked();
    void StringToHex(QString str, QByteArray & senddata);
    char ConvertHexChar(char ch);
    void GetMacAddr(QString macAddr,unsigned char[]);

    void on_ipbtn_clicked();

    void on_macbtn_clicked();

private:
    Ui::Chuan *ui;
    QTimer *timer;
    QTimer *comTimer;
    QSerialPort *my_serialport;
    bool comIsOpen =false;
};

#endif // CHUAN_H
