#include "algorithms/multilevel_feedback_scheduler.h"
#include "types/process.h"
#include "types/thread.h"

using namespace std;


SchedulingDecision* MultilevelFeedbackScheduler::get_next_thread(
    const Event* event) {
  
 // for(int i = 0; i < NUM_QUEUES; i++){
//	robins[i] = robin;
  //}

//(event->thread){
//f(
//

  SchedulingDecision* dec = new SchedulingDecision();

//  for(int i = 0; i < NUM_QUEUES; i++){
//	if(robins[i]->get_next_thread(event)->thread != NULL){
//		dec->thread = robins[i]->get_next_thread(event)->thread;		//robins[i];
//		break;
//	}
 // }
if(event){
  if((q1.size() > 0)){ //&& (q1.front()->current_state == Thread::State::EXIT)){
	dec->thread = q1.front();
	
	//	q2.push(q1.front());
	//}
	q1.pop();
	/*if((event->thread->previous_state == Thread::State::RUNNING) && (event->thread->current_state != Thread::State::EXIT)){
		q2.push(event->thread);
	}*/
  }else if(q2.size() > 0){
	dec->thread = q2.front();
//	q3.push(q2.front());
	q2.pop();
	/*if((event->thread->previous_state == Thread::State::RUNNING) && (event->thread->current_state != Thread::State::EXIT)){
		q3.push(event->thread);
	}*/

  }else if(q3.size() > 0){
	dec->thread = q3.front();
//	q4.push(q3.front());
	q3.pop();
	/*if((event->thread->previous_state == Thread::State::RUNNING) && (event->thread->current_state != Thread::State::EXIT)){
		q4.push(event->thread);
	}*/

  }else if(q4.size() > 0){
	dec->thread = q4.front();
//	q5.push(q4.front());
	q4.pop();
	/*if((event->thread->previous_state == Thread::State::RUNNING) && (event->thread->current_state != Thread::State::EXIT)){
		q5.push(event->thread);
	}*/

  }else if(q5.size() > 0){
	dec->thread = q5.front();
//	q6.push(q5.front());
	q5.pop();
	/*if((event->thread->previous_state == Thread::State::RUNNING) && (event->thread->current_state != Thread::State::EXIT)){
		q6.push(event->thread);
	}*/

  }else if(q6.size() > 0){
	dec->thread = q6.front();
	q6.pop();
  }else{
	return NULL;
  }  
  
  dec->explanation = "Selected from threads based on priority.";
  dec->time_slice = 3;
}
  return dec;
}


void MultilevelFeedbackScheduler::enqueue(const Event* event, Thread* thread) {
if(thread){
  switch(event->thread->process->type){
	case Process::Type::SYSTEM:
		q1.push(thread);		
		break;
	case Process::Type::INTERACTIVE:
		q1.push(thread);
		break;
	case Process::Type::NORMAL:
		q2.push(thread);
		break;
	case Process::Type::BATCH:
		q2.push(thread);
		break;
  }  

 //favor threads that are preempted less
 }
}


bool MultilevelFeedbackScheduler::should_preempt_on_arrival(
    const Event* event) const {
  // is preemptive
  return true;
}


size_t MultilevelFeedbackScheduler::size() const {
  int size = 0;
 
 // for(int i = 0; i < NUM_QUEUES; i++){
//	size += robins[i]->size();
  //}

  size = q1.size() + q2.size() + q3.size() + q4.size() + q6.size() + q5.size();

  return size;
}
