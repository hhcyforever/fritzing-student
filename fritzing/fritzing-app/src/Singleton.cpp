#include "Singleton.h"
#include "sio_client.h"
#include "sio_socket.h"
#include "sio_message.h"
#include "./internal/sio_packet.h"
#include "./mainwindow/fritzingwindow.h"
#include "./debugdialog.h"
#include "./lib/boost_1_68_0/boost/algorithm/string.hpp"
#include <regex>
#include "stdlib.h"

//#include "sio_client_impl.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include <qmap.h>
#include "./new_dialogs/MsgDlg.h"
#include <QMessageBox>
#include <String>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include "./mainwindow/mainwindow.h"
using namespace std;

#define BIND_EVENT(IO,EV,FN) \
    do{ \
        socket::event_listener_aux l = FN;\
        IO->on(EV,l);\
    } while(0)

using namespace std;
using namespace sio;

int loop_time = 0;
int prflg = 0;

Singleton *Singleton::GetInstance()
{
    static Singleton obj;
    return &obj;
}

Singleton::Singleton(){
    io=new client();
    count = 0;
}


void Singleton::connecturl(){
    io->connect(url);
    io->socket("/student")->Emit("studentOn");
//    using std::placeholders::_1;
//    using std::placeholders::_2;
//    using std::placeholders::_3;
//    using std::placeholders::_4;
//    socket::ptr sock=io->socket("/student");
//    BIND_EVENT(sock,"praise",std::bind(&Singleton::OnNewMessage,this,_1,_2,_3,_4));

}


void Singleton::emitImage(QString imagestr){
    QByteArray bytes = imagestr.toUtf8();
    std::string msg(bytes.data(),bytes.length());
    io->socket("/student")->Emit("circuitChange",msg);
}

//void Singleton::emitdata(long fromID,QString fromConnectorID,long toID,QString toConnectorID,bool connect){
//    QString t_id = QString::number(ID);
//    if(!id2svg.contains(t_id)){
//        DebugDialog::debug(QString("id not exist"));
//        return;
//    }
//    QMap<QString,QString>::iterator it2 = id2svg.find(t_id);
//    QString t_svg = it2.value();
//    if(addordelete){
//        count += 1;
//        if(count == 2){
//            if(t_svg == "wire"){
//                QMap<QString,QString>::iterator it_place = id2firstplace.find(t_id);
//                QString firstplace = it_place.value();
//                QString placeForWire = firstplace+"#"+ConnectorID;

//                QString m1 = t_id+"#"+t_svg;
//                QByteArray bytes1 = m1.toUtf8();
//                std::string msg1(bytes1.data(),bytes1.length());

//                QByteArray bytes2 = placeForWire.toUtf8();
//                std::string msg2(bytes2.data(),bytes2.length());

//                QString yesorno = addordelete ? "1" : "0";
//                QByteArray bytes3 = yesorno.toUtf8();
//                std::string msg3(bytes3.data(),bytes3.length());

//                message::list li(msg1);
//                li.push(msg2);
//                li.push(msg3);
//                qDebug("socket message:"+ bytes1+" 2 "+bytes2+" 3 "+bytes3);
//               io->socket("/student")->Emit("circuitChange",li);
//            }
//            else{
//                QString m1 = t_id+"#"+t_svg;
//                QByteArray bytes1 = m1.toUtf8();
//                std::string msg1(bytes1.data(),bytes1.length());

//                QByteArray bytes2 = ConnectorID.toUtf8();
//                std::string msg2(bytes2.data(),bytes2.length());

//                QString yesorno = addordelete ? "1" : "0";
//                QByteArray bytes3 = yesorno.toUtf8();
//                std::string msg3(bytes3.data(),bytes3.length());

