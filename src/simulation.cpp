#include "simulation.h"
#include "types/event.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include "types/system_stats.h"

using namespace std;


void Simulation::run(const string& filename) {
  read_file(filename);

  // While their are still events to process, invoke the corresponding methods
  // to handle them.
  while (!events.empty()) {
    const Event* event = events.top();
    events.pop();

    // Invoke the appropriate method on the scheduler for the given event type.
    switch (event->type) {
    case Event::THREAD_ARRIVED:
      handle_thread_arrived(event);
      break;

    case Event::THREAD_DISPATCH_COMPLETED:
      handle_thread_dispatch_completed(event);
      break;

    case Event::PROCESS_DISPATCH_COMPLETED:
      handle_process_dispatch_completed(event);
      break;

    case Event::CPU_BURST_COMPLETED:
      handle_cpu_burst_completed(event);
      break;

    case Event::IO_BURST_COMPLETED:
      handle_io_burst_completed(event);
      break;

    case Event::THREAD_COMPLETED:
      handle_thread_completed(event);
      break;

    case Event::THREAD_PREEMPTED:
      handle_thread_preempted(event);
      break;

    case Event::DISPATCHER_INVOKED:
      handle_dispatcher_invoked(event);
      break;
    }

    // Free the event's memory.
    delete event;
  }
}


//==============================================================================
// Event-handling methods
//==============================================================================


void Simulation::handle_thread_arrived(const Event* event) {
  //Set Ready
  //Then enqueue

  event->thread->set_ready(event->time);
  scheduler->enqueue(event, event->thread);
  
  //active_thread is the thread that is currently executing
  //events is a queue containing objects of event type
  if(!active_thread){
  	//if we are here, then the processor is idle --> move to DISPATCHER INVOKED
  	//using constructor works!
  	events.push(new Event(Event::DISPATCHER_INVOKED, event->time, NULL, NULL));
  }

  //should print info here----------------------------  

  cout << "event: THREAD_ARRIVED" << endl;
}


void Simulation::handle_thread_dispatch_completed(const Event* event) {
  // Set RUNNING
  //Set last thread = current thread
  int burst_length = event->thread->set_running(event->time);
  int time_slice = event->scheduling_decision->time_slice;


  //See if time slice is less than burst time
  //if yes, move to Thread Preempted
  //if no, move to CPU burst completed
  if(time_slice < burst_length){
	events.push(new Event(Event::THREAD_PREEMPTED, event->time + time_slice, event->thread, NULL));
  }else{
	events.push(new Event(Event::CPU_BURST_COMPLETED, event->time + burst_length, event->thread, NULL));
  }
  
   cout << "event: THREAD_DISPATCH_COMPLETED" << endl;
}


void Simulation::handle_process_dispatch_completed(const Event* event) {
  // Set RUNNING
  //Set last thread = current thread
  int burst_length = event->thread->set_running(event->time);
  int time_slice = event->scheduling_decision->time_slice;

  //See if time slice is less than burst time
  //if yes, move to Thread Preempted
  //if no, move to CPU burst completed
   if(time_slice < burst_length){
	events.push(new Event(Event::THREAD_PREEMPTED, event->time + time_slice, event->thread, NULL));
  }else{
	events.push(new Event(Event::CPU_BURST_COMPLETED, event->time + burst_length, event->thread, NULL));
  }

  cout << "event: PROCESS_DISPATCH_COMPLETED" << endl;
}


void Simulation::handle_cpu_burst_completed(const Event* event) {
  // Pop burst, unset current thread
  //Last CPU Burst?
  //If yes, thread completed --> Set exit!
  //If no, Move to IO burst completed, set Blocked
  cout << "event: CPU_BURST_COMPLETED" << endl;
}


void Simulation::handle_io_burst_completed(const Event* event) {
  //Set READY
  //Enqueue and pop burst
  event->thread->set_ready(event->time);
  scheduler->enqueue(event, event->thread);

  //Go back to checking if processor is idle
  if(!active_thread){
	events.push(new Event(Event::DISPATCHER_INVOKED, event->time, NULL, NULL));
  }

  cout << "event: IO_BURST_COMPLETED" << endl;
}


