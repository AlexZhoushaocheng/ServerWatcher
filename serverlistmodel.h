#ifndef SERVERLISTMODEL_H
#define SERVERLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "processagent.h"

class ServerListModelPrivate;

class ServerListModel: public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
        Alias = Qt::UserRole + 1,   //服务的别名
        Path,               //服务的绝对路径，exe的名称当作服务名
        ID,                 //在配置的中id
        Parameters,         //运行参数
        Workdir,            //工作目录
        Watch,              //是否守护
        AutoRestartCount,   //自动重启次数
        State,              //运行状态

    };

    Q_ENUM(Roles)
    //explicit ServerListModel(QObject *parent = nullptr);


    static ServerListModel& getInstance(){
        static ServerListModel instance;
        return instance;
    }

    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
    virtual QHash<int,QByteArray> roleNames() const override;

    /* 自定义 方法*/
    //新增  indertData 没有重载，如果有 ，syn表示是否需要同步到持久化文件中
    Q_INVOKABLE void insertData(const ProcessAgentInfo &processInfo,bool syn = false);

    Q_INVOKABLE void run(int row);
    Q_INVOKABLE void stop(int row);
    Q_INVOKABLE void modifyData(int row,const ProcessAgentInfo& agentInfo);
    Q_INVOKABLE void deleteData(int row);

signals:

public slots:
    void onStateChanged(QProcess::ProcessState newState);
protected:

private:
    ServerListModel(QObject *parent = nullptr);
    Q_DECLARE_PRIVATE(ServerListModel)
    ServerListModelPrivate* d_ptr;
    Q_DISABLE_COPY_MOVE(ServerListModel)
};

#endif // SERVERLISTMODEL_H
