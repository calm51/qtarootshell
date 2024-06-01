#include <QString>
#include <QApplication>
#include <QDebug>
#include <QScreen>
#include "QtAndroid"
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QProcess>


#ifndef QTAROOTSHELL_H
#define QTAROOTSHELL_H


class Qtarootshell;
extern Qtarootshell *qtarootshell_instance;

class Qtarootshell : public QObject{
    Q_OBJECT

public:
    Qtarootshell(const Qtarootshell&) = delete;
    Qtarootshell& operator=(const Qtarootshell&) = delete;
    static Qtarootshell* instance() {
        if (qtarootshell_instance){
            return qtarootshell_instance;
        }
        qtarootshell_instance = new Qtarootshell();
        return qtarootshell_instance;
    }
    ~Qtarootshell();


    // =======================

    static QPair<int,QPair<QString,QString>> executeRootCommand(const QString &command) {
        QPair<int,QPair<QString,QString>> result;
        QProcess process;
        QStringList arguments;
        arguments << "-c" << command;
        process.start("su", arguments);
        if (!process.waitForStarted()) {
            result.first = -1;
            result.second.second = "Failed to start process";
            return result;
        }
        if (!process.waitForFinished()) {
            result.first = -1;
            result.second.second = "Failed to finish process";
            return result;
        }
        result.first = process.exitCode();
        result.second.first = process.readAllStandardOutput();
        result.second.second = process.readAllStandardError();
        return result;
    }

    QPair<QString,QString> executeCommand(const QString &command) {
        QPair<QString,QString> result;
        if (process->state() != QProcess::Running) {
            result.second = "Root shell is not running";
            return result;
        }
        process->write(command.toUtf8() + "\n");
        if (!process->waitForReadyRead()) {
            result.second = "No output from command";
            return result;
        }
        result.first = process->readAllStandardOutput();
        result.second = process->readAllStandardError();
        return result;
    }


    // =======================


private:
    Qtarootshell();
    QProcess *process;

signals:


};

#endif
