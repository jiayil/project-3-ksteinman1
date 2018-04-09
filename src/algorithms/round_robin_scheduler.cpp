#include "round_robin_scheduler.h"

using namespace std;


SchedulingDecision* RoundRobinScheduler::get_next_thread(const Event* event) {
  SchedulingDecision* dec = new SchedulingDecision();
  dec->thread = rthreads.front();
  dec->time_slice = time_slice;
if(rthreads.size() > 0){ 
  rthreads.pop();
  dec->explanation = "Selected from " + to_string(rthreads.size()) + "Threads; will run for at most 3 ticks.";
}
  return dec;
}


void RoundRobinScheduler::enqueue(const Event* event, Thread* thread) {
  if(thread!=NULL){
	rthreads.push(thread);
  }
}


bool RoundRobinScheduler::should_preempt_on_arrival(const Event* event) const { //is preemptive
  return true;
}


size_t RoundRobinScheduler::size() const {
  return rthreads.size();
}
