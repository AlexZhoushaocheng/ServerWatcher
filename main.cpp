#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "configmanager.h"
#include "processagent.h"
#include "serverlistmodel.h"
#include <functional>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    qmlRegisterType<ProcessAgentInfo>();

    //读取配置
    ConfigManager::getInstance().loadConfig();

    //初始化model
    ConfigManager::getInstance().foreachServer(std::bind(&ServerListModel::insertData,&ServerListModel::getInstance(),std::placeholders::_1));

    //注册model
    qmlRegisterSingletonType<ServerListModel>("ServerWatcher.Model",1,0,"ServerListModel",[](QQmlEngine* ,QJSEngine *)->QObject*{
        return & ServerListModel::getInstance();
    });

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
