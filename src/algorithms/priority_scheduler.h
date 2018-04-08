#pragma once
#include "algorithms/scheduler.h"
#include "types/event.h"
#include "types/scheduling_decision.h"
#include "types/thread.h"
#include <queue>
#include "types/process.h"

/**
 * Represents a scheduling queue that gives threads of each type a different
 * priority.
 */
class PriorityScheduler : public Scheduler {
public:

  virtual SchedulingDecision* get_next_thread(const Event* event) override;


  virtual void enqueue(const Event* event, Thread* thread) override;


  virtual bool should_preempt_on_arrival(const Event* event) const override;


  virtual size_t size() const override;

private:

  // TODO: add any instance variables you need
  std::queue<Thread*> queue1;
  std::queue<Thread*> queue2;
  std::queue<Thread*> queue3;
  std::queue<Thread*> queue4;
};
