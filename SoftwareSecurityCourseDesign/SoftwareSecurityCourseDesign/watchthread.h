#ifndef WATCHTHREAD_H
#define WATCHTHREAD_H

#include <QThread>

class WatchThread: public QThread
{
public:
    WatchThread();
protected:
    run();
};

#endif // WATCHTHREAD_H
