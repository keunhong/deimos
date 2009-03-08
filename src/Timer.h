/*
 * Timer.h
 *
 *  Created on: 12-Feb-2009
 *      Author: 1parkk
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "common.h"

class Timer {
	Uint started_ticks;
	Uint paused_ticks;
	bool started;
	bool paused;

public:
	Timer();
	virtual ~Timer();

	void start(void);
	void stop(void);
	void pause(void);
	void unpause(void);

	Uint get_ticks(void);

	bool is_started(void);
	bool is_paused(void);
};

#endif /* TIMER_H_ */
