#include "processagentInfo.h"
#include <QtDebug>

ProcessAgentInfo::ProcessAgentInfo(QObject *parent):QObject(parent),
id(-1),
watch(false),
autoRestartCount(0)
{

}

ProcessAgentInfo::ProcessAgentInfo(const int &id, const QString &path, const QString &alias, const QString &parameters, const QString &workdir, bool watch, const int &autoRestartCount):
    id(id),
    path(path),
    alias(alias),
    parameters(parameters),
    workdir(workdir),
    watch(watch),
    autoRestartCount(autoRestartCount)
{

}

ProcessAgentInfo::ProcessAgentInfo(const ProcessAgentInfo &base)
{
    this->id = base.id;
    this->path = base.path;
    this->alias = base.alias;
    this->parameters = base.parameters;
    this->workdir = base.workdir;
    this->watch = base.watch;
    this->autoRestartCount = base.autoRestartCount;
}

ProcessAgentInfo::~ProcessAgentInfo()
{
    qDebug()<< "delete";
}

ProcessAgentInfo &ProcessAgentInfo::operator=(const ProcessAgentInfo &base)
{
    this->id = base.id;
    this->path = base.path;
    this->alias = base.alias;
    this->parameters = base.parameters;
    this->workdir = base.workdir;
    this->watch = base.watch;
    this->autoRestartCount = base.autoRestartCount;

    return *this;
}

int ProcessAgentInfo::getId() const
{
    return id;
}

void ProcessAgentInfo::setId(int value)
{
    id = value;
}

const QString& ProcessAgentInfo::getPath() const
{
    return path;
}

void ProcessAgentInfo::setPath(const QString &value)
{
    path = value;
}

const QString& ProcessAgentInfo::getAlias() const
{
    return alias;
}

void ProcessAgentInfo::setAlias(const QString &value)
{
    alias = value;
}

const QString& ProcessAgentInfo::getParameters() const
{
    return parameters;
}

void ProcessAgentInfo::setParameters(const QString &value)
{
    parameters = value;
}

const QString& ProcessAgentInfo::getWorkdir() const
{
    return workdir;
}

void ProcessAgentInfo::setWorkdir(const QString &value)
{
    workdir = value;
}

bool ProcessAgentInfo::getWatch() const
{
    return watch;
}

void ProcessAgentInfo::setWatch(bool value)
{
    watch = value;
}

int ProcessAgentInfo::getAutoRestartCount() const
{
    return autoRestartCount;
}

void ProcessAgentInfo::setAutoRestartCount(int value)
{
    autoRestartCount = value;
}
