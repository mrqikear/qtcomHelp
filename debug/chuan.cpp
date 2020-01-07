#include "chuan.h"
#include "ui_chuan.h"
#include <QDebug>
#include<QTimer>
#include<QSerialPort>
#include<QDialog>
#include<QLabel>
#include<QMessageBox>
#include<QStandardItem>
#include<QIcon>
#include<QSize>
#include "proto645.h"
#include "define645.h"
#include "debug.h"
Chuan::Chuan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chuan)
{
    ui->setupUi(this);
    setWindowTitle("645通讯协议助手(prod by mrqi)");
   //执行函数
    initPort();
    //设置应用程序图标
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/image/icon.png")));
    this->setWindowIcon(icon);
     //this->setIconSize(QSize(256,256));
    ui->teReceiveData->setStyleSheet("background-color:white");


    comTimer = new QTimer();
    comTimer->stop();
    comTimer->setInterval(10000);
    connect(comTimer,SIGNAL(timeout()),this,SLOT(initPort()));
    comTimer->start();

}

Chuan::~Chuan()
{
    delete ui;
}
/***********************串口初始化*****************************/
void Chuan::initPort()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
       {
           //qDebug()<<"Name:"<<info.portName();
           //qDebug()<<"Description:"<<info.description();
           //qDebug()<<"Manufacturer:"<<info.manufacturer();

           //这里相当于自动识别串口号之后添加到了cmb，如果要手动选择可以用下面列表的方式添加进去
           QSerialPort serial;
           serial.setPort(info);
           if(serial.open(QIODevice::ReadWrite))
                   {
                        //清空之前所有串口
                       ui->cmbPortName->clear();
                       //将串口号添加到cmb
                       ui->cmbPortName->addItem(info.portName());
                       //关闭串口等待人为(打开串口按钮)打开
                       serial.close();
                   }
               }

               QStringList baudList;//波特率
               QStringList parityList;//校验位
               QStringList dataBitsList;//数据位
               QStringList stopBitsList;//停止位
               baudList<<"50"<<"75"<<"100"<<"134"<<"150"<<"200"<<"300"
                          <<"600"<<"1200"<<"1800"<<"2400"<<"4800"<<"9600"
                         <<"14400"<<"19200"<<"38400"<<"56000"<<"57600"
                        <<"76800"<<"115200"<<"128000"<<"256000";

                   ui->cmbBaudRate->addItems(baudList);
                   ui->cmbBaudRate->setCurrentIndex(12);

                   parityList<<"无"<<"奇"<<"偶";
                   parityList<<"标志";
                   parityList<<"空格";

                   ui->cmbParity->addItems(parityList);
                   ui->cmbParity->setCurrentIndex(0);

                   dataBitsList<<"5"<<"6"<<"7"<<"8";
                   ui->cmbDataBits->addItems(dataBitsList);
                   ui->cmbDataBits->setCurrentIndex(3);

                   stopBitsList<<"1";
                   stopBitsList<<"1.5";
                   stopBitsList<<"2";

                   ui->cmbStopBits->addItems(stopBitsList);
                   ui->cmbStopBits->setCurrentIndex(0);

                   //设置按钮可以被按下
                   ui->btnOpen->setCheckable(true);



 }

/****************************串口设置******************************/





void Chuan::on_btnOpen_clicked()
{
    if(ui->btnOpen->text() == "打开串口")
       {
           my_serialport = new QSerialPort(this);

           this->comIsOpen =true;

           //设置串口号
           my_serialport->setPortName(ui->cmbPortName->currentText());
           //以读写方式打开串口
           //qDebug()<<my_serialport->open(QIODevice::ReadWrite)<<endl;
           ui->btnOpen->setText("关闭串口");
           ui->btnSend->setDisabled(false); //可以几点发送按钮
           if(my_serialport->open(QIODevice::ReadWrite))
           {
               //设置波特率
               my_serialport->setBaudRate(ui->cmbBaudRate->currentText().toInt());
               //设置数据位
               my_serialport->setDataBits(QSerialPort::Data8);
               //设置校验位
               my_serialport->setParity(QSerialPort::NoParity);
               //设置流控制
               my_serialport->setFlowControl(QSerialPort::NoFlowControl);
               //设置停止位
               my_serialport->setStopBits(QSerialPort::OneStop);

               //每秒读一次
               timer = new QTimer(this);
               connect(timer, SIGNAL(timeout()), this, SLOT(readComDataSlot()));
               timer->start(1000);

           }
           else
           {
               QMessageBox::about(NULL, "提示", "串口没有打开！");
               return;
           }
       }
       else
       {
           timer->stop();
            //QStandardItem::setSelectable;
           ui->btnOpen->setText("打开串口");
           ui->btnSend->setDisabled(true); //发送按键不可编辑
           my_serialport->close();
           this->comIsOpen = false;//串口关闭标识
       }
}
/****************************数据传输******************************/
void Chuan::readComDataSlot()
{
    //读取串口数据
    QByteArray readComData = my_serialport->readAll();


    //将读到的数据显示到数据接收区的te中
    if(readComData != NULL)
    {
        ui->teReceiveData->append(readComData);
        //qDebug()<<"接收到信息";

    }
    QString q;
    q=QString(readComData);


    //清除缓冲区
    readComData.clear();
    //QString a=readComData;

}

