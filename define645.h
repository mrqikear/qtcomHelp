#ifndef DEFINE645_H
#define DEFINE645_H

#include <qglobal.h>

#define HI_METER_ADDR_LEN               6
#define MRS_PROTO_MR_DATAGRAM_BUF_MAX   (2000)
#define MRS_PROTO645_DATAGRAM_DATA_LEN_MAX     200
#define MRS_PROTO645_DATAGRAM_HEADER_LEN_MAX   12
#define MRS_PROTO645_DATAGRAM_LEN_MAX   (MRS_PROTO645_DATAGRAM_DATA_LEN_MAX\
                                        +MRS_PROTO645_DATAGRAM_HEADER_LEN_MAX)

#define HI_ERR_FAILURE (unsigned int)(-1)
#define HI_ERR_SUCCESS (0)
#define HI_ERR_INVALID_PARAMETER (1)
#define HI_ERR_CONTINUE (10)
#define HI_ERR_MALLOC_FAILUE        (15)
#define HI_ERR_BAD_DATA             (53)

#define HI_FALSE   0
#define HI_TRUE    1

typedef enum {
    DLT_ACTIVE_POWER = 0,
    DLT_REACTIVE_POWER,
    DLT_CURRENT_A,
    DLT_CURRENT_B,
    DLT_CURRENT_C,
    DLT_VOLTAGE_A,
    DLT_VOLTAGE_B,
    DLT_VOLTAGE_C,
    DLT_INSTANTANEOUS_ACTIVE_POWER,
    DLT_INSTANTANEOUS_ACTIVE_POWER_A,
    DLT_INSTANTANEOUS_ACTIVE_POWER_B,
    DLT_INSTANTANEOUS_ACTIVE_POWER_C,
    DLT_INSTANTANEOUS_REACTIVE_POWER,
    DLT_INSTANTANEOUS_REACTIVE_POWER_A,
    DLT_INSTANTANEOUS_REACTIVE_POWER_B,
    DLT_INSTANTANEOUS_REACTIVE_POWER_C,
    DLT_POWER_FACTOR_BLOCK,
    DLT_POWER_FACTOR_BLOCK_A,
    DLT_POWER_FACTOR_BLOCK_B,
    DLT_POWER_FACTOR_BLOCK_C,
    DLT_HOUR_FREEZING_ACTIVE_ENERGY,
    DLT_HOUR_FREEZING_REACTIVE_ENERGY,
    DLT_IDENTIFICATION_MAX
}DLT_IDENTIFICATION;

typedef enum {
    DLT_AMMETER_PHASE_A = 0,
    DLT_AMMETER_PHASE_B,
    DLT_AMMETER_PHASE_C,
    DLT_AMMETER_PHASE_D,
    DLT_AMMETER_PHASE_NONE
}DLT_AMMETER_PHASE;

