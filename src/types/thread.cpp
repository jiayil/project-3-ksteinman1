#include "types/thread.h"
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

void Thread::set_ready(unsigned int time){
  previous_state = current_state;
  current_state = State::READY;

  state_change_time = time;

  cout << "\tTransitioned to READY" << endl;
}

unsigned int Thread::set_running(unsigned int time){
  previous_state = current_state;
  current_state = State::RUNNING;

  state_change_time = time;
  cout << "\tTransitioned to RUNNING" << endl;
  return bursts.front()->length;
}
