#ifndef SOURCEDETECTIONMANAGER_STRING_H
#define SOURCEDETECTIONMANAGER_STRING_H
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
class SourceDetectionManager_string
{
public:
    SourceDetectionManager_string();
    int File2String(QString filePath, QString &string, QString &outputBufa);
    int Modify(QString input, QString &output);
private:
};

#endif // SOURCEDETECTIONMANAGER_STRING_H
