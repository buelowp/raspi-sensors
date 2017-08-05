/*
 * helpers.cc
 *
 *  Created on: Aug 4, 2017
 *      Author: pete
 */
#include "helpers.h"

namespace sensors {
	void sleep(int sec, int msec)
	{
		struct timespec ts;

		ts.tv_sec = sec;
		ts.tv_nsec = msec * 1000;
		nanosleep(&ts, NULL);
	}
}

