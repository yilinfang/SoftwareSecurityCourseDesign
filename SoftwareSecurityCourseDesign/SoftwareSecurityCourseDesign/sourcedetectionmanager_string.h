#ifndef SOURCEDETECTIONMANAGER_STRING_H
#define SOURCEDETECTIONMANAGER_STRING_H
#include <QString>
#include <QStringList>
#include <QDebug>
class SourceDetectionManager_string
{
public:
    SourceDetectionManager_string();
    ~SourceDetectionManager_string();
    int Modify(QString &input);
    int LoadCode(QString input);
    int LoadLibs(QStringList input);
private:
    QString code;
    QString libs;
};

#endif // SOURCEDETECTIONMANAGER_STRING_H
