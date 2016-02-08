/*

  Display an animated rotating cursor in a seperate thread.
  Steve Connet (c) 2002
  Thu Feb 21 13:00:33 MST 2002

 */

#ifndef __WAITCURSOR_H_
#define __WAITCURSOR_H_

#include <pthread.h>

class WaitCursor
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_t tid;
    bool quit;
    float delay; /* seconds */

    void *thread();
    static void *thread_(void *wc)
    {
        return reinterpret_cast<WaitCursor *>(wc)->thread();
    }

public:
    WaitCursor(bool start = false);
    ~WaitCursor();

    bool start(float dlay = 0.15f);
    void stop();
};

#endif // __WAITCURSOR_H_
