/*
 * Cullen Williams & Garrick Hutcheson
 * Scheduler.h
 */

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "Job.h"
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <string>
using std::string;

class Scheduler {
public:
  Scheduler();
  Scheduler(int numJobs, int procs = 8);

  void Run();

  /*
    Tick


    prints the job_id numbers of any job submitted during the tick
    prints the job_id of any jobs compleated during the tick
  */
  void Tick();

  /*
    insertJob
    adds a job to the priority que
  */
  void insertJob(int id, int procs = 0, int ticks = 0, string desc = "NULL");

  /*
    findShortest
    acceses the top(shortest) element in the priority queue
  */
  Job findShortest();

  /*
    deleteShortest
  */
  Job deleteShortest();

  void waitForUserInput();

  /*
    checkAvailiability
  */
  bool checkAvailiability(int procs);

  /*
    runJob
  */
  void runJob();

  /*
    decrementTimer
  */
  void decrementTimer();

  /*
    releaseProcs
  */
  void releaseProcs(int procs);

  /**/
  void getAJob();
  /**/
  void fillQueue();
  /**/
  void decrementEggTimers();
  /**/
  string deleteByTimer();

  int getTJobs();
  void decrementTJobs();

private:
  std::priority_queue<Job, std::vector<Job>, std::greater<Job> > procaQueue;
  int avaliableProcs;    // keeps track of free proccessors
  int allTheProcs;
  int totalJobs; //keeps track of the total number of jobs for independent naming
  int totalJobsToDo;
  std::list<Job> running;
}; 
#endif