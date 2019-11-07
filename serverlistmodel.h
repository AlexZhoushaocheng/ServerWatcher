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

    //用户操作类型
    enum UserOperate{
        Run,            //运行
        Termination     //终止
    };

    //explicit ServerListModel(QObject *parent = nullptr);

    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
    virtual QHash<int,QByteArray> roleNames() const override;

    //新增  indertData 没有重载，如果有
    Q_INVOKABLE void insertData(const ProcessAgentInfo &processInfo);

    //处理用户操作
    Q_INVOKABLE void DealUserOperation(const QModelIndex &index, const UserOperate& type);

    static ServerListModel& getInstance(){
        static ServerListModel instance;
        return instance;
    }
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
