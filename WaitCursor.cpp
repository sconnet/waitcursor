#include "WaitCursor.h"
#include <sys/time.h>
#include <iostream>

WaitCursor::WaitCursor(bool start) :
    quit(false)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    if(start)
    {
        this->start();
    }
}

WaitCursor::~WaitCursor()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

bool WaitCursor::start(float dlay)
{
    delay = dlay;
    return pthread_create(&tid, NULL, thread_, this) == 0;
}

void WaitCursor::stop()
{
    pthread_mutex_lock(&mutex);
    quit = true;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
    pthread_join(tid, NULL);
    tid = 0;
    quit = false;
}

void *WaitCursor::thread()
{
    const long BILLION = 1000000000L;
    int x = 0;
    struct timeval now;
    long dlay = (long)(BILLION * delay);
    while(true)
    {
        gettimeofday(&now, NULL);
        struct timespec timeout = { now.tv_sec, (now.tv_usec * 1000) + dlay };
        pthread_mutex_lock(&mutex);
        pthread_cond_timedwait(&cond, &mutex, &timeout);
        if(quit)
        {
            break;
        }
        pthread_mutex_unlock(&mutex);

        std::cout << '\r' << "|/-\\" [x++ % 4] << std::flush;
    }

    pthread_mutex_unlock(&mutex);
    return 0;
}

