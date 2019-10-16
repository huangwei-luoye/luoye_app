#ifndef UDPPROTOCOL_H
#define UDPPROTOCOL_H

#include <QObject>

const static quint16 ProtocolHead = 0x7E7E;
const static quint16 ProtocolEnd = 0xE7E7;

const static quint32 UdpProtocolAckHead = 0x18EFDC01;
const static quint32 UdpProtocolAckEnd = 0x01DCEF18;

#define CMD_SOFTWARE_VERSION  (0x01)
#define CMD_RESET             (0X02)
#define CMD_WOSHOU            (0x03)
#define CMD_START             (0x04)
#define CMD_END               (0x05)
#define CMD_COUNT             (0x06)

//#define PCK_START             (0x01)
//#define PCK_CENTRE            (0x02)
//#define PCK_END               (0x03)

#pragma pack(push, 1)

typedef struct _CMD_UDP
{
    quint16  head = ProtocolHead;
    quint8   cmd;
    quint8   reserve[3] = {0};
    quint16  end = ProtocolEnd;
}MsgCmdUdp;

typedef struct _CMD_UDP_ACK
{
    quint32 head = UdpProtocolAckHead;
    quint8  ackCmd;
    quint8  reserve[3] = {0xff};
    quint32 end = UdpProtocolAckEnd;

}MsgCmdUdpAck;

typedef struct _UDP_DATA_ACK_PROTOCOL
{
    quint32 head = UdpProtocolAckHead;
    quint8  channel;
    quint64 allPoint;
    quint32 allFrameCnt;
    quint32 currentFramNum ;
    quint16  currentFramDataLen;
    //QByteArray data;
    //quint32 end = UdpProtocolAckEnd;
}MsgUdpDataAckProtocol;

#pragma pack(pop)

#endif // UDPPROTOCOL_H