void Simulation::handle_thread_completed(const Event* event) {
  // Set exit
  cout << "event: THREAD_COMPLETED" << endl;
}


void Simulation::handle_thread_preempted(const Event* event) {
  // Set READY
  //Enqueue
  //Decrease CPU Burst
  event->thread->set_ready(event->time);
  scheduler->enqueue(event, event->thread);
  prev_thread = active_thread;
  //active_thread = NULL;

  
  //Go back to invoking dispatcher
  if(!active_thread){
	events.push(new Event(Event::DISPATCHER_INVOKED, event->time, NULL, NULL));
  }
  cout << "event: THREAD_PREEMPTED" << endl;
}


void Simulation::handle_dispatcher_invoked(const Event* event) {
  //Get scheduling decision and set current thread
  SchedulingDecision* dec = scheduler->get_next_thread(event); 
   
  if(!dec->thread){
	return; 
  }
 
  active_thread = dec->thread;
  
  //Decision made?
  //See if Process or Thread Switch
  //If Thread, move to Thread Dispatch
  //If process, move to Process Dispatch complete


  //soooo if current and previous threads are not null and both threads belong to the same process
  if(active_thread && prev_thread && (prev_thread->process == active_thread->process)){
	//Thread dispatch is complete
	events.push(new Event(Event::THREAD_DISPATCH_COMPLETED, event->time + thread_switch_overhead, dec->thread, dec));
	stats.dispatch_time += thread_switch_overhead; 
  }else{
	//Process dispatch is complete
	events.push(new Event(Event::PROCESS_DISPATCH_COMPLETED, event->time + process_switch_overhead, dec->thread, dec));
	stats.dispatch_time += process_switch_overhead; 

  }


  cout << "event: DISPATCHER_INVOKED" << endl;
}


//==============================================================================
// Utility methods
//==============================================================================


void Simulation::add_event(Event* event) {
  if (event != nullptr) {
    events.push(event);
  }
}


void Simulation::read_file(const string& filename) {
  ifstream file(filename.c_str());

  if (!file) {
    cerr << "Unable to open simulation file: " << filename << endl;
    exit(EXIT_FAILURE);
  }

  size_t num_processes;

  // Read the total number of processes, as well as the dispatch overheads.
  file >> num_processes >> thread_switch_overhead >> process_switch_overhead;

  // Read in each process.
  for (size_t p = 0; p < num_processes; p++) {
    Process* process = read_process(file);

    processes[process->pid] = process;
  }
}


Process* Simulation::read_process(istream& in) {
  int pid, type;
  size_t num_threads;

  // Read in the process ID, its type, and the number of threads.
  in >> pid >> type >> num_threads;

  // Create the process and register its existence in the processes map.
  Process* process = new Process(pid, (Process::Type) type);

  // Read in each thread in the process.
  for (size_t tid = 0; tid < num_threads; tid++) {
    process->threads.push_back(read_thread(in, tid, process));
  }

  return process;
}


Thread* Simulation::read_thread(istream& in, int tid, Process* process) {
  int arrival_time;
  size_t num_cpu_bursts;

  // Read in the thread's arrival time and its number of CPU bursts.
  in >> arrival_time >> num_cpu_bursts;

  Thread* thread = new Thread(arrival_time, tid, process);

  // Read in each burst in the thread.
  for (size_t n = 0, burst_length; n < num_cpu_bursts * 2 - 1; n++) {
    in >> burst_length;

    Burst::Type burst_type = (n % 2 == 0)
        ? Burst::CPU
        : Burst::IO;

    thread->bursts.push(new Burst(burst_type, burst_length));
  }

  // Add an arrival event for the thread.
  events.push(new Event(Event::THREAD_ARRIVED, thread->arrival_time, thread));

  return thread;
}


SystemStats Simulation::calculate_statistics() {
  // TODO: your code here (optional; feel free to modify code structure)
  return SystemStats();
}
