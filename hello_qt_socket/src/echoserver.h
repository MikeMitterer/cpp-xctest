//
// Created by Mike Mitterer on 19.05.17.
//

#ifndef XCTEST_ECHOSERVER_H_H
#define XCTEST_ECHOSERVER_H_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)

QT_FORWARD_DECLARE_CLASS(QWebSocket)

class EchoServer : public QObject {
Q_OBJECT
public:
    explicit EchoServer(quint16 port, bool debug = false, QObject* parent = Q_NULLPTR);

    ~EchoServer() override;

Q_SIGNALS:

    void closed();

private Q_SLOTS:

    void onNewConnection();

    void processTextMessage(QString message);

    void processBinaryMessage(QByteArray message);

    void socketDisconnected();

private:
    QWebSocketServer* m_pWebSocketServer;
    QList<QWebSocket*> m_clients;
    bool m_debug;
};

#endif //XCTEST_ECHOSERVER_H_H
