#include "serverlistmodel.h"
#include <QMutex>
#include <qglobal.h>
#include <QDebug>
#include "processagent.h"

class ServerListModelPrivate{
public:
    ServerListModelPrivate(ServerListModel* parent):
        q_ptr(parent),
        mutex(nullptr)
    {
    }

    void init(){
        if(! mutex){
            mutex = new QMutex();
        }
        rolesNames.insert(ServerListModel::Roles::Alias,"alias");
        rolesNames.insert(ServerListModel::Roles::Path,"path");
        rolesNames.insert(ServerListModel::Roles::ID,"id");
        rolesNames.insert(ServerListModel::Roles::Parameters,"parameters");
        rolesNames.insert(ServerListModel::Roles::Workdir,"workdir");
        rolesNames.insert(ServerListModel::Roles::Watch,"watch");
        rolesNames.insert(ServerListModel::Roles::AutoRestartCount,"autoRestartCount");
        rolesNames.insert(ServerListModel::Roles::State,"state");
    }

    void uninit(){
        if(mutex){
            delete mutex;
            mutex = nullptr;
        }

        qDeleteAll(data);
        data.clear();
    }

    //找到对象所在的行
    int findRow(QObject* process){
        return  data.indexOf(dynamic_cast<ProcessAgent*>(process));
    }
private:
    ServerListModel * const q_ptr;
    Q_DECLARE_PUBLIC(ServerListModel)

    QVector<ProcessAgent*> data;
    QHash<int,QByteArray> rolesNames;
    QMutex *mutex;
};

ServerListModel::ServerListModel(QObject *parent) : QAbstractListModel(parent),
    d_ptr(new ServerListModelPrivate(this))
{
    Q_D(ServerListModel);
    d->init();
}

int ServerListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    const Q_D(ServerListModel);

    return d->data.size();
}

int ServerListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant ServerListModel::data(const QModelIndex &index, int role) const
{
    const Q_D(ServerListModel);
    if(index.row()>=0 && index.row() < d->data.size()){
        switch (role) {
        case Alias:
            return d->data[index.row()]->getBaseInfo().getAlias();
        case Path:
            return d->data[index.row()]->getBaseInfo().getPath();
        case ID:
            return d->data[index.row()]->getBaseInfo().getId();
        case Parameters:
            return d->data[index.row()]->getBaseInfo().getParameters();
        case Workdir:
            return d->data[index.row()]->getBaseInfo().getWorkdir();
        case Watch:
            return d->data[index.row()]->getBaseInfo().getWatch();
        case AutoRestartCount:
            return d->data[index.row()]->getBaseInfo().getAutoRestartCount();
        case State:
            return d->data[index.row()]->getProcessState();
        default:
            return QString("role %1  didn't found").arg(role);
        }
    }
    else {

        return "index error";
    }
}

bool ServerListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool ret = true;
    const Q_D(ServerListModel);
    if(index.row()>=0 && index.row() < d->data.size()){
        switch (role) {
        case Alias:{
            d->data[index.row()]->getBaseInfo().setAlias(value.toString());
            emit dataChanged(index,index);
            break;
        }
        case Path:{
            d->data[index.row()]->getBaseInfo().setPath(value.toString());
            emit dataChanged(index,index);
            break;
        }
        case Parameters:{
            d->data[index.row()]->getBaseInfo().setParameters(value.toString());
            emit dataChanged(index,index);
            break;
        }
        case Workdir:{
            d->data[index.row()]->getBaseInfo().setWorkdir(value.toString());
            emit dataChanged(index,index);
            break;
        }
        case Watch:{
            d->data[index.row()]->getBaseInfo().setWatch(value.toBool());
            emit dataChanged(index,index);
            break;
        }
        case AutoRestartCount:{
            d->data[index.row()]->getBaseInfo().setAutoRestartCount(value.toInt());
            emit dataChanged(index,index);
            break;
        }
        default:
            ret = false;
        }
    }

    return ret;
}

void ServerListModel::insertData(const ProcessAgentInfo& processInfo)
{
    qDebug()<<"insert: "<<processInfo.getAlias();
    Q_D(ServerListModel);
    ProcessAgent* pProcess = new ProcessAgent(processInfo);

    connect(pProcess,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(onStateChanged(QProcess::ProcessState)));

    beginInsertRows(QModelIndex(),d->data.size(),d->data.size());
    d->data.push_back(pProcess);
    endInsertRows();
}


QHash<int, QByteArray> ServerListModel::roleNames() const
{
   const Q_D(ServerListModel);

   return d->rolesNames;
}

void ServerListModel::DealUserOperation(const QModelIndex &index, const UserOperate& type)
{

}

void ServerListModel::onStateChanged(QProcess::ProcessState newState)
{
    Q_UNUSED(newState)
    Q_D(ServerListModel);
    auto sender = QObject::sender();
    int row = d->findRow(sender);

    if(row > 0){
        emit dataChanged(this->index(row),this->index(row));
    }

}

