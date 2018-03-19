#include "fcfs_scheduler.h"

using namespace std;


SchedulingDecision* FcfsScheduler::get_next_thread(const Event* event) {
  //
  return nullptr;
}


void FcfsScheduler::enqueue(const Event* event, Thread* thread) {
  //add incoming thread to queue of threads
  threads.push(thread);
}


bool FcfsScheduler::should_preempt_on_arrival(const Event* event) const {
  //does not preempt
  return false;
}


size_t FcfsScheduler::size() const {
  return 0;
}
