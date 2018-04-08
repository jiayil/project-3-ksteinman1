#include "algorithms/priority_scheduler.h"

using namespace std;


SchedulingDecision* PriorityScheduler::get_next_thread(const Event* event) {
  SchedulingDecision* dec = new SchedulingDecision();
  
  if(queue1.size() > 0){
	dec->thread = queue1.front();
	queue1.pop();
  }else if(queue2.size() > 0){
	dec->thread = queue2.front();
	queue2.pop();
  }else if(queue3.size() > 0){
	dec->thread = queue3.front();
	queue3.pop();
  }else if(queue4.size() > 0){
	dec->thread = queue4.front();
	queue4.pop();
  }else{
	return NULL;
  }

  dec->explanation = "Selected based on priority.....";
  return dec;
}


void PriorityScheduler::enqueue(const Event* event, Thread* thread) {
  Process::Type t = event->thread->process->type;

  if(t == Process::Type::SYSTEM){
	queue1.push(thread);
  }else if(t == Process::Type::INTERACTIVE){
	queue2.push(thread);
  }else if(t == Process::Type::NORMAL){
	queue3.push(thread);
  }else{
	queue4.push(thread);
  }
return;
}


bool PriorityScheduler::should_preempt_on_arrival(const Event* event) const {
  // not preemptive
  return false;
}


size_t PriorityScheduler::size() const {
  return queue1.size() + queue2.size() + queue3.size() + queue4.size();
}
