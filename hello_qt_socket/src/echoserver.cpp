//
// Created by Mike Mitterer on 19.05.17.
//

#include "echoserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

EchoServer::EchoServer(quint16 port, bool debug, QObject* parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),  QWebSocketServer::NonSecureMode, this)),
    m_debug(debug) {

    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug) {
            qDebug() << "Echoserver listening on port" << port;
        }

        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,  this, &EchoServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &EchoServer::closed);
    }
}

EchoServer::~EchoServer() {
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());

    if (m_debug) {
        qDebug() << "~EchoServer()";
    }
}

void EchoServer::onNewConnection() {
    QWebSocket* pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &EchoServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &EchoServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &EchoServer::socketDisconnected);

    m_clients << pSocket;
}

void EchoServer::processTextMessage(QString message) {
    auto* pClient = qobject_cast<QWebSocket*>(sender());
    if (m_debug) {
        qDebug() << "Message received:" << message;
    }

    if (pClient != nullptr) {
        pClient->sendTextMessage(message);
    }
}

void EchoServer::processBinaryMessage(QByteArray message) {
    auto* pClient = qobject_cast<QWebSocket*>(sender());
    if (m_debug) {
        qDebug() << "Binary Message received:" << message;
    }

    if (pClient != nullptr) {
        pClient->sendBinaryMessage(message);
    }
}

void EchoServer::socketDisconnected() {
    auto* pClient = qobject_cast<QWebSocket*>(sender());
    if (m_debug) {
        qDebug() << "socketDisconnected:" << pClient;
    }

    if (pClient != nullptr) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
