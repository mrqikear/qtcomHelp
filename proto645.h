#ifndef PROTO645_H
#define PROTO645_H

#include "define645.h"
#include <QString>
#include <QWidget>

namespace Ui{
class Proto645;
}
class Proto645 :public QObject
{

  Q_OBJECT;

public:
    Proto645();

    MRS_645_PROTO_CTX_STRU * mrs645GetContext(unsigned char buf_id);

    unsigned int mrs645ProtoInit(MRS_645_PROTO_CTX_STRU& pstCtx);   // 初始化
    unsigned int mrs645ProtoStream2Buffer(unsigned char* pucStream, unsigned short usStreamLen, unsigned char buf_id);
    unsigned int mrs645ProtoStreamInput(unsigned char* pucStream, unsigned short usStreamLen,
                                            MRS_ONE_RAW_FRAME_STRU* pstFrame, unsigned char buf_id);

    unsigned int mrs645ProtoStreamInputCheck(bool bDiscardOldStream, unsigned char buf_id);

    // 在缓冲区中查找有效的645帧并输出帧头偏移及帧长
    unsigned int mrsFind645Frame(unsigned char* in_buf, short in_len,
                                unsigned short *start, unsigned short *out_len);
    // 645帧解码
    void mrs645DataDecode(unsigned char * buf, unsigned int len);
    void mrs645DataEncode(unsigned char * buf, unsigned int len);
    void Decode645Frame(unsigned char* pucDatagram, unsigned short usDatagramSize);                                         //解析645数据帧

    // 电表地址预处理: 上行帧97表地址高位字节AAH->00H
    void mrsMeterAddrULPreProc(unsigned char *aucDstAddr, unsigned char *aucSrcAddr, unsigned char ucProtocol, unsigned char ucCtrl);

    // 电表地址预处理: 97表地址高位字节AAH->00H
    void mrsMeterAddrPreProc(unsigned char *aucDstAddr, unsigned char *aucSrcAddr, unsigned char ucProtocol);

    // 地址pDstAddr是否与pSrcAddr匹配(通配符0xAA)
    // 去掉pSrcAddr高位字节的AAH之后，用低位字节和pDstAddr比较(不关注pDstAddr高位字节的AAH)
    bool mrsMeterAddrMatch(unsigned char *pSrcAddr, unsigned char *pDstAddr);

    unsigned int mrsGen645Frame(MRS_PROTO645_FRAME_INF *pFrameInf, unsigned char **ppFrame, unsigned short *pFrameLen);
    unsigned int mrsGetFrame645MeterAddr(unsigned char *pucFrame, unsigned short usFrameLength, unsigned char *pucMeterAddr);
    unsigned int mrsToolsCheck645Frame(unsigned char*, unsigned short);
    unsigned short mrsToolsCalcCheckSum2(unsigned char* ptr, unsigned short len);
    unsigned char* mrsToolsStreamFindByte(unsigned char* ptr, unsigned short len, unsigned char v);

    unsigned int Create645Frame(unsigned char* paddr, unsigned short addrlen, unsigned int udi, unsigned char* puserdata,
                          unsigned short userdatalen, unsigned char **ppFrame, unsigned short *pFrameLen);                  //创建645数据帧
    void Gen645Addr(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen);      //根据字符串生成645转发协议帧格式地址
    void Dec645Addr(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen);      //通过645转发协议帧格式地址转换成字符串
    void Hexs2Bcds(unsigned char * src, unsigned char * dst, short len);
    void HexInverts(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen);
    unsigned int mrsIntToBcd(unsigned int data,unsigned char bcd[],unsigned char len);
    unsigned int GetBcd2Int(const unsigned char bcd[], unsigned char len);
    float GetBcd2float(const unsigned char bcd[], unsigned char len = 4, float fdiv = 1000.0);
    void InitProto645Frame(MRS_PROTO645_FRAME_INF& frame, int type);      //初始化645帧结构
private:
    void Gen645Data(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen);      //生成645数据
    void Dec645Data(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen);      //解析645数据
    unsigned char GetCtrl(MRS_645_CTRL_STRU& ctrl);             //获取控制码
    void initProtoCtx();                                        //
    unsigned int mrs645ProtoBuffer(MRS_645_PROTO_CTX_STRU * pstCtx,MRS_ONE_RAW_FRAME_STRU * pstFrame);
    unsigned char *Get645FrameData(unsigned char* pucDatagram, unsigned short usDatagramSize, MRS_645_FRAME_STRU* pstFrame, unsigned int *udi, unsigned char *nlen);
    unsigned int MRS_Proto645Dec( unsigned char* pucDatagram, unsigned short usDatagramSize, MRS_645_FRAME_STRU* pstFrame );

    MRS_645_PROTO_CTX_STRU pst645ProtoCtx[MRS_645BUF_MAX];

   void SendIpportSignal(unsigned char *ucframedata,unsigned char nlen);
   void SendAddrSignal(unsigned char *ucframedata,unsigned char nlen);
signals:
    void emitIpportSignal(QString ip,QString port);
    void emitAddrSignal(QString addr);

};

#endif // PROTO645_H
