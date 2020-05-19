
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <unistd.h>
#include <time.h>

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include "Logging.h"
#include "Logging.cc"

#include <pthread.h>
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


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
	char pRuleTmp[256] = {0};
	pthread_t thr;
	int s = pthread_create(&thr, NULL, threadFunc, NULL);
	if(s != 0)
	{
		LOG_ERROR("create thread error!");
		exit(1);
	}
	int len = snprintf(pRuleTmp, 20, "yuan");
	LOG_INFO("----------yuanIN:%d\n", len);
	sleep(4);


	return (0);
}

