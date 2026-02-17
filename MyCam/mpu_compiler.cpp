#include "mpu_compiler.h"
#include <QDebug>
#include <QTextCodec>

void MPU_CompilerWorker::doWork(const QStringList &arguments)
{
    qDebug() << "receive the execute signal";
    qDebug() << "\tCurrent thread ID:" << QThread::currentThreadId();

    QProcess *mpuProcess = new QProcess;
    QString program = "stdbuf";

    m_recordRotateLabelChange = 0;
    emit sigRotatelabel(0);
    connect(mpuProcess, &QProcess::readyReadStandardOutput, this, &MPU_CompilerWorker::readStandardOutput);
    connect(mpuProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(compilerFinished(int,QProcess::ExitStatus)));


    mpuProcess->start(program, arguments);
    qDebug() << "[Current process ID: " << mpuProcess->processId() << "]";
}

void MPU_CompilerWorker::compilerFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "mpu process finish." << exitCode << exitStatus;
    qDebug() << "\tFinish the work and sent the result Ready signal\n";
    emit resultReady("result...");
}

void MPU_CompilerWorker::readStandardOutput()
{
    QProcess *process = qobject_cast<QProcess *>(sender());
    QTextCodec *codec = QTextCodec::codecForLocale();
    QString str = codec->toUnicode(process->readAllStandardOutput());
    //qDebug() << str;
    QString prefix = "roll = ";
    QString suffix = ".";
    int roll_index = str.indexOf(prefix) + 7;
    str = str.mid(roll_index, (str.indexOf(suffix, 20) - roll_index));
    // qDebug("%d", str.toInt());
    if(str.toInt() > 45 || str.toInt() < -45){
        if(m_recordRotateLabelChange != 1){
            m_recordRotateLabelChange = 1;
            qDebug() << "Need to Rotate";
            emit sigRotatelabel(1);
        }
    }else{
        if(m_recordRotateLabelChange != 0){
            m_recordRotateLabelChange = 0;
            qDebug() << "Need to keep horizon";
            emit sigRotatelabel(0);
        }
    }
}

//-------------------------------------------------//

MPU_CompilerController::MPU_CompilerController()
{
    MPU_CompilerWorker *compiler = new MPU_CompilerWorker;
    compiler->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, compiler, &QObject::deleteLater);
    connect(this, &MPU_CompilerController::operate, compiler, &MPU_CompilerWorker::doWork);
    connect(compiler, &MPU_CompilerWorker::resultReady, this, &MPU_CompilerController::handleResults);
    connect(compiler, &MPU_CompilerWorker::sigRotatelabel, this, &MPU_CompilerController::handleRotate);
    workerThread.start();
}

MPU_CompilerController::~MPU_CompilerController()
{
    qDebug() << "!!!~CompilerController()";
    workerThread.quit();
    workerThread.wait();
}

void MPU_CompilerController::sendOperateSignal(const QStringList &arguments)
{
    qDebug() << "\nemit the signal to execute!";
    qDebug() << "\tCurrent thread ID:" << QThread::currentThreadId() << "\n";
    emit operate(arguments);
}

void MPU_CompilerController::handleResults(const QString &result)
{
    qDebug() << "receive the resultReady signal";
    qDebug() << "\tCurrent thread ID:" << QThread::currentThreadId();
    qDebug() << "\tThe result is:" << result;

    emit threadFinished();
}

void MPU_CompilerController::handleRotate(const bool rotate_flag)
{
    emit sigSendRotate(rotate_flag);
}
