#include "socket_com.h"
#include <iostream>
socket_com::socket_com(QObject *parent) : QObject(parent)
{

    hostadress = new QHostAddress("10.7.0.113");
    udpSocket = new QUdpSocket(this);
    //udpSocket->bind(QHostAddress::LocalHost, 7755);

    //connect(udpSocket, &QUdpSocket::readyRead,this, &Server::readPendingDatagrams);
    udpSocket->bind(*hostadress, 5005);
}

void socket_com::sendDataToClient(int data){
   const char d = data;
udpSocket->writeDatagram(&d, *hostadress, 5005);
//std::cout<<"kpahachorizozozozozo"<<std::endl;

}
