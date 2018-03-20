#include "types/thread.h"


void Thread::set_ready(unsigned int time){
  previous_state = current_state;
  current_state = State::READY;

  state_change_time = time;
}

unsigned int Thread::set_running(unsigned int time){
  previous_state = current_state;
  current_state = State::RUNNING;

  state_change_time = time;

  return bursts.front()->length;
}
