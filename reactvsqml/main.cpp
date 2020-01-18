/*--------------------------------------------------------------------------
* Project: Reat Over QML / Qt Project
* Author Fabrice Lainard Created : 18/01/2020
*
* Copyright (c) Fabtice Lainard Programming. All rights reserved.
* Licensed under the MIT License.
--------------------------------------------------------------------------*/
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine>
#include <QWebChannel>
#include <QWebEngineView>
#include <QWebSocketServer>
#include <QStringLiteral>
#include <QDesktopWidget>
#include "backend.h"
#include "websocketclientwrapper.h"
#include "websockettransport.h"

BackEnd* backend =  nullptr;

void createWebView(QWebChannel* channel,int iView)
{
    const QUrl url(QStringLiteral("http://localhost:5000/"));
    QWebEngineView *view = new QWebEngineView();
    view->page()->setWebChannel(channel);
    view->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    view->load(url);
    view->move((view->width()+20)*iView,200);
    view->show();

}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    //  QGuiApplication app(argc, argv);
    //QML Related staff
    qmlRegisterType<BackEnd>("backend", 1, 0, "BackEnd");

    //Qt App
    QQmlApplicationEngine engine;

    // init backend API
    backend = new BackEnd();
    backend->list().push_back("Element 1");
    backend->list().push_back("Element 2");
    backend->list().push_back("Element 3");
    backend->list().push_back("Element 4");
    engine.rootContext()->setContextProperty("backend", backend);


    // Show Qml Window
    { const QUrl url(QStringLiteral("qrc:/main.qml"));

        engine.load(url);
    }
    // Show React Window
    {
        QtWebEngine::initialize();
        //   qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "23654");
         QWebSocketServer* server = new QWebSocketServer(QStringLiteral("qcw"), QWebSocketServer::NonSecureMode);
        if (!server->listen(QHostAddress::LocalHost, 89)) {
            qDebug() << "Failed to open web socket server.";
            return  1;
        }
        WebSocketClientWrapper* clientWrapper = new WebSocketClientWrapper(server);
        QWebChannel* channel = new QWebChannel;
        channel->registerObject(QStringLiteral("backend"), backend);
        QObject::connect(clientWrapper, &WebSocketClientWrapper::clientConnected,channel, &QWebChannel::connectTo);

        createWebView(channel,1);
        createWebView(channel,2);
    }


    return app.exec();
}


