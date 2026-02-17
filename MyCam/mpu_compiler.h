#ifndef MPU_COMPILER_H
#define MPU_COMPILER_H

#include <QObject>
#include <QProcess>
#include <QThread>

class MPU_CompilerWorker : public QObject
{
    Q_OBJECT
public slots:
    void doWork(const QStringList &arguments);

private slots:
    void compilerFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void readStandardOutput();

private:
    bool m_recordRotateLabelChange;

signals:
    void resultReady(const QString &result);
    void sigRotatelabel(bool rotate_flag);
};

class MPU_CompilerController : public QObject
{
    Q_OBJECT

public:
    explicit MPU_CompilerController();
    ~MPU_CompilerController();

    void sendOperateSignal(const QStringList &);

signals:
    void operate(const QStringList &);
    void threadFinished();
    void sigSendRotate(const bool);

private slots:
    void handleResults(const QString &);
    void handleRotate(const bool);

private:
    QThread workerThread;
};

#endif // MPU_COMPILER_H
