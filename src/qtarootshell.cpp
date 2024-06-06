
#include "qtarootshell.h"


Qtarootshell *qtarootshell_instance = nullptr;
Qtarootshell::~Qtarootshell(){
    if (process){
        process->write("exit\n");
        process->waitForFinished(5);
        process->terminate();
        process->kill();
        delete process;
        process = nullptr;
    }
    if(process2){
        process2->write("exit\n");
        process2->waitForFinished(5);
        process2->terminate();
        process2->kill();
        delete process2;
        process2 = nullptr;
    }
}
Qtarootshell::Qtarootshell() : QObject(){
    init_process();
}

void Qtarootshell::init_process(){
    if (process){
        process->write("exit\n");
        process->waitForFinished(5);
        process->terminate();
        process->kill();
        delete process;
        process = nullptr;
    }
    process = new QProcess();
    process->start("su");
    if (!process->waitForStarted()) {
        qDebug() << "Failed to start root shell";
    }
}

void Qtarootshell::init_process2(){
    if (process2){
        process2->write("exit\n");
        process2->waitForFinished(5);
        process2->terminate();
        process2->kill();
        delete process2;
        process2 = nullptr;
    }
    process2 = new QProcess();
    // process2.setProcessChannelMode(QProcess::MergedChannels);
    connect(process2,&QProcess::readyReadStandardOutput,this,[=](){
        emit this->process2_readyReadStandardOutput(process2->readAllStandardOutput());
    });
    connect(process2,&QProcess::readyReadStandardError,this,[=](){
        emit this->process2_readyReadStandardError(process2->readAllStandardError());
    });
    process2->start("su");
    if (!process2->waitForStarted()) {
        qDebug() << "Failed to start root shell2";
    }
}