#define MRS_645_IDENTIFICATION_CURRENT_ACTIVE_ENERGY                    (0x00010000)//当前正向有功总电能*4-xxxxxx.xx-65536
#define MRS_645_IDENTIFICATION_POSITIVE_ACTIVE_ENERGY_DATA_BLOCK        (0x0001FF00)//（当前）正向有功电能数据块
#define MRS_645_IDENTIFICATION_CURRENT_REVERSE_ACTIVE_ENERGY            (0x00020000)//当前反向有功总电能*4-xxxxxx.xx-131072
#define MRS_645_IDENTIFICATION_REVERSE_ACTIVE_ENERGY_DATA_BLOCK         (0x0002FF00)//（当前）反向有功电能数据块
#define MRS_645_IDENTIFICATION_VOLTAGE_A                                (0x02010100)//A相电压*2-xxx.x-33620224
#define MRS_645_IDENTIFICATION_VOLTAGE_B                                (0x02010200)//B相电压*2-xxx.x-33620480
#define MRS_645_IDENTIFICATION_VOLTAGE_C                                (0x02010300)//C相电压*2-xxx.x-33620736
#define MRS_645_IDENTIFICATION_VOLTAGE_DATA_BLOCK                       (0x0201FF00)//三相电压*2-xxx.x-33685248
#define MRS_645_IDENTIFICATION_CURRENT_A                                (0x02020100)//A相电流*3-xxx.xxx-33685760
#define MRS_645_IDENTIFICATION_CURRENT_B                                (0x02020200)//B相电流*3-xxx.xxx-33686016
#define MRS_645_IDENTIFICATION_CURRENT_C                                (0x02020300)//C相电流*3-xxx.xxx-33686272
#define MRS_645_IDENTIFICATION_CURRENT_DATA_BLOCK                       (0x0202FF00)//三相电流*3-xxx.xxx-33750784
#define MRS_645_IDENTIFICATION_INSTANTANEOUS_ACTIVE_POWER_DATA_BLOCK    (0x0203FF00)//瞬时有功功率数据块*3-xx.xxxx-33816320
#define MRS_645_IDENTIFICATION_INSTANTANEOUS_REACTIVE_POWER_DATA_BLOCK  (0x0204FF00)//瞬时无功功率数据块*3-xx.xxxx-33881856
#define MRS_645_IDENTIFICATION_POWER_FACTOR_BLOCK                       (0x0206FF00)//功率因数数据块2-x.xxx-34012928
#define MRS_645_IDENTIFICATION_POWER_DOWN1                              (0x02110001)//（上1次）掉电时刻
#define MRS_645_IDENTIFICATION_POWER_DOWN2                              (0x02110002)//（上2次）掉电时刻
#define MRS_645_IDENTIFICATION_POWER_DOWN3                              (0x02110003)//（上3次）掉电时刻
#define MRS_645_IDENTIFICATION_NEUTRAL_CURRENTS                         (0x02B00001)//零线电流
#define MRS_645_IDENTIFICATION_POWER_FAILURES_COUNTS                    (0x03010000)//掉电总次数
#define MRS_645_IDENTIFICATION_DATE_WEEK                                (0x04020101)//日期及星期
#define MRS_645_IDENTIFICATION_TIME                                     (0x04020102)//时间
#define MRS_645_IDENTIFICATION_METER_STATUS                             (0x040005FF)//电表运行状态字数据块
#define MRS_645_IDENTIFICATION_HOUR_FREEZING_DATATIME                   (0x05040001)//整点冻结时间*5
#define MRS_645_IDENTIFICATION_HOUR_FREEZING_ACTIVE_ENERGY              (0x05040101)//整点冻结正向有功总电能*4
#define MRS_645_IDENTIFICATION_HOUR_FREEZING_REACTIVE_ENERGY            (0x05040201)//整点冻结反向有功总电能*4
#define MRS_645_IDENTIFICATION_HOUR_FREEZING_DATATIME_DATA_BLOCK        (0x0504FF01)//整点冻结数据块*4-84213505
#define MRS_645_IDENTIFICATION_FREEZING_DATATIME                        (0x05060001)//日冻结时间
#define MRS_645_IDENTIFICATION_FREEZING_REVERSE_ACTIVE_ENERGY_DATA      (0x05060201)//（上1次）日冻结反向有功电能数据
#define MRS_645_IDENTIFICATION_FREEZING_ELECTRICITY                     (0x05060101)//日冻结电能
#define MRS_645_IDENTIFICATION_FREEZING_CMD                             (0x99999900)//小时冻结
#define MRS_645_IDENTIFICATION_GPS_INFO                                 (0xEE000000) //获取上报GPS信息
#define MRS_645_IDENTIFICATION_SET_MAC_ADDR                             (0x04D00109)//设置（查询）终端地址(叶工项目)
#define MRS_645_IDENTIFICATION_SET_IP_PORT                              (0x04D00108) //设置(查询)ip和端口(叶工项目)

#define MRS_SRV_PROTO_645           (0)
#define MRS_SRV_PROTO_698_45        (1)
#define MRS_SRV_PROTO_TRANSPARENT   (2)

#define ID_MRS_BBUDA_645BUF     (ID_MRS_IRDA_645BUF)

#define MRS_645_FRAME_CONTROL_DIR_COMMAND_BIT            0 //方向位-命令
#define MRS_645_FRAME_CONTROL_DIR_RESPONSION_BIT         1 //方向位-应答
#define MRS_645_FRAME_CONTROL_RESPONSION_NOMAL_BIT       0 //应答标志-正常应答
#define MRS_645_FRAME_CONTROL_RESPONSION_ABNORMITY_BIT   1 //应答标志-异常应答
#define MRS_645_FRAME_CONTROL_AFER_FRAME_NON_BIT         0 //后续帧标志-无
#define MRS_645_FRAME_CONTROL_AFER_FRAME_EXIST_BIT       1 //后续帧标志-有
#define MRS_645_FRAME_CONTROL_FUNC_BIT       0x11 //功能码-读数据
#define MRS_645_FRAME_CONTROL_FUNC_Read      0x14 //功能码-写数据

