#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <functional>
#include <QVector>
#include <QSharedPointer>
#include "processagentInfo.h"

using Call = std::function<void (const ProcessAgentInfo&)>;

class ConfigManager : public QObject
{
    Q_OBJECT
public:
    //从配置文件中读取配置
    bool loadConfig();

    static ConfigManager& getInstance();

    const QVector<QSharedPointer<ProcessAgentInfo>> & getAllServers(){return m_servers;}

    void foreachServer(Call call);

    //清空数据
    void clear();
private:
    explicit ConfigManager(QObject *parent = nullptr);

    QVector<QSharedPointer<ProcessAgentInfo>> m_servers;
signals:

public slots:
};

#endif // CONFIGMANAGER_H