void Chuan::on_btnSend_clicked()
{
   if(my_serialport->isOpen()){

       QString str=ui->teSendData->toPlainText();
       QByteArray sendata;
       StringToHex(str,sendata);
       //写入缓冲区
       qDebug()<< sendata <<endl;
       my_serialport->write(sendata);
   }else{
       QMessageBox::about(NULL, "提示", "老铁!串口没有打开");
   }
}

void  Chuan::StringToHex(QString str, QByteArray & senddata)  //字符串转换成16进制数据0-F
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        //char lstr,
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);        
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}

char Chuan::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
            return ch-0x30;
        else if((ch >= 'A') && (ch <= 'F'))
            return ch-'A'+10;
        else if((ch >= 'a') && (ch <= 'f'))
            return ch-'a'+10;
        else return ch-ch;//不在0-f范围内的会发送成0
}




/**
  设置ip地址和端口号
 * @brief Chuan::on_ipbtn_clicked
 */
void Chuan::on_ipbtn_clicked()
{
    if(!this->comIsOpen){
         QMessageBox::about(NULL, "提示", "串口没有打开");
         return;
    }

}

/**
    设置终端地址
 * @brief Chuan::on_macbtn_clicked
 */
void Chuan::on_macbtn_clicked()
{
   if(!this->comIsOpen){
        QMessageBox::about(NULL, "提示", "串口没有打开");
        return;
   }

       QString macAddr = ui->macaddr->text();
       macAddr.remove(QRegExp("^ +\\s*"));
    if(macAddr.isEmpty()){
         QMessageBox::about(NULL, "提示", "设置终端命令终端不能为空");
         return;
    }

    Proto645 proto645;
    QString Zore = "000000000000";  //集中器地址没有哦
    QByteArray ba = Zore.toLatin1();
    unsigned char * addr;
    addr = (unsigned char*)ba.data();
    //------------------------------------------用户数据

    unsigned char *p645data = NULL;
    unsigned short n645len = 0;
    MRS_PROTO645_FRAME_INF frame;
    proto645.InitProto645Frame(frame);

    unsigned char macAddrArr[6] ={0};
    this->GetMacAddr(macAddr,macAddrArr);
    frame.ucDataLength =6;
    frame.pData =macAddrArr;
    frame.ulDi = MRS_645_IDENTIFICATION_SET_MAC_ADDR;
    proto645.Gen645Addr(addr, 12, frame.aucAddr, HI_METER_ADDR_LEN);
    qDebug()<<"pFrameInf->ulDi:"<<frame.ulDi<<endl;
    qDebug()<<"pFrameInf->ucDataLength:"<<frame.ucDataLength<<endl;
    qDebug()<<"frame.pData[0]:"<<frame.pData[0]<<endl;
    qDebug()<<"frame.pData[1]:"<<frame.pData[1]<<endl;
    proto645.mrsGen645Frame(&frame, &p645data,&n645len);
    debug debug;
    debug.debug_str("p645:",p645data,n645len);

}



/**
 * 获取终端地址并且反转
*/
  void Chuan::GetMacAddr(QString macAddr,unsigned char arr[]){
        QByteArray sendata;
        if(macAddr.length() > 12){
            macAddr = macAddr.left(12);
        }
        this->StringToHex(macAddr,sendata);
        //电表地址长度为6位
        int index =5;
        for(int i=0;i<6;i++){
          arr[i] = sendata[index];
          index--;
        }
    }