#define MRS_645_FRAME_DATA_DI_SIZE     4
#define MRS_645_FRAME_DATA_DI_SIZE_V97 2
#define MRS_645_FRAME_COMMAND_ID_SIZE  4
#define MRS_645_FRAME_STAT_ID_SIZE     4

#define MRS_645_FRAME_CONTROL_DIR_UP        (0x80)
#define MRS_645_METER_ADDR_WILDCARDS        (0xAA)


#define MRS_645_FRAME_CONTROL_READ_DATA97   0x01
#define MRS_645_FRAME_CONTROL_READ_FOLLOW97 0x02
#define MRS_645_FRAME_CONTROL_READ_DATA     0x11
#define MRS_645_FRAME_CONTROL_READ_FOLLOW   0x12
#define MRS_645_FRAME_CONTROL_READ_ADDR     0x13
#define MRS_645_FRAME_CONTROL_WRITE_DATA    0x14
#define MRS_645_FRAME_CONTROL_WRITE_MAX     0x1D
#define MRS_645_FRAME_CONTROL_BRAKE         0x1C
#define MRS_645_FRAME_CONTROL_SAFE          0x03

#define MRS_645_CONTROL_TIMEOUT           2000

#define MRS_645_FRAME_CONTROL_MASK          (0x1F)
#define MRS_645_FRAME_CONTROL_ADJUST_TIME   (0x08)
#define MRS_645_FRAME_CONTROL_DENY_MASK     (0x40)

#define MRS_645_FRAME_LENGTH_MIN            (12)
#define MRS_645_FRAME_1ST_HEAD_LEN          (1)
#define MRS_645_FRAME_METERADD_LEN          (6)
#define MRS_645_FRAME_2ND_HEAD_LEN          (1)
#define MRS_645_FRAME_CTRL_LEN              (1)
#define MRS_645_FRAME_LENGTH_LEN            (1)

#define MRS_645_FRAME_1ST_HEAD_OFFSET       (0)
#define MRS_645_FRAME_METERADD_OFFSET       (MRS_645_FRAME_1ST_HEAD_OFFSET + MRS_645_FRAME_1ST_HEAD_LEN)
#define MRS_645_FRAME_2ND_HEAD_OFFSET       (MRS_645_FRAME_METERADD_OFFSET + MRS_645_FRAME_METERADD_LEN)
#define MRS_645_FRAME_CTRL_OFFSET           (MRS_645_FRAME_2ND_HEAD_OFFSET + MRS_645_FRAME_2ND_HEAD_LEN)
#define MRS_645_FRAME_LENGTH_OFFSET         (MRS_645_FRAME_CTRL_OFFSET + MRS_645_FRAME_CTRL_LEN)
#define MRS_645_FRAME_DATA_OFFSET           (MRS_645_FRAME_LENGTH_OFFSET + MRS_645_FRAME_LENGTH_LEN)
#define MRS_645_FRAME_DATA_IDENTIFICATION   (4)

#define MRS_645_FRAME_ADJUST_TIME_LEN       (0x06)
#define MRS_645_FRAME_ADJUST_TIME_FRAMELEN  (0x12)

#define MRS_645_FRAME_START_FLG             (0x68)
#define MRS_645_FRAME_END_FLG               (0x16)
#define MRS_645_FRAME_HEX33                 (0x33)

#define  MRS_645_CTRL_OFFSET                (MRS_645_FRAME_CTRL_OFFSET)
#define MRS_PREFIX_FE_SIZE                  (4)

#define MRS_645_IS_CTRL_CMD(x)              ( (((x) >= MRS_645_FRAME_CONTROL_WRITE_DATA) && ((x) <= MRS_645_FRAME_CONTROL_WRITE_MAX)) \
                                                || ((x) == MRS_645_FRAME_CONTROL_SAFE) )

