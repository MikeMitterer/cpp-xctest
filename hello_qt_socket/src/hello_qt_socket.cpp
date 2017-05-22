#include <memory>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "echoserver.h"

// Weitere Infos
//      https://github.com/voidpirate/qwss

using namespace std;

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoserver");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
                                 QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
                                  QCoreApplication::translate("main", "Port for echoserver [default: 5000]."),
                                  QCoreApplication::translate("main", "port"), QLatin1Literal("5000"));
    parser.addOption(portOption);
    parser.process(a);

    bool debug = parser.isSet(dbgOption);
    auto port = parser.value(portOption).toInt();

    auto server = unique_ptr<EchoServer>(new EchoServer(static_cast<quint16>(port), debug));
    QObject::connect(server.get(), &EchoServer::closed, &a, &QCoreApplication::quit);

    // auto server = new EchoServer(static_cast<quint16>(port), debug);
    // QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
