
#include "qtarootshell.h"


Qtarootshell *qtarootshell_instance = nullptr;
Qtarootshell::~Qtarootshell(){
    process->write("exit\n");
    process->waitForFinished();
    delete process;
}
Qtarootshell::Qtarootshell() : QObject(){
    process = new QProcess();
    process->start("su");
    if (!process->waitForStarted()) {
        qDebug() << "Failed to start root shell";
    }
}






