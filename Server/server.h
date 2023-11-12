#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDebug>
#include <QList>
#include <QRandomGenerator>
#include <QDataStream>

class Server : public QTcpServer{
    Q_OBJECT

public:
    Server();
    QTcpSocket *socket;

private:
    int token;
    QVector <QTcpSocket*> aSockets;
    QByteArray data;
    void sendToClient(QTcpSocket *client, const QString &str);
    void sendTaskToClient(QTcpSocket *client);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H
