
#include <sys/types.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/stat.h>
#ifndef WIN32
#include <sys/queue.h>
#include <unistd.h>
#endif
#include <time.h>
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include <event.h>
#include <evutil.h>

#include "Logging.h"
#include "Logging.cc"

#include <pthread.h>
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int lasttime;

static void
timeout_cb(int fd, short event, void *arg)
{
	struct timeval tv;
	struct event *exit_timeout_cb = static_cast<struct event*>(arg);
	int newtime = time(NULL);

	// LOG_ERROR(" :called at %d: %d\n", newtime, newtime - lasttime);
	lasttime = newtime;

	evutil_timerclear(&tv);
	tv.tv_sec = 2;
	event_add(exit_timeout_cb, &tv);
	sleep(2);
}


class Global_obj
{
public:
	~Global_obj();
};

Global_obj::~Global_obj()
{
	LOG_INFO(" dtcor !!！\n");
	pthread_mutex_lock(&mtx);
	LOG_INFO("unlock mutex sucess!!！\n");
	pthread_mutex_unlock(&mtx);
}

static void* threadFunc(void *arg)
{
	pthread_mutex_lock(&mtx);
	LOG_INFO(" lock mutex sucess!!！\n");
	exit(-1);
	LOG_INFO(" unlock mutex !!!\n");
	pthread_mutex_unlock(&mtx);
}

Global_obj A;

int
main (int argc, char **argv)
{
	// struct event timeout;
	// struct timeval tv;

	// /* Initalize the event library */
	// event_init();

	// /* Initalize one event */
	// evtimer_set(&timeout, timeout_cb, &timeout);

	// evutil_timerclear(&tv);
	// tv.tv_sec = 2;
	// event_add(&timeout, &tv);
	// lasttime = time(NULL);

	// event_dispatch();

	pthread_t thr;
	int s = pthread_create(&thr, NULL, threadFunc, NULL);
	if(s != 0)
	{
		LOG_ERROR("create thread error!");
		exit(1);
	}
	sleep(30);


	return (0);
}

