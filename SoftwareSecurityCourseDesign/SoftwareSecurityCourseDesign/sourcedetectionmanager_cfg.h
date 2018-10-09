#ifndef SOURCEDETECTIONMANAGER_CFG_H
#define SOURCEDETECTIONMANAGER_CFG_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QCoreApplication>
#include <QTextCodec>

class sourcedetectionmanager_cfg
{
public:
    sourcedetectionmanager_cfg();
    int LoadCode(QString input);
    int LoadLibs(QStringList input);
    int Compare(QString &outputBufa);
private:
    QString fileName;
    QString scriptsPath;
    QString bufferPath;
    QStringList fileNames;
};

#endif // SOURCEDETECTIONMANAGER_CFG_H
