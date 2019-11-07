#include "processagent.h"

ProcessAgent::ProcessAgent(QObject *parent) : QObject(parent),
    m_pProcess(new QProcess())
{
}

ProcessAgent::ProcessAgent(const ProcessAgentInfo &base, QObject *parent):QObject(parent),
    m_pProcess(new QProcess()),
    m_baseInfo(base),
    m_bInited(false)
{

}

ProcessAgent::~ProcessAgent()
{
    delete m_pProcess;
}

void ProcessAgent::start()
{
    if(!m_bInited)
    {
        init();
    }

    m_pProcess->start();
}

void ProcessAgent::stop()
{
    m_pProcess->terminate();
}

QString ProcessAgent::toJson()
{
    return "";
}

bool ProcessAgent::init()
{
    bool ret = true;
    if(! m_bInited){
        m_bInited = true;
        //connect(this->m_pProcess,SIGNAL(started()),this,SIGNAL(sg_started()));
        //connect(this->m_pProcess,SIGNAL(finished()),this,SLOT(finished()));
        connect(this->m_pProcess,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(stateChanged(QProcess::ProcessState)));
    }
    return  ret;
}

void ProcessAgent::setBaseInfo(const ProcessAgentInfo &baseInfo)
{
    m_baseInfo = baseInfo;
}

QProcess::ProcessState ProcessAgent::getProcessState()
{
    return this->m_pProcess->state();
}

ProcessAgentInfo &ProcessAgent::getBaseInfo()
{
    return m_baseInfo;
}


