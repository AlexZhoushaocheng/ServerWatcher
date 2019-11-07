#include "configmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <memory>



const QString ConfigFileName = "config.json";

ConfigManager::ConfigManager(QObject *parent) : QObject(parent)
{

}

bool ConfigManager::loadConfig()
{
    bool ret = true;
    QFile f(ConfigFileName);

    if(f.open(QIODevice::ReadOnly)){
        QJsonParseError error;
        QJsonDocument json = QJsonDocument::fromJson(f.readAll(),&error);
        if(json.isObject()){
            QJsonObject obj = json.object();
            QJsonArray servers = obj["servers"].toArray();

            for (int i = 0; i < servers.size(); i++) {
                auto jsonServer = servers[i].toObject();
                auto spServer = QSharedPointer<ProcessAgentInfo>::create(jsonServer["id"].toInt(),
                        jsonServer["path"].toString(),
                        jsonServer["alias"].toString(),
                        jsonServer["parameters"].toString(),
                        jsonServer["workdir"].toString(),
                        jsonServer["watch"].toBool(),
                        jsonServer["autoRestartCount"].toInt());
                m_servers.push_back(spServer);
            }
        }else {
            qDebug() << error.errorString();
            ret = false;
        }
    }else {
        ret = false;
    }

    return ret;
}

ConfigManager &ConfigManager::getInstance()
{
    static ConfigManager configMgr;
    return configMgr;
}

void ConfigManager::foreachServer(Call call)
{
    for(auto server:this->m_servers){
        call(*server);
    }
}

void ConfigManager::clear()
{
    m_servers.clear();
}
