#include "proto645.h"
#include "define645.h"
#include <QMutex>
#include <QString>
#include <QDebug>
#include <QWidget>
#include "debug.h"
const float DIV_DLT_DIVISOR_TEN = 10.0;
const float DIV_DLT_DIVISOR_HUNDRED = 100.0;
const float DIV_DLT_DIVISOR_THOUSAND = 1000.0;
const float DIV_DLT_DIVISOR_TEN_THOUSAND = 10000.0;
const unsigned char TMP_BUF_LEN = 128;


unsigned char Char2Hex(unsigned char x)
{
    if((x >= 0) && (x <= 9))
    {
        x += 0x30;
    }
    else if((x >= 10) && (x <= 15))//Capital
    {
        x += 0x37;
    }
    else
    {
        x = 0xff;
    }

    return x;
}

unsigned char* DTH(unsigned char src, unsigned char *dst)
{
    dst[0] = src / 16;
    dst[1] = src % 16;
    return dst;
}

unsigned char Hex2Char(unsigned char x)
{
    if ((x >= '0') && (x <= '9'))
    {
        return x - 0x30;
    }
    else if ((x >= 'A') && (x <= 'F'))
    {
        return x - 'A' + 10;
    }
    else if ((x >= 'a') && (x <= 'f'))
    {
        return x - 'a' + 10;
    }
    else
    {
        return 0x00;
    }
}

unsigned char HTD(unsigned char *x)
{
    return (unsigned char)(16 * Hex2Char(x[0]) + Hex2Char(x[1]));
}

// HEX码流逆序
void HexInvert(unsigned char * buf, short len)
{
    if ((buf != NULL) && (len > 0))
    {
        unsigned char a = 0;
        short i = 0;

        for(i = 0; i < (len / 2); i++)
        {
            a = buf[i];
            buf[i] = buf[len - i - 1];
            buf[len - i - 1] = a;
        }
    }
}

void Proto645::Hexs2Bcds(unsigned char * src, unsigned char * dst, short len)
{
    if ((src != NULL) && (dst != NULL) && (len > 0))
    {
        unsigned char * psrc = src;
        unsigned char * pdst = dst;
        for (short i = 0; i < (len / 2); i++)
        {
            *pdst = HTD(psrc);
            pdst++;
            psrc += 2;
        }
        pdst = dst;
        HexInvert(pdst, (len / 2));
    }
}

void Bcd2Chars(unsigned char * src, unsigned char * dst, short len)
{
    if ((src != NULL) && (dst != NULL) && (len > 0))
    {
        unsigned char * pdst = dst;
        unsigned char * psrc = src;
        HexInvert(psrc, len);
        for (short i = 0; i < len; i++)
        {
            DTH(*psrc, pdst);
            pdst += 2;
            psrc++;
        }
    }
}

void Chars2Hexs(unsigned char* src, unsigned char* dst,unsigned short len)
{
    if ((src != NULL) && (dst != NULL) && len > 0)
    {
        unsigned char* psrc = src;
        unsigned char* pdst = dst;
        for (unsigned short i = 0; i < len; i++, pdst++, psrc++)
        {
            *pdst = Char2Hex(*psrc);
        }
    }
}

