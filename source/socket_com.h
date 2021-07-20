#ifndef SOCKET_COM_H
#define SOCKET_COM_H

#include <QObject>
#include <QUdpSocket>

class socket_com : public QObject
{
    Q_OBJECT
public:
    explicit socket_com(QObject *parent = nullptr);
    QUdpSocket *udpSocket;
    QHostAddress *hostadress;
signals:

public slots:
    void sendDataToClient(double data);

private:

};

#endif // SOCKET_COM_H
