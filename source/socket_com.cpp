#include "socket_com.h"
#include <iostream>
socket_com::socket_com(QObject *parent) : QObject(parent)
{

    hostadress = new QHostAddress("10.7.0.139");
    udpSocket = new QUdpSocket(this);
    //udpSocket->bind(QHostAddress::LocalHost, 7755);

    //connect(udpSocket, &QUdpSocket::readyRead,this, &Server::readPendingDatagrams);
    udpSocket->bind(*hostadress, 5005);
}

void socket_com::sendDataToClient(double data){
    QByteArray datagram;
    datagram.setNum(data,'f',6);
   //const char d = data;
udpSocket->writeDatagram(datagram, *hostadress, 5005);
//std::cout<<<<std::endl;

}
