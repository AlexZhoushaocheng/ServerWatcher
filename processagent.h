#ifndef PROCESSAGENT_H
#define PROCESSAGENT_H

#include <QObject>
#include <QProcess>
#include "processagentInfo.h"

class ProcessAgent : public QObject
{
    Q_OBJECT
public:
    explicit ProcessAgent(QObject *parent = nullptr);

    ProcessAgent(const ProcessAgentInfo& base,QObject *parent = nullptr);
    ~ProcessAgent();

    void start();
    void stop();
    QString toJson();

    bool init();

    //没有通过构造传入baseinfo时，使用此接口
    void setBaseInfo(const ProcessAgentInfo &baseInfo);

    //获取进程的运行状态
    QProcess::ProcessState getProcessState();

    ProcessAgentInfo& getBaseInfo();

private:
    QProcess *m_pProcess;
    ProcessAgentInfo m_baseInfo;
    bool m_bInited;
signals:
    //void sg_started();
    //void sg_crash(int id);

    void stateChanged(QProcess::ProcessState newState);

    void sg_ErrorChanelOutput(QString text);
    void sg_NormalChanelOutput(QString text);
public slots:

    //void errorOccurred(QProcess::ProcessError error);
    //void finished(int exitCode, QProcess::ExitStatus exitStatus);
    //void readyReadStandardError();
    //void readyReadStandardOutput();
    //void started();
    //void stateChanged(QProcess::ProcessState newState);

};

#endif // PROCESSAGENT_H
