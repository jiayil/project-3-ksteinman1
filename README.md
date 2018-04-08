# Project 3 - CPU Scheduling Simulator

1. Name: Katrina Steinman

2. List of Files:

fcfs_scheduler.{cpp,h} = Functions and variables for the FCFS algorithm.

multilevel_feedback_scheduler.{cpp,h} = Functions and variables for the MLFS algorithm.

priority_scheduler.{cpp,h} = Functions and variables for the PRIORITY algorithm.

round_robin_scheduler.{cpp,h} = Functions and variables for the RR algorithm.

logger.{cpp,h} = methods for printing output

flags.{cpp,h} = implementing help, verbose, and algorithm flags

burst.h = properties for the Burst object type

event.h = properties for the Event object type

process.h = properties for the Process object type

system_stats = properties for the Stats object type

thread.{cpp,h} = functions and variables for the Thread object type

scheduling_decision.h = properties for the SchedulingDecision object type

simulation.{cpp,h} = methods for running the simulated scheduler


3. Hours spent: 40

4. SYSTEM processes are added to the highest priority queue, INTERACTIVE
processes are added to the next highest priority queue, followed by 
NORMAL and BATCH. I wanted to optimize CPU utilization, and I did this
by implementing the Round Robin algorithm on each queue. This is where
the usage of preemption came into play. There are a total of 6 queues, 
and though starvation is not possible within each individual queue,
starvation is possible overall if a process sits in a low priority
queue for a long time. The usage of Round Robin makes this algorithm
fair, since all processes within a queue get a chance, but it is not
fair since certain types of processes are automatically prioritized over
others. 