//                message::list li(msg1);
//                li.push(msg2);
//                li.push(msg3);
//                qDebug("socket message:"+ bytes1+" 2 "+bytes2+" 3 "+bytes3);
//                io->socket("/student")->Emit("circuitChange",li);
//            }
//            count = 0;
//        }
//        if(count == 1){
//            if(t_svg == "wire"){
//                id2firstplace.insert(t_id,ConnectorID);
//            }
//        }

//    }
//    if(addordelete == 0){
//        QString m1 = t_id+"#"+t_svg;
//        QByteArray bytes1 = m1.toUtf8();
//        std::string msg1(bytes1.data(),bytes1.length());

//        QByteArray bytes2 = ConnectorID.toUtf8();
//        std::string msg2(bytes2.data(),bytes2.length());

//        QString yesorno = addordelete ? "1" : "0";
//        QByteArray bytes3 = yesorno.toUtf8();
//        std::string msg3(bytes3.data(),bytes3.length());

//        message::list li(msg1);
//        li.push(msg2);
//        li.push(msg3);
//        qDebug("socket message:"+ bytes1+" "+bytes2+" "+bytes3);
//        io->socket("/student")->Emit("circuitChange",li);
//    }
//}

void Singleton::emitsleep(){
    io->socket("/student")->Emit("studentSleep");
}

void Singleton::emitwake(){
    io->socket("/student")->Emit("studentAwake");
}

void Singleton::emitLogin(QString name){
    QByteArray bytes = name.toUtf8();
    std::string msg(bytes.data(),bytes.length());
    io->socket("/student")->Emit("studentName",msg);
}

void Singleton::emitInitPairs(QString constTitle,qint64 id){
    QString string_id = QString::number(id);
    id2type.insert(string_id,constTitle);
}

void Singleton::emitPairsSVG(QString filename,qint64 id){
    QString string_id = QString::number(id);
    id2svg.insert(string_id,filename);
}

//void Singleton::OnNewMessage(std::string const& name,message::ptr const& data,bool hasAck,message::list &ack_resp){
//    FritzingWindow::OnNewMessage(name, data, hasAck, ack_resp);
//    qDebug("message content");
//    std::string a = "Box";
//    QMessageBox::information(this, QString::fromStdString(a),QString::fromStdString(data->get_string()));
//    MsgDlg dlg(Msg_Praise,data->get_string(),this->window());
//    dlg.setAttribute(Qt::WA_ShowModal, true);
//    dlg.startTimer();
//    dlg.exec();
//}