//*****************************************************************************
// 函数名称: mrsIsLetterValid
// 功能描述: 判断是否是合法数字
//
// 参数说明:
//    pStr 被判断的字符串
//    ucType 判断的进制类型依据
//
// 返 回 值:
//    TRUE  合法
//    FALSE 非法
//
// 调用要求:
// 调用举例:
// 作    者: fengxiaomin/00209182 [2014-1-14]
//*****************************************************************************
bool mrsIsLetterValid(char *pStr, unsigned char ucType)
{
    Q_UNUSED(ucType);
    if (!pStr)
    {
        return HI_FALSE;
    }

    if ((*pStr >= '0') && (*pStr <= '9'))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

//*****************************************************************************
// 函数名称: mrsStrToInt
// 功能描述:将字符串转换成整数
//
// 参数说明:
//    pStr 被转换的字符串
//    ucType 转换的进制类型
//
// 返 回 值:
//    转换后的整数
//
// 调用要求:
// 调用举例:
// 作    者: fengxiaomin/00209182 [2014-1-14]
//*****************************************************************************
unsigned int mrsStrToInt(char* pStr, unsigned char ucType)
{
    unsigned int ulData = 0;

    if (!pStr)
    {
        return ulData;
    }

    while(mrsIsLetterValid(pStr, ucType) && (*pStr != '\0'))
    {
        ulData = ucType * ulData + static_cast<unsigned char>(*pStr - '0');
        pStr++;
    }

    return ulData;
}

/*将整数转化成定长BCD码,并逆序*/
unsigned int Proto645::mrsIntToBcd(unsigned int data,unsigned char bcd[],unsigned char len)
{
    unsigned int i = 0;
    unsigned int remain = data;
    unsigned int tail = 0;

    if (!bcd)
    {
        return static_cast<unsigned int>(-1);
    }

    for (i = 0; i < len; i++)
    {
        tail = remain % 100;
        remain /= 100;

        bcd[i] = static_cast<unsigned char>(tail / 10 * 16 + tail % 10);
    }
    return 0;
}

/*将定长BCD码转化成整数,并逆序*/
unsigned int mrsBcdToInt(const unsigned char bcd[], unsigned char len)
{
    unsigned int tail = 0;

    if (!bcd && len > 0)
    {
        return static_cast<unsigned int>(-1);
    }

    tail = ((bcd[0] % 16) + ((bcd[0] / 16) * 10));
    for (unsigned int i = 1; i < len; i++)
    {
        tail += ((bcd[i] % 16) + ((bcd[i] / 16) * 10)) * pow(100 , i);
    }
    return tail;
}

unsigned int Proto645::GetBcd2Int(const unsigned char bcd[], unsigned char len)
{
    if (!bcd && len > 0)
    {
        return static_cast<unsigned int>(-1);
    }

    for (int i = 0; i < len; i++)
    {
        if (bcd[i] != 0xFF)
        {
            return mrsBcdToInt(bcd, len);
        }
    }

    return static_cast<unsigned int>(-1);
}

float Proto645::GetBcd2float(const unsigned char bcd[], unsigned char len, float fdiv)
{
    if (!bcd && len > 0)
    {
        return 0.0;
    }

    unsigned int utemp = GetBcd2Int(bcd, len);
    if(utemp != static_cast<unsigned int>(-1))
    {
        return utemp / fdiv;
    }

    return 0.0;
}

unsigned char mrsToolsGet645Ver(unsigned char ucFn)
{
    unsigned char ret = METER_PROTO_645_2007;

    if ((!(ucFn & 0x10) && (ucFn != MRS_COLLECTOR_07_PROTOCOL_CONTROL)
        && (ucFn != MRS_COLLECTOR_BOARDCAST_TIMEING_CONTROL))
        || (MRS_MAXIMUM_DEMAND_CLEAR_CONTROL == (ucFn & 0x1F)))
    {
        ret = METER_PROTO_645_1997;
    }

    return ret;
}

Proto645::Proto645()
{
    initProtoCtx();
}

void Proto645::initProtoCtx()
{
    for(int i = 0; i < MRS_645BUF_MAX; i++)
    {
        // 645协议 初始化
        mrs645ProtoInit(pst645ProtoCtx[i]);
    }
}

MRS_645_PROTO_CTX_STRU * Proto645::mrs645GetContext(unsigned char buf_id)
{
    return &pst645ProtoCtx[buf_id % MRS_645BUF_MAX];
}

// 初始化
unsigned int Proto645::mrs645ProtoInit(MRS_645_PROTO_CTX_STRU& pstCtx)
{
    pstCtx.reserved = 0;
    pstCtx.usRcvBufferSize = 0;
    pstCtx.pucRcvBuffer = static_cast<unsigned char *>(mrsToolsMalloc(MRS_PROTO_MR_DATAGRAM_BUF_MAX));

    if (pstCtx.pucRcvBuffer == NULL)
    {
        return HI_ERR_MALLOC_FAILUE;
    }

    mrsToolsMemZero_s(pstCtx.pucRcvBuffer, MRS_PROTO_MR_DATAGRAM_BUF_MAX, MRS_PROTO_MR_DATAGRAM_BUF_MAX);

    return HI_ERR_SUCCESS;
}

unsigned int Proto645::mrs645ProtoStream2Buffer(unsigned char* pucStream, unsigned short usStreamLen, unsigned char ucBufId)
{
    MRS_645_PROTO_CTX_STRU * pst645Ctx = mrs645GetContext(ucBufId);

    // 判断缓冲区是否已满
    if ((usStreamLen + pst645Ctx->usRcvBufferSize) > MRS_PROTO_MR_DATAGRAM_BUF_MAX)
    {
        mrs645ProtoStreamInputCheck(HI_TRUE, ucBufId);
        return HI_ERR_BAD_DATA;
    }

    mrsToolsMemcpy_s(pst645Ctx->pucRcvBuffer + pst645Ctx->usRcvBufferSize,MRS_PROTO_MR_DATAGRAM_BUF_MAX-pst645Ctx->usRcvBufferSize, pucStream, usStreamLen);
    pst645Ctx->usRcvBufferSize = static_cast<unsigned short>(pst645Ctx->usRcvBufferSize + usStreamLen);

    return HI_ERR_SUCCESS;
}

unsigned int Proto645::mrs645ProtoStreamInput(unsigned char* pucStream, unsigned short usStreamLen,
                                         MRS_ONE_RAW_FRAME_STRU* pstFrame, unsigned char buf_id)
{
    unsigned int ulRet = HI_ERR_SUCCESS;

    ulRet = mrs645ProtoStream2Buffer(pucStream, usStreamLen, buf_id);
    if (HI_ERR_SUCCESS == ulRet)
    {
        MRS_645_PROTO_CTX_STRU * pst645Ctx = mrs645GetContext(buf_id);
        ulRet = mrs645ProtoBuffer(pst645Ctx, pstFrame);
    }

    return ulRet;
}

unsigned int Proto645::mrs645ProtoStreamInputCheck(bool bDiscardOldStream, unsigned char buf_id)
{
    MRS_645_PROTO_CTX_STRU * pst645Ctx = NULL;
    pst645Ctx = mrs645GetContext(buf_id);

    if(pst645Ctx)
    {
        if(bDiscardOldStream)
        {
            pst645Ctx->usRcvBufferSize = 0;
        }
    }

    return HI_ERR_SUCCESS;
}


// 在缓冲区中查找有效的645帧并输出帧头偏移及帧长
unsigned int Proto645::mrsFind645Frame(unsigned char* in_buf, short in_len,
                            unsigned short *start, unsigned short *out_len)
{
    unsigned int ret = HI_ERR_FAILURE;
    unsigned char* buf = in_buf;

    if((!in_buf) || (!start) || (!out_len))
    {
        return HI_ERR_INVALID_PARAMETER;
    }

    while (in_len > 0)
    {
        unsigned char* head = NULL;
        head = static_cast<unsigned char*>(mrsToolsStreamFindByte(buf, static_cast<unsigned short>(in_len), 0x68));

        if (head != NULL)
        {//找到帧
            unsigned short frame_len = 0;

            in_len -= static_cast<short>(head - buf);
            buf = head;

            if (in_len < 12)
            {
                ret = HI_ERR_BAD_DATA;
                break;
            }

            frame_len = static_cast<unsigned short>(buf[9] + 12);

            //超长帧
            if (frame_len > MRS_PROTO645_DATAGRAM_LEN_MAX)
            {
                buf++;
                in_len--;
                continue;
            }

            if(in_len >= frame_len)
            {
                if(HI_ERR_SUCCESS == mrsToolsCheck645Frame(buf,frame_len))
                {
                    *start = static_cast<unsigned short>(buf - in_buf);
                    *out_len = frame_len;

                    //找到了一个完整645帧;
                    ret = HI_ERR_SUCCESS;
                    break;
                }
                else
                {
                    buf++;
                    in_len--;
                    continue;
                }
            }
            else
            {
                buf++;
                in_len--;
                continue;
            }

        }
        else
        {
            ret = HI_ERR_BAD_DATA;
            break;
        }
    }

    return ret;
}




void Proto645::mrs645DataDecode(unsigned char * buf, unsigned int len)
{
    while(len--)
    {
        buf[len] -= MRS_645_FRAME_HEX33;
    }
    return;
}

void Proto645::mrs645DataEncode(unsigned char * buf, unsigned int len)
{
    while(len--)
    {
        buf[len] += MRS_645_FRAME_HEX33;
        // buf[len] += 0x00;
    }
    return;
}

// 电表地址预处理: 上行帧97表地址高位字节AAH->00H
void Proto645::mrsMeterAddrULPreProc(unsigned char *aucDstAddr, unsigned char *aucSrcAddr, unsigned char ucProtocol, unsigned char ucCtrl)
{
    if (ucCtrl & MRS_645_FRAME_CONTROL_DIR_UP)
    {
        mrsMeterAddrPreProc(aucDstAddr, aucSrcAddr, ucProtocol);
    }
    else
    {
        mrsToolsMemcpy_s(aucDstAddr, HI_METER_ADDR_LEN, aucSrcAddr, HI_METER_ADDR_LEN);
    }
}

// 电表地址预处理: 97表地址高位字节AAH->00H
void Proto645::mrsMeterAddrPreProc(unsigned char *aucDstAddr, unsigned char *aucSrcAddr, unsigned char ucProtocol)
{
    if (METER_PROTO_645_1997 != ucProtocol)
    {
        mrsToolsMemcpy_s(aucDstAddr, HI_METER_ADDR_LEN, aucSrcAddr, HI_METER_ADDR_LEN);
    }
    else
    {
        int i;

        for (i = HI_METER_ADDR_LEN - 1; i >= 0; i--)
        {
            if (aucSrcAddr[i] == MRS_645_METER_ADDR_WILDCARDS)
            {
                aucDstAddr[i] = 0;
                continue;
            }

            break;
        }

        for (; i >= 0; i--)
        {
            aucDstAddr[i] = aucSrcAddr[i];
        }
    }
}

// 地址pDstAddr是否与pSrcAddr匹配(通配符0xAA)
// 去掉pSrcAddr高位字节的AAH之后，用低位字节和pDstAddr比较(不关注pDstAddr高位字节的AAH)
// 新增698之后，按照半字节比较
bool Proto645::mrsMeterAddrMatch(unsigned char *pSrcAddr, unsigned char *pDstAddr)
{
    char i = 0;
    char sAddrLength = HI_METER_ADDR_LEN * 2;

    for (i = sAddrLength - 1; i >= 0; i--)
    {
        if (((pSrcAddr[i/2] >> (4 * (i % 2))) & 0xF) != 0xA)
        {
            break;
        }
    }

    for (; i >= 0; i--)
    {
        if (((pSrcAddr[i/2] >> (4 * (i % 2))) & 0xF) != ((pDstAddr[i/2] >> (4 * (i % 2))) & 0xF))
        {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

unsigned int Proto645::mrsGen645Frame(MRS_PROTO645_FRAME_INF *pFrameInf, unsigned char **ppFrame, unsigned short *pFrameLen)
{
    unsigned short usBufferLength = MRS_645_FRAME_LENGTH_MIN + pFrameInf->ucDiSize + pFrameInf->ucDataLength;
    unsigned char *pBuffer = NULL;
    unsigned short usOffset = 0;

    pBuffer = static_cast<unsigned char*>(mrsToolsMalloc(usBufferLength));
    if (!pBuffer)
    {
        return HI_ERR_MALLOC_FAILUE;
    }

    mrsToolsMemZero_s(pBuffer, usBufferLength, usBufferLength);


    // HEAD
    pBuffer[usOffset++] = MRS_645_FRAME_START_FLG;

    // ADDR
    mrsToolsMemcpy_s(pBuffer + usOffset, usBufferLength - usOffset, pFrameInf->aucAddr, HI_METER_ADDR_LEN);
    usOffset += HI_METER_ADDR_LEN;

    // HEAD 2
    pBuffer[usOffset++] = MRS_645_FRAME_START_FLG;

    // CTRL
    pBuffer[usOffset++] = pFrameInf->ucCtrl;

    // LENGTH
    pBuffer[usOffset++] = pFrameInf->ucDiSize + pFrameInf->ucDataLength;

    // DI
    if (pFrameInf->ucDiSize > 0)
    {
        mrsToolsMemcpy_s(pBuffer + usOffset, usBufferLength - usOffset, &(pFrameInf->ulDi), pFrameInf->ucDiSize);
        mrs645DataEncode(pBuffer + usOffset, pFrameInf->ucDiSize);
        usOffset += pFrameInf->ucDiSize;
    }

    // DATA
    if (pFrameInf->ucDataLength > 0)
    {
        mrsToolsMemcpy_s(pBuffer + usOffset, usBufferLength - usOffset, pFrameInf->pData, pFrameInf->ucDataLength);
        mrs645DataEncode(pBuffer + usOffset, pFrameInf->ucDataLength);
        usOffset += pFrameInf->ucDataLength;
    }

    // CS
    pBuffer[usOffset] = static_cast<unsigned char>(mrsToolsCalcCheckSum2(pBuffer, usOffset));
    usOffset++;

    // END
    pBuffer[usOffset++] = MRS_645_FRAME_END_FLG;

    *ppFrame = pBuffer;
    *pFrameLen = usBufferLength;

    return HI_ERR_SUCCESS;
}

unsigned int Proto645::mrsGetFrame645MeterAddr(unsigned char *pucFrame, unsigned short usFrameLength, unsigned char *pucMeterAddr)
{
    unsigned short usPos = 0;
    unsigned short usLength = 0;
    unsigned int ulRet = HI_ERR_SUCCESS;

    ulRet = mrsFind645Frame(pucFrame, static_cast<short>(usFrameLength), &usPos, &usLength);
    if (HI_ERR_SUCCESS != ulRet)
    {
        return static_cast<unsigned int>(HI_ERR_FAILURE);
    }

    mrsToolsMemcpy_s(pucMeterAddr, HI_METER_ADDR_LEN, pucFrame + usPos + MRS_645_FRAME_METERADD_OFFSET, HI_METER_ADDR_LEN);

    return HI_ERR_SUCCESS;
}

unsigned int Proto645::mrs645ProtoBuffer(MRS_645_PROTO_CTX_STRU * pstCtx,MRS_ONE_RAW_FRAME_STRU * pstFrame)
{
    unsigned char* pucInputBuffer = pstCtx->pucRcvBuffer;
    unsigned short   usInputLen = pstCtx->usRcvBufferSize;
    unsigned int ret = HI_ERR_SUCCESS;

    while (usInputLen > 0)
    {
        unsigned char* pucFrameHead;
        pucFrameHead = (unsigned char*)mrsToolsStreamFindByte(pucInputBuffer,usInputLen,0x68);

        if (pucFrameHead != NULL)
        {//找到帧
            unsigned short usFrameLen = 0;
            unsigned char ucFrameLen = 0;

            usInputLen = (unsigned short)((usInputLen) - (pucFrameHead - pucInputBuffer));
            pucInputBuffer = pucFrameHead;

            if (usInputLen < 12) // 如果小于最小帧长-移动帧头到缓冲区头-继续接收
            {//包不完整
                ret = HI_ERR_CONTINUE;
                mrsToolsMemmove_s(pstCtx->pucRcvBuffer, MRS_PROTO_MR_DATAGRAM_BUF_MAX, pucInputBuffer, usInputLen);
                pstCtx->usRcvBufferSize = usInputLen;
                break;
            }

            if (pucInputBuffer[7] != 0x68) // 第二个帧标志
            {
                pucInputBuffer ++;
                usInputLen --;
                continue;
            }

            usFrameLen = (unsigned short)(pucInputBuffer[9] + 12);

            //超长帧
            if (usFrameLen > MRS_PROTO645_DATAGRAM_LEN_MAX)
            {
                pucInputBuffer ++;
                usInputLen --;
                continue;
            }
            ucFrameLen = (unsigned char)usFrameLen;

            //完整包
            if (usInputLen >= ucFrameLen)
            {
                if (mrsToolsCheck645Frame(pucInputBuffer,ucFrameLen) == HI_ERR_SUCCESS)
                {//成功的645帧
                    unsigned char* bf645 = (unsigned char*)mrsToolsMalloc(ucFrameLen);
                    if (bf645 == NULL)
                    {
                        pstCtx->usRcvBufferSize = 0;
                        return HI_ERR_MALLOC_FAILUE;
                    }

                    pstFrame->pucDatagram = bf645;
                    pstFrame->usDatagramSize = ucFrameLen;
                    mrsToolsMemcpy_s(bf645, ucFrameLen, pucInputBuffer, ucFrameLen);
                    pstCtx->usRcvBufferSize = 0;
                    return HI_ERR_SUCCESS;
                }
                else
                {//坏包
                    pucInputBuffer++;
                    usInputLen--;
                }
            }
            else
            {
                mrsToolsMemmove_s(pstCtx->pucRcvBuffer, MRS_PROTO_MR_DATAGRAM_BUF_MAX, pucInputBuffer, usInputLen);
                pstCtx->usRcvBufferSize = usInputLen;
                //上报帧不完整
                return HI_ERR_CONTINUE;
            }
        }
        else
        {//没有找到帧头
            pstCtx->usRcvBufferSize = 0;
            return HI_ERR_BAD_DATA;
        }
    }
    return ret;
}

unsigned int Proto645::mrsToolsCheck645Frame(unsigned char* ptr, unsigned short len)
{
    unsigned char checkSum;

    //帧长检测
    if ((!ptr) ||
        (len > MRS_PROTO645_DATAGRAM_LEN_MAX) ||
        (len < MRS_PROTO645_DATAGRAM_HEADER_LEN_MAX))
    {
        return HI_ERR_BAD_DATA;
    }

    //帧标志检查
    if ((ptr[0] != 0x68) || (ptr[7] != 0x68) || (ptr[len-1] != 0x16))
    {
        return HI_ERR_BAD_DATA;
    }

    //校验和检查
    checkSum = mrsToolsCalcCheckSum2(ptr,(unsigned short)(len-2));
    if (checkSum != ptr[len - 2])
    {
        return HI_ERR_BAD_DATA;
    }

    return HI_ERR_SUCCESS;
}

unsigned short Proto645::mrsToolsCalcCheckSum2(unsigned char* ptr, unsigned short len)
{
    unsigned short CheckSum = 0;

    if ((ptr != NULL) && (len > 0))
    {
        unsigned short i = 0;
        for(i = 0; i < len; i++)
        {
            CheckSum += ptr[i];
        }
    }
    return CheckSum;
}

unsigned char* Proto645::mrsToolsStreamFindByte(unsigned char* ptr, unsigned short len, unsigned char v)
{
    unsigned short i = 0;

    if (ptr != NULL)
    {
        for (i = 0; i < len; i++)
        {
            if (ptr[i] == v)
            {
                return ptr + i;
            }
        }
    }

    return NULL;
}


unsigned char Proto645::GetCtrl(MRS_645_CTRL_STRU& ctrl)
{
    return (unsigned char)(((ctrl.ucDir & 0x01) << 7)
                   + ((ctrl.ucSlaveFlag & 0x01) << 6)
                   + ((ctrl.ucFrameFlag & 0x01) << 5)
                   + ((ctrl.ucFn & 0x1F)));
}

void Proto645::InitProto645Frame(MRS_PROTO645_FRAME_INF& frame,int type=14)
{

    MRS_645_CTRL_STRU ctrl;
    type ==14? ctrl.ucFn = MRS_645_FRAME_CONTROL_FUNC_Read :ctrl.ucFn = MRS_645_FRAME_CONTROL_FUNC_BIT;
    ctrl.ucFrameFlag = MRS_645_FRAME_CONTROL_AFER_FRAME_NON_BIT;
    ctrl.ucSlaveFlag = MRS_645_FRAME_CONTROL_RESPONSION_NOMAL_BIT;
    ctrl.ucDir = MRS_645_FRAME_CONTROL_DIR_COMMAND_BIT;
    frame.ucCtrl = GetCtrl(ctrl);
    frame.ulDi = 0;
    frame.ucDiSize = MRS_645_FRAME_DATA_DI_SIZE;
    frame.ucDataLength = 0;
    frame.pData = NULL;
}

void Proto645::Gen645Data(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen)
{
    if ((psrcaddr != NULL) && (pdescaddr != NULL) && (srclen > 0) && (desclen < srclen))
    {
        unsigned char szdata[TMP_BUF_LEN] = { 0 };
        mrsToolsMemcpy_s(szdata, srclen, psrcaddr, srclen);
        Hexs2Bcds(szdata, pdescaddr, srclen);
    }
}

void Proto645::Gen645Addr(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen)
{
    Gen645Data(psrcaddr, srclen, pdescaddr, desclen);
}

void Proto645::Dec645Data(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen)
{
    if ((psrcaddr != NULL) && (pdescaddr != NULL) && (srclen > 0) && (desclen >= 2*srclen))
    {
        unsigned char buf[TMP_BUF_LEN] = { 0 };
        mrsToolsMemcpy_s(buf, TMP_BUF_LEN, psrcaddr, srclen);
        unsigned char addr[TMP_BUF_LEN] = { 0 };
        Bcd2Chars(buf, addr, srclen);
        Chars2Hexs(addr, pdescaddr, desclen);
    }
}

void Proto645::Dec645Addr(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen)
{
    Dec645Data(psrcaddr, srclen, pdescaddr, desclen);
}

void Proto645::HexInverts(unsigned char* psrcaddr, unsigned short srclen, unsigned char* pdescaddr, unsigned short desclen)
{
    mrsToolsMemcpy_s(pdescaddr, desclen, psrcaddr, srclen);
    HexInvert(pdescaddr, srclen);
}

unsigned int Proto645::Create645Frame(unsigned char* paddr, unsigned short addrlen, unsigned int udi, unsigned char* puserdata,
                                unsigned short userdatalen, unsigned char **ppFrame, unsigned short *pFrameLen)
{
    if ((addrlen != 12) || (paddr == NULL))
    {
        return HI_ERR_FAILURE;
    }
    if (userdatalen > 0)
    {
        if(puserdata == NULL)
        {
            return HI_ERR_FAILURE;
        }
    }

    MRS_PROTO645_FRAME_INF frame;
    InitProto645Frame(frame);
    frame.ulDi = udi;
    Gen645Addr(paddr, addrlen, frame.aucAddr, HI_METER_ADDR_LEN);
    return mrsGen645Frame(&frame, ppFrame, pFrameLen);

}

unsigned int Proto645::MRS_Proto645Dec( unsigned char* pucDatagram, unsigned short usDatagramSize, MRS_645_FRAME_STRU* pstFrame )
{

    if ((pucDatagram == NULL) || (pstFrame == NULL))
    {
        return HI_ERR_BAD_DATA;
    }

    unsigned short frame_len = 0;
    unsigned short pos = 0;
    unsigned int ret = mrsFind645Frame(pucDatagram, (short)usDatagramSize, &pos, &frame_len);
    if (ret != HI_ERR_SUCCESS)
    {
        return HI_ERR_BAD_DATA;
    }
    unsigned char* pInBuffer = pucDatagram + pos;

    //地址域6个字节
    mrsToolsMemcpy_s(pstFrame->ucAddr, sizeof(pstFrame->ucAddr), (unsigned char*)pInBuffer + 1, HI_METER_ADDR_LEN);

    //控制域
    pstFrame->stCtrl.ucDir = (unsigned char)((pInBuffer[8] & 0x80) >> 7);
    pstFrame->stCtrl.ucSlaveFlag = (unsigned char)((pInBuffer[8] & 0x40) >> 6);
    pstFrame->stCtrl.ucFrameFlag = (unsigned char)((pInBuffer[8] & 0x20) >> 5);
    pstFrame->stCtrl.ucFn = (unsigned char)(pInBuffer[8] & 0x1F);

    //长度
    pInBuffer += 9;
    pstFrame->ucDataRealmLen = *pInBuffer++;
    unsigned char ucDataRealmLen = pstFrame->ucDataRealmLen;

    if (ucDataRealmLen > sizeof(pstFrame->ucDataRealm))
    {
        return HI_ERR_BAD_DATA;
    }

    //应用程序数据
    if (ucDataRealmLen != 0)
    {
        mrsToolsMemcpy_s(pstFrame->ucDataRealm, sizeof(pstFrame->ucDataRealm), pInBuffer, ucDataRealmLen);
    }

    //获取版本号
    pstFrame->ucVer = mrsToolsGet645Ver(pstFrame->stCtrl.ucFn);

    return ret;
}

unsigned char* Proto645::Get645FrameData(unsigned char* pucDatagram, unsigned short usDatagramSize, MRS_645_FRAME_STRU* pstFrame, unsigned int *udi, unsigned char *nlen)
{
    if ((pucDatagram == NULL) || (pstFrame == NULL))
    {

        return NULL;
    }
    if (MRS_Proto645Dec(pucDatagram, usDatagramSize, pstFrame) != HI_ERR_SUCCESS)
    {
        return NULL;
    }
    unsigned char pdata[5] = { 0 };
    mrsToolsMemcpy_s(pdata, MRS_645_FRAME_DATA_IDENTIFICATION, pucDatagram + MRS_645_FRAME_DATA_OFFSET, MRS_645_FRAME_DATA_IDENTIFICATION);
    mrs645DataDecode(pdata, MRS_645_FRAME_DATA_IDENTIFICATION);
    mrsToolsMemcpy_s(udi, sizeof(unsigned int), pdata, sizeof(unsigned int));
    *nlen = pstFrame->ucDataRealmLen - MRS_645_FRAME_DATA_IDENTIFICATION;

    return pucDatagram + MRS_645_FRAME_DATA_OFFSET + MRS_645_FRAME_DATA_IDENTIFICATION;
}






void Proto645::Decode645Frame(unsigned char* pucDatagram, unsigned short usDatagramSize)
{

        bool bupdate = false;
        unsigned int ucdi = 0;
        unsigned char nlen = 0;
        unsigned short data_len = usDatagramSize;
        unsigned char *pdatagram = pucDatagram;
        unsigned char addrdata[13] = {0};
        unsigned char ucframedata[MRS_PROTO645_DATAGRAM_DATA_LEN_MAX] = { 0 };
        QString straddr;
        MRS_645_FRAME_STRU st645frame = { 0 };
        unsigned char *ptemp = NULL;
        for (;;)
        {
            ptemp = Get645FrameData(pdatagram, data_len, &st645frame, &ucdi, &nlen);
            if ((ptemp == NULL) || (st645frame.stCtrl.ucSlaveFlag == 1) || (st645frame.stCtrl.ucDir == 0))
            {
                qDebug()<<"get Get645FrameData break"<<endl;
                break;
            }
            Dec645Addr(st645frame.ucAddr, HI_METER_ADDR_LEN, addrdata, 12);
            straddr = (QString)((char*)addrdata);

            mrsToolsMemZero_s(ucframedata, MRS_PROTO645_DATAGRAM_DATA_LEN_MAX, MRS_PROTO645_DATAGRAM_DATA_LEN_MAX);
            mrsToolsMemcpy_s(ucframedata, MRS_PROTO645_DATAGRAM_DATA_LEN_MAX, ptemp, nlen);


            mrs645DataDecode(ucframedata, nlen);
            switch (ucdi)
            {
            case MRS_645_IDENTIFICATION_SET_IP_PORT:
                this->SendIpportSignal(ucframedata,nlen);
                break;

            case MRS_645_IDENTIFICATION_SET_MAC_ADDR: //设置ip
                  this->SendAddrSignal(ucframedata,nlen);
                break;
            }



            pdatagram += st645frame.ucDataRealmLen + MRS_645_FRAME_LENGTH_MIN;
            mrsToolsMemZero_s(&st645frame, sizeof(MRS_645_FRAME_STRU), sizeof(MRS_645_FRAME_STRU));


        }

}

void Proto645::SendIpportSignal(unsigned char *ucframedata,unsigned char nlen){

    if(nlen != 18){
        return;
    }
    QString ip;
    QByteArray portByteArray;
    QString port="";

    for(int i=0;i<nlen;i++){
        if(i<16){
           ip.append(*(ucframedata+i));
        }
        if(i>=16){
             char pHex[1];
            sprintf(pHex, "%02x", *(ucframedata+i) & 0xff);
            port=pHex+port;
        }
    }

    bool ok;
    int hex=port.toInt(&ok, 16);
    port =  QString::number(hex);



    emit emitIpportSignal(ip,port);
}


void Proto645::SendAddrSignal(unsigned char *ucframedata,unsigned char nlen){
    QString addr;
   for(int i=(int)nlen-1;i>=0;i--){
       char pHex[1];
       sprintf(pHex, "%02x",*(ucframedata+i) & 0xff);
       addr.append(pHex);
   }
    emit emitAddrSignal(addr);
}



