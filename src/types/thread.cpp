#include "types/thread.h"
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

void Thread::set_ready(unsigned int time){
  previous_state = current_state;
  current_state = State::READY;

  state_change_time = time;


  if(previous_state == State::RUNNING || previous_state == State::BLOCKED){
	pop_burst(time);
  }
 // cout << "\tTransitioned to READY" << endl;
}

unsigned int Thread::set_running(unsigned int time){
  previous_state = current_state;
  current_state = State::RUNNING;

  state_change_time = time;
 // cout << "\tTransitioned to RUNNING" << endl;
  return bursts.front()->length;
}

unsigned int Thread::set_blocked(unsigned int time){
  pop_burst(time);

  if(bursts.size() == 0){
	return -1;
  }

  previous_state = current_state;
  current_state = State::BLOCKED;

  state_change_time = time;

  return bursts.front()->length;
}

void Thread::set_exit(unsigned int time){
  previous_state = current_state;
  current_state = State::EXIT;

  end_time = time;
  state_change_time  = time;
}

void Thread::pop_burst(unsigned int time){
  Burst* burst = bursts.front();

  if(burst->length <= (time - state_change_time)){
	bursts.pop();
  }else{
	burst->length = time - state_change_time;
  }

  if(burst->type == Burst::Type::CPU){
	service_time += time - state_change_time;
  }else if(burst->type == Burst::Type::IO){
	io_time += time - state_change_time;
  }

}
