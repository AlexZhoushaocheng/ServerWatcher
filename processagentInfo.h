#ifndef PROCESSAGENTBASE_H
#define PROCESSAGENTBASE_H

#include <QObject>

class ProcessAgentInfo:public QObject{

    Q_GADGET
public:
    ProcessAgentInfo(QObject *parent = nullptr);

    ProcessAgentInfo(const int& id,const QString& path,const QString& alias,const QString& parameters,const QString& workdir,bool watch,const int& autoRestartCount);

    ProcessAgentInfo(const ProcessAgentInfo &base);
    ~ProcessAgentInfo();

    ProcessAgentInfo& operator=(const ProcessAgentInfo& base);

    int getId() const;
    void setId(int value);

    const QString& getPath() const;
    void setPath(const QString &value);

    const QString& getAlias() const;
    void setAlias(const QString &value);

    const QString& getParameters() const;
    void setParameters(const QString &value);

    const QString& getWorkdir() const;
    void setWorkdir(const QString &value);

    bool getWatch() const;
    void setWatch(bool value);

    int getAutoRestartCount() const;
    void setAutoRestartCount(int value);

protected:

    int id;
    QString path;
    QString alias;
    QString parameters;
    QString workdir;
    bool watch;
    int autoRestartCount;

    friend class ProcessAgent;
};
#endif // PROCESSAGENTBASE_H
