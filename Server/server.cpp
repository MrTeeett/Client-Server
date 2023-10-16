#include "server.h"

Server::Server(){
    if(this->listen(QHostAddress::Any, 2323)){
        qDebug() << "start";
    }
    else{
        qDebug() << "error";
    }
}

void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    aSockets.push_back(socket);
    qDebug() << "client connected" << socketDescriptor;
}

void Server::slotReadyRead(){
    socket = (QTcpSocket *)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_5);
    if (in.status() == QDataStream::Ok){
        qDebug() << "read..";
        QString str;
        in >> str;
        qDebug() << str;
        double value = str.toDouble()*3;
        str = QString::number(value);
        sendToClient(str);
    }
    else{
        qDebug() << "DataStream error";
    }
}

void Server::sendToClient(QString str){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << str;
    //socket->write(data);
    for(int i = 0; i < aSockets.size(); i++){
        aSockets[i]->write(data);
    }
}
