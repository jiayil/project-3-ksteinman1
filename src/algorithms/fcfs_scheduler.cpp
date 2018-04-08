#include "fcfs_scheduler.h"

using namespace std;


SchedulingDecision* FcfsScheduler::get_next_thread(const Event* event) {
  //SchedulingDecision* next;
  Thread* nextthread = NULL;
  //return scheduling decision for next thread from queue
  if(!threads.empty()){
 	nextthread = threads.front();
	threads.pop();
//	next->thread =  nextthread;
  }
  //don't change time slice because it won't be preempted
//  next->explanation = "Next thread comes from front of thread queue for FCFS scheduling.";
//  return next;
  SchedulingDecision* dec = new SchedulingDecision;
  dec->thread = nextthread;
  dec->explanation = "Selected from " + to_string(threads.size()) + "threads; will run to completion of burst.";
  //no preempting
  dec->time_slice = -1; 
  return dec;
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
  //return size of queue
  return threads.size();
}