void Singleton::analyseData(long fromID,QString fromConnectorID,long toID,QString toConnectorID,bool connect){
    cout << "itemsStruct" << endl;
    if(prflg == 0){
        for(int i = 0; i < itemsStruct.size();i++){
            cout << itemsStruct[i].id << endl;
            cout << itemsStruct[i].type << endl;
            cout << itemsStruct[i].end0 << endl;
            cout << itemsStruct[i].end1 << endl;
        }
    }

    prflg = 1;
    QString fromIDstr = QString::number(fromID);
    QMap<QString,QString>::iterator it = id2type.find(fromIDstr);
    QString type = it.value();
    string typestr = type.toStdString();

    QString toIDstr = QString::number(toID);
    QMap<QString,QString>::iterator it2 = id2type.find(toIDstr);
    QString type2 = it2.value();
    string type2str = type2.toStdString();

    string fid = fromIDstr.toStdString();
    string tid = toIDstr.toStdString();
    string fcid = fromConnectorID.toStdString();
    string tcid = toConnectorID.toStdString();

    int flag = 0;
    for(int i = 0; i < itemsStruct2.size();i++){
        if(itemsStruct2[i].id == fid){
            flag = 1;
            if(itemsStruct2[i].type == "led" || itemsStruct2[i].type == "resistor"){
                if(fcid == "connector0"){
                    if(connect == 1){
                        itemsStruct2[i].end0 = tcid;
                    }
                    else{
                        itemsStruct2[i].end0 = "";
                    }
                }
                else if(fcid == "connector1"){
                    if(connect == 1){
                        itemsStruct2[i].end1 = tcid;
                    }
                    else{
                        itemsStruct2[i].end1 = "";
                    }
                }

            }
            else if(itemsStruct2[i].type == "Arduino Nano3(fix)"){
                if(fcid == "connector30"){
                    if(connect == 1){
                        itemsStruct2[i].end0 = tcid;
                    }
                    else{
                        itemsStruct2[i].end0 = "";
                    }
                }
                else if(fcid == "connector31"){
                    if(connect == 1){
                        itemsStruct2[i].end1 = tcid;
                    }
                    else{
                        itemsStruct2[i].end1 = "";
                    }
                }
            }
            else if(itemsStruct2[i].type == "wire"){
                if(fcid == "connector0"){
                    if(connect == 1){
                        if(type2 == "RSR 03MB102 Breadboard")
                            itemsStruct2[i].end0 = tcid;
                        else{
                            itemsStruct2[i].end0 = tcid+"#"+tid;
                            int find_flg = 0;
                            for(int j = 0; j < itemsStruct2.size(); j++){
                                if(itemsStruct2[j].id == tid){
                                    find_flg = 1;
                                    if(tcid == "connector0"){
                                        itemsStruct2[j].end0 = fcid+"#"+fid;
                                    }
                                    else if(tcid == "connector1"){
                                        itemsStruct2[j].end1 = fcid+"#"+fid;
                                    }
                                    break;
                                }
                            }
                        }

                    }
                    else{
                        itemsStruct2[i].end0 = "";
                    }
                }
                else if(fcid == "connector1"){
                    if(connect == 1){
                        if(type2 == "RSR 03MB102 Breadboard")
                            itemsStruct2[i].end1 = tcid;
                        else{
                            itemsStruct2[i].end1 = tcid+"#"+tid;
                            int find_flg = 0;
                            for(int j = 0; j < itemsStruct2.size(); j++){
                                if(itemsStruct2[j].id == tid){
                                    find_flg = 1;
                                    if(tcid == "connector0"){
                                        itemsStruct2[j].end0 = fcid+"#"+fid;
                                    }
                                    else if(tcid == "connector1"){
                                        itemsStruct2[j].end1 = fcid+"#"+fid;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    else{
                        itemsStruct2[i].end1 = "";
                    }
                }
            }
        break;
        }
    }

    if(flag == 0){
        simple_item new_item;
        new_item.flag = 0;
        if(type == "wire"){
            new_item.type = "wire";
            new_item.id = fid;
            if(fcid == "connector0"){
                if(type2 == "RSR 03MB102 Breadboard")
                    new_item.end0 = tcid;
                else
                    new_item.end0 = tid+"#"+tcid;
            }
            else if(fcid == "connector1"){
                if(type2 == "RSR 03MB102 Breadboard")
                    new_item.end1 = tcid;
                else
                    new_item.end1 = tid+"#"+tcid;
            }
        }

        else if(type == "220Ω Resistor"){
            new_item.type = "resistor";
            new_item.id = fid;
            if(fcid == "connector0"){
                new_item.end0 = tcid;


            }
            else if(fcid == "connector1"){
                new_item.end1 = tcid;

            }
        }

        else if(type == "Red (633nm) LED"){
            new_item.type = "led";
            new_item.id = fid;
            if(fcid == "connector0"){
                new_item.end0 = tcid;

            }
            else if(fcid == "connector1"){
                new_item.end1 = tcid;
            }
        }

        else if(type == "Arduino Nano (Rev3.0)"){
            new_item.type = "Arduino Nano3(fix)";
            new_item.id = fid;
            if(fcid == "connector30"){
                new_item.end0 = tcid;

            }
            else if(fcid == "connector31"){
                new_item.end1 = tcid;
            }
        }

        itemsStruct2.push_back(new_item);
    }

    for(vector<simple_item>::iterator it = itemsStruct2.begin(); it != itemsStruct2.end();){
        if((*it).end0 == "" && (*it).end1 == ""){
            it = itemsStruct2.erase(it);

        }
        else it++;
    }

    for(int i = 0; i < itemsStruct2.size();i++){
        if(itemsStruct2[i].end0 == "" && itemsStruct2[i].end1 == "" ){
            itemsStruct2.erase(itemsStruct.begin()+i);
            i = i-1;
        }
    }
    for(int i = 0; i < itemsStruct2.size();i++){
        cout << itemsStruct2[i].id << endl;
        cout << itemsStruct2[i].type << endl;
        cout << itemsStruct2[i].end0 << endl;
        cout << itemsStruct2[i].end1 << endl;
    }
    for(int i = 0; i < itemsStruct.size();i++){
        if(itemsStruct[i].end0 == "" || itemsStruct[i].end1 == "") return;
    }
    for(int i = 0; i < itemsStruct2.size();i++){
        if(itemsStruct2[i].end0 == "" || itemsStruct2[i].end1 == "") return;
    }
    int size = itemsStruct.size();
    float match = 0;
    for(int i = 0; i < itemsStruct2.size();i++){
        for(int j = 0; j < itemsStruct.size();j++){
            if(itemsStruct[j].type == itemsStruct2[i].type){
                if(itemsStruct[j].type == "resistor"){
                    if(itemsStruct[j].end0 == itemsStruct2[i].end0 && itemsStruct[j].end1 == itemsStruct2[i].end1){
                        match += 1;

                    }
                    else if(itemsStruct[j].end0 == itemsStruct2[i].end1 && itemsStruct[j].end1 == itemsStruct2[i].end0){
                        match += 1;
                    }
                }
                else if(itemsStruct[j].type == "led"){
                    if(itemsStruct[j].end0 == itemsStruct2[i].end0 && itemsStruct[j].end1 == itemsStruct2[i].end1){
                        match += 1;

                    }
                }
                else if(itemsStruct[j].type == "Arduino Nano3(fix)"){
                    if(itemsStruct[j].end0 == itemsStruct2[i].end0 && itemsStruct[j].end1 == itemsStruct2[i].end1){
                        match += 1;

                    }
                }
                else if(itemsStruct[j].type == "wire"){

                    if(itemsStruct[j].end0 == itemsStruct2[i].end0 && itemsStruct[j].end1 == itemsStruct2[i].end1){
                        match += 1;

                    }
                    else if(itemsStruct[j].end0 == itemsStruct2[i].end1 && itemsStruct[j].end1 == itemsStruct2[i].end0){
                        match += 1;
                    }
                    else if(itemsStruct[j].end0 == itemsStruct2[i].end0 && (itemsStruct[j].end1.compare("pin") < 0) && (itemsStruct2[i].end1.compare("pin") < 0)){
                        string end1 = otherEnd(itemsStruct[j].end1,(itemsStruct[j].end1.compare("connector1")>0));
                        cout << itemsStruct[j].end0 << "+++" <<endl;
                        cout << end1 << "---" << endl;
                        int loop1 = loop_time;
                        loop_time = 0;
                        string end2 = otherEnd2(itemsStruct2[i].end1,(itemsStruct2[i].end1.compare("connector1")>0));
                        cout << itemsStruct2[i].end0 << "***" <<endl;
                        cout << end2 << "```" << endl;
                        int loop2 = loop_time;
                        loop_time = 0;
                        if(end1 == end2 && loop1 == loop2){
                            match += ((float)(loop1+1)/2);
                        }
                    }
                    else if(itemsStruct[j].end0 == itemsStruct2[i].end1 && (itemsStruct[j].end1.compare("pin") < 0) && (itemsStruct2[i].end0.compare("pin") < 0)){
                        string end1 = otherEnd(itemsStruct[j].end1,(itemsStruct[j].end1.compare("connector1")>0));
                        cout << itemsStruct[j].end0 << "+++" <<endl;
                        cout << end1 << "---" << endl;
                        int loop1 = loop_time;
                        loop_time = 0;
                        string end2 = otherEnd2(itemsStruct2[i].end0,(itemsStruct2[i].end0.compare("connector1")>0));
                        cout << itemsStruct2[i].end1 << "***" <<endl;
                        cout << end2 << "```" << endl;
                        int loop2 = loop_time;
                        loop_time = 0;
                        if(end1 == end2 && end1 != "" && loop1 == loop2){
                            match += ((float)(loop1+1)/2);
                        }
                    }
                    else if(itemsStruct[j].end1 == itemsStruct2[i].end1 && (itemsStruct[j].end0.compare("pin") < 0) && (itemsStruct2[i].end0.compare("pin") < 0)){
                        string end1 = otherEnd(itemsStruct[j].end0,(itemsStruct[j].end0.compare("connector1")>0));
                        cout << itemsStruct[j].end1 << "+++" <<endl;
                        cout <<end1 <<  "---" << endl;
                        int loop1 = loop_time;
                        loop_time = 0;
                        string end2 = otherEnd2(itemsStruct2[i].end0,(itemsStruct2[i].end0.compare("connector1")>0));
                        cout << itemsStruct2[i].end1 << "***" <<endl;
                        cout << end2 << "```" << endl;
                        int loop2 = loop_time;
                        loop_time = 0;
                        if(end1 == end2 && end1 != "" && loop1 == loop2){
                            match += ((float)(loop1+1)/2);
                        }
                    }
                    else if(itemsStruct[j].end1 == itemsStruct2[i].end0 && (itemsStruct[j].end0.compare("pin") < 0) && (itemsStruct2[i].end1.compare("pin") < 0)){
                        string end1 = otherEnd(itemsStruct[j].end0,(itemsStruct[j].end0.compare("connector1")>0));
                        cout << itemsStruct[j].end1 << "+++" <<endl;
                        cout <<end1<< "---" << endl;
                        int loop1 = loop_time;
                        loop_time = 0;
                        string end2 = otherEnd2(itemsStruct2[i].end1,(itemsStruct2[i].end1.compare("connector1")>0));
                        cout << itemsStruct2[i].end0 << "***" <<endl;
                        cout << end2 << "```" << endl;
                        int loop2 = loop_time;
                        loop_time = 0;
                        if(end1 == end2 && end1 != "" && loop1 == loop2){
                            match += ((float)(loop1+1)/2);
                        }
                    }
                }
            }
        }
    }
    cout << "size" << size <<endl;
    cout << "match" << match << endl;





//    if(type == "220Ω Resistor"){
//        if(fromConnectorID == "connector0"){
//            if(type2 == "RSR 03MB102 Breadboard"){
//                if(connect == 1){
//                    for(int i = 0; i < itemsStruct.size(); i++){
//                        if(itemsStruct[i].type == "resistor" && itemsStruct[i].end0 == toConnectorID.toStdString()){
//                            if(itemsStruct[i].flag == 0 || itemsStruct[i].flag == 1)
//                                itemsStruct[i].flag += 1;
//                        }
//                    }
//                }
//            }
//        }
//        else if(fromConnectorID == "connector1"){
//            if(type2 == "RSR 03MB102 Breadboard"){

//            }
//        }
//    }

//    if(type == "wire"){
//        if(fromConnectorID == "connector0"){

//        }
//        else if(fromConnectorID == "connector1"){

//        }
//    }

//    if(type == "Arduino Nano3(fix)"){
//        if(fromConnectorID == "connector30"){
//            if(toID == 57510){
//                if(connect == 1){
//                    for(int i = 0; i < itemsStruct.size(); i++){
//                        if(itemsStruct[i].type == "Arduino Nano3(fix)" && itemsStruct[i].end0 == toConnectorID.toStdString()){
//                            if(itemsStruct[i].flag == 0 || itemsStruct[i].flag == 1)
//                                itemsStruct[i].flag += 1;
//                        }
//                    }
//                }

//                else if(connect == )
//            }

//        }
//        else if(fromConnectorID == "connector1"){

//        }
//    }

//    if(type == "wire"){
//        if(fromConnectorID == "connector0"){

//        }
//        else if(fromConnectorID == "connector1"){

//        }
//    }
}

string Singleton::otherEnd(const string &a ,int flg){
    loop_time += 1;
    vector<string> v;
    boost::split( v, a, boost::is_any_of("#"));
    if(flg == 0){
        for(int i = 0; i < itemsStruct.size();i++){
            if(itemsStruct[i].id == v[1]){
                if(itemsStruct[i].end1.compare("pin") > 0){
                    return itemsStruct[i].end1;
                }
                else if(itemsStruct[i].end1 != ""){
                    return otherEnd(itemsStruct[i].end1 , (itemsStruct[i].end1.compare("connector1") > 0));
                }
                else return "";
            }
        }
    }
    else{
        for(int i = 0; i < itemsStruct.size();i++){
            if(itemsStruct[i].id == v[1]){
                if(itemsStruct[i].end0.compare("pin") > 0){
                    return itemsStruct[i].end0;
                }
                else if(itemsStruct[i].end0 != ""){
                    return otherEnd(itemsStruct[i].end0 , (itemsStruct[i].end0.compare("connector1") > 0));
                }
                else return "";
            }
        }
    }
}

string Singleton::otherEnd2(const string &a ,int flg){
    cout << a << flg << endl;
    loop_time += 1;
    vector<string> v;
    boost::split( v, a, boost::is_any_of("#"));
    if(flg == 0){
        for(int i = 0; i < itemsStruct2.size();i++){
            if(itemsStruct2[i].id == v[1]){
                if(itemsStruct2[i].end1.compare("pin") > 0){
                    return itemsStruct2[i].end1;
                }
                else if(itemsStruct2[i].end1 != ""){
                    return otherEnd2(itemsStruct2[i].end1 , (itemsStruct2[i].end1.compare("connector1") > 0));
                }
                else return "";
            }
        }
    }
    else{
        for(int i = 0; i < itemsStruct2.size();i++){
            if(itemsStruct2[i].id == v[1]){
                if(itemsStruct2[i].end0.compare("pin") > 0){
                    return itemsStruct2[i].end0;
                }
                else if(itemsStruct2[i].end0 != ""){
                    return otherEnd2(itemsStruct2[i].end0 , (itemsStruct2[i].end0.compare("connector1") > 0));
                }
                else return "";
            }
        }
    }
}

void Singleton::judgeIntersect(){
//    for(int i = 0; i < itemsStruct2.size();i++){
//        if(itemsStruct2[i].end1.compare("pin") < 0 || itemsStruct2[i].end0.compare("pin") < 0) continue;
//        int point1_a = trans(itemsStruct2[i].end0);
//        int point1_b = trans(itemsStruct2[i].end1);
//        for(int j = i+1; j < itemsStruct2.size();j++){
//            if(itemsStruct2[j].end1.compare("pin") < 0 || itemsStruct2[j].end0.compare("pin") < 0) continue;
//            int point2_a = trans(itemsStruct2[j].end0);
//            int point2_b = trans(itemsStruct2[j].end1);
//            judge(point1_a,point1_b,point2_a,point2_b);

//        }
//    }

}

//int Singleton::trans(string &s){
//    const regex pattern("(\\w*)(\\d*)(\\w*)");
//    match_results<string::const_iterator> result;
//    bool valid = regex_match(s,result,pattern);
//    if(valid){
//        int x = atoi(s.c_str());

//    }

//}
