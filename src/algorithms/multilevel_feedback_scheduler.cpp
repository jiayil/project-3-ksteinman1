#include "algorithms/multilevel_feedback_scheduler.h"
#include "types/process.h"

using namespace std;


SchedulingDecision* MultilevelFeedbackScheduler::get_next_thread(
    const Event* event) {
  
 // for(int i = 0; i < NUM_QUEUES; i++){
//	robins[i] = robin;
  //}

  SchedulingDecision* dec = new SchedulingDecision();

//  for(int i = 0; i < NUM_QUEUES; i++){
//	if(robins[i]->get_next_thread(event)->thread != NULL){
//		dec->thread = robins[i]->get_next_thread(event)->thread;		//robins[i];
//		break;
//	}
 // }

  if(q1.size() > 0){
	dec->thread = q1.front();
	q1.pop();
  }else if(q2.size() > 0){
	dec->thread = q2.front();
	q2.pop();
  }else if(q3.size() > 0){
	dec->thread = q3.front();
	q3.pop();
  }else if(q4.size() > 0){
	dec->thread = q4.front();
	q4.pop();
  }else if(q5.size() > 0){
	dec->thread = q5.front();
	q5.pop();
  }else if(q6.size() > 0){
	dec->thread = q6.front();
	q6.pop();
  }else{
	return NULL;
  }  
  
  dec->explanation = "Selected from threads...";
  dec->time_slice = 3;

  return dec;
}


void MultilevelFeedbackScheduler::enqueue(const Event* event, Thread* thread) {
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


  return size;
}
