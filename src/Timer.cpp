/*
 * Timer.cpp
 *
 *  Created on: 12-Feb-2009
 *      Author: 1parkk
 */

#include "SDL/SDL.h"
#include "Timer.h"

Timer::Timer() {
	started_ticks = 0;
	paused_ticks = 0;
	started = false;
	paused = false;
}

Timer::~Timer() { }

void Timer::start(void){
	started = true;
	paused = false;
	started_ticks = SDL_GetTicks();
}

void Timer::stop(void){
	if(started == true || paused == true){
		started = false;
		paused = false;
		started_ticks = 0;
		paused_ticks = 0;
	}
}

void Timer::pause(){
	if( paused == false && started == true ){
		paused = true;
		paused_ticks = SDL_GetTicks() - started_ticks;
	}
}

void Timer::unpause(){
	if( paused == true && started == true ){
		paused = false;
		started_ticks = SDL_GetTicks() - paused_ticks;
		paused_ticks = 0;
	}
}

Uint Timer::get_ticks(void){
	if(started == true){
		if(paused == true){
			return paused_ticks;
		}else if(paused == false){
			return ( SDL_GetTicks() - started_ticks );
		}
	}
	return 0;
}

bool Timer::is_started(void){
	return started;
}

bool Timer::is_paused(void){
	return paused;
}
