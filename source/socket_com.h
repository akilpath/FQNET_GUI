#ifndef SOCKET_COM_H
#define SOCKET_COM_H

#include <QObject>

class socket_com : public QObject
{
    Q_OBJECT
public:
    explicit socket_com(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SOCKET_COM_H
