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

void Server::slotReadyRead() {
    socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_6_5);

        if (in.status() == QDataStream::Ok) {
            qDebug() << "Reading from client...";
            QString str;
            in >> str;
            qDebug() << "Received answer from client: " << str;

            // Process the answer from the client as needed

            // Send a new task to the client
            sendTaskToClient(socket);
        } else {
            qDebug() << "DataStream error";
        }
    }
}

void Server::sendToClient(QTcpSocket *client, const QString &str){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << str;
    client->write(data);
}

void Server::sendTaskToClient(QTcpSocket *client) {
    // Generate a math task
    int operand1 = QRandomGenerator::global()->bounded(2);
    QString task;
    if ((operand1 < 1) or (token != 1)){
        task = QString("cos(x) * 2 - 1,5");
        token = 1;
    }
    else if(token != 2) {
        task = QString("sin(x) / 3 + 0,5");
        token = 2;
    }
    else{
        task = QString("NONE");
    }
    sendToClient(client, task);
}
