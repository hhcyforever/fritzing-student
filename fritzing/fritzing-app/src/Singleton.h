#ifndef SINGLETON
#define SINGLETON

#endif // SINGLETON

#include "sio_client.h"
#include "sio_socket.h"
#include "./internal/sio_packet.h"
#include "sio_message.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include <qmap.h>
#include <string>

using namespace std;
using namespace sio;

class Singleton
{
public:

    Singleton();
    static Singleton *GetInstance();
    QMap<QString,QString> id2type;
    QMap<QString,QString> id2svg;
    QMap<QString,QString> id2firstplace;
    int count;
    string otherEnd(const string &a ,int flg);
    string otherEnd2(const string &a ,int flg);
    //void emitdata(long fromID,QString fromConnectorID,long toID,QString toConnectorID,bool connect);
    void judgeIntersect();
    void analyseData(long fromID,QString fromConnectorID,long toID,QString toConnectorID,bool connect);
    void emitImage(QString imagestr);
    void emitInitPairs(QString constTitle,qint64 id);
    void emitPairsSVG(QString filename, qint64 id);
    void emitsleep();
    void emitwake();
    void emitLogin(QString name);
    void connecturl();
    void OnNewMessage(std::string const& name,message::ptr const& data,bool hasAck,message::list &ack_resp);
    client *io; //定义socket.io的客户端
private:
    //std::string url="http://127.0.0.1:3000";
    std::string url="http://10.0.1.3:3000"; //服务器的URL地址


};