//进制
/* BEGIN: Added by fengxiaomin/00209182, 2014/1/14   问题单号号:DTS2014012607684 */
#define MRS_CCO_ALGORISM_TYPE   (10)
#define MRS_CCO_HEX_TYPE        (16)
//开启内存分配调试信息
#define MRS_COLLECTOR_07_PROTOCOL_CONTROL         0x03   //特定控制字，属于645-2007规约
#define MRS_COLLECTOR_BOARDCAST_TIMEING_CONTROL   0x08   //广播校时报文中的控制字
#define MRS_MAXIMUM_DEMAND_CLEAR_CONTROL          0x10   //645-97规约中最大需量清零控制字

#undef ERROR
#define ERROR -1

#define DATA_ITEM_LEN 64


typedef enum
{
    ID_MRS_UART_645BUF = 0,    // 业务串口BUF ID
    ID_MRS_IRDA_645BUF,        // 红外串口BUF ID
    MRS_645BUF_MAX             // 645串口BUF总数量
} EM_MRS_645BUF_ID;

typedef enum
{

    METER_PROTO_TRANSPARENT,    /* 透明协议 */
    METER_PROTO_645_1997,       /* DL/T 645-1997 */
    METER_PROTO_645_2007,       /* DL/T 645-2007 */
    METER_PROTO_698_45,         /* DL/T 698.45 */
    METER_PROTO_MAX
} METER_PROTO_E;

typedef struct
{
    unsigned char* pucRcvBuffer;    // 内存分配出来的接收帧buffer
    unsigned short usRcvBufferSize; // 接收帧buffer大小
    unsigned short reserved;
}MRS_645_PROTO_CTX_STRU;

// 645控制域结构体
typedef struct
{
    unsigned char ucFn        :5; // 请求及应答功能码
    unsigned char ucFrameFlag :1; // 后续帧标志 0-无后续数据帧 1-有后续数据帧
    unsigned char ucSlaveFlag :1; // 从站异常标志 0-从站正确应答 1-从站对异常信息的应答
    unsigned char ucDir       :1; // 传送方向 0-由主站发出的命令帧 1-由从站发出的应答帧
}MRS_645_CTRL_STRU;

// 645 帧头信息结构体
typedef struct
{
    unsigned char ucVer; // 协议版本,取值为 MRS_PROTO645_VER_XXX
    unsigned char ucAddr[6];           // 表地址，固定6字节
    MRS_645_CTRL_STRU stCtrl; // 控制码
    unsigned char ucDataRealmLen; // 数据域大小必须小于200字节, 0表示无数据域
    unsigned char ucDataRealm[MRS_PROTO645_DATAGRAM_DATA_LEN_MAX]; // 数据域
}MRS_645_FRAME_STRU;

typedef struct
{
    unsigned char * pucHead;    // 缓冲区中第一个合法帧的帧头
    unsigned char * pucAddr;    // 缓冲区中第一个合法帧的表地址
    unsigned int  ulCrc;      // 缓冲区数据CRC校验
    unsigned char   ucNum;      // 缓冲区中合法645帧个数
    bool bCtrlCmd;   // 是否存在费控命令的645帧
    unsigned char   padding[2];
}MRS_645BUF_INF;


typedef struct
{
    unsigned char aucAddr[HI_METER_ADDR_LEN];
    unsigned char ucCtrl;
    unsigned char ucDiSize;
    unsigned int ulDi;
    unsigned char aucReserved[3];
    unsigned char ucDataLength;
    unsigned char *pData;
} MRS_PROTO645_FRAME_INF;

typedef struct
{
    unsigned short usDatagramSize; // 报文长度,单位字节
    unsigned short reserved;
    unsigned char* pucDatagram;  // 报文buffer
} MRS_ONE_RAW_FRAME_STRU;

#define mrsToolsMemset_s(des,max,src,cnt)   memset_s(des,max,src,cnt)
#define mrsToolsMemcpy_s(des,max,src,cnt)   memcpy(des,src,cnt)
#define mrsToolsMemmove_s(des,max,src,cnt)  memmove(des,src,cnt)
#define mrsToolsMalloc(sz) malloc(sz)
#define mrsToolsFree(sz)  do{if(sz)free(sz);sz=0;}while(0)
#define mrsToolsMemZero_s(des,max,cnt) memset(des,0,cnt)

#endif // DEFINE645_H
