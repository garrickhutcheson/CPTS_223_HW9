/*
 * Cullen Williams & Garrick Hutcheson
 * Scheduler.cpp
 */

#include "Scheduler.h"



Scheduler::Scheduler() {
  allTheProcs = 13;
  avaliableProcs = allTheProcs;
  totalJobs = 0; // starts at the first line of a file
  fin.open("Input.txt");
  exitScheduler = false;
}
Scheduler::Scheduler(int numJobs, int procs) {
  avaliableProcs = procs;
  allTheProcs = procs;
  totalJobs = 0;
  fin.open("Input.txt");
  exitScheduler = false;
}

//runs jobs from file w/o user input
void Scheduler::Run() {
  do {  
    Tick();
      if(exitScheduler){
      std::cout << "exiting" <<std::endl;
      return;
      }
  } while (!(procaQueue.top().getDesc()=="exit") || !running.empty());
}

void Scheduler::waitForUserInput() {
  string jobdesk="";
  int numprocs=0;
  int numticks=0;
  std::cout << "enter Job description " << std::endl;
  std::cin >> jobdesk;
  std::cout << "enter required processors " << std::endl;
  std::cin >> numprocs;
  std::cin >> numticks;
  if(numprocs !=0)
    int id = totalJobs;
}

/*
  Tick
  prints the job_id numbers of any job submitted during the tick
  prints the job_id of any jobs compleated during the tick
*/
void Scheduler::Tick() {
 // waitForUserInput();
 std::cout<<"\nTICK\n";
 if (!fin.eof())
 {
  exitScheduler = getAJobFromTextFile();
 } else {
   insertJob(-1,allTheProcs,0,"exit");
 }
 if(!procaQueue.empty() || !exitScheduler)
 {
  scheduleJob();
 }
 if(!running.empty() || !exitScheduler)
 {
  deleteByTimer();
 }
}

/*
  insertJob
  adds a job to the priority queue
  calls std priority queue push
  The InsertJob() function first checks if (0 < n_procs ≤ p) and (n_ticks > 0).
If  so,  it  inserts  the  job  into  a  “wait  queue”.  Otherwise,  a  job
submission error is raised with an appropriate message.
*/
void Scheduler::insertJob(int id, int procs, int ticks, string desc) {
  if ((0 <= procs) && (0 <= ticks)) {
    Job toPriorityQueue = Job(id, procs, ticks, desc);
    procaQueue.push(toPriorityQueue);
    if(id!=-1)
      std::cout << toPriorityQueue << " inserted to priority Queue" << std::endl;

  }
}

/*
  findShortest
  acceses the top(shortest) element in the priority queue
*/
Job Scheduler::findShortest() { return procaQueue.top(); }

/*
  deleteShortest
  calls std priority queue pop
*/
Job Scheduler::deleteShortest() {
  Job deletedJob = Job(procaQueue.top());
  procaQueue.pop();
  return deletedJob;
}

/*
  checkAvailiability
*/
bool Scheduler::checkAvailiability(int procs) {
  return (avaliableProcs >= procs);
}

/*
  scheduleJob
  passes job to parallel computer( in theory)
  removes job from top of queue
*/
void Scheduler::scheduleJob() {
  int procs = procaQueue.top().getProcs();
  if(checkAvailiability(procs)&&(procaQueue.top().getID()!=-1))
  {
    avaliableProcs-= procs;
    Job toRunning = deleteShortest();
    running.push_back(toRunning);

    std::cout << toRunning <<
    " added to running processes and removed from priority queue"
    << std::endl;

  }
}

/*
  releaseProcs
  adds procs back to pool checks to
*/
void Scheduler::releaseProcs(int procs) {
    {
       (avaliableProcs += procs);
    }
}

/*
  pulls a job from input file
  assigns job an unused integer id
  calls InsertJob(job_id,job_description,n_procs,n_ticks)
*/
bool Scheduler::getAJobFromTextFile() {
  string desc;
  int procs = 0;    
  int ticks = 0;
  getline(fin, desc, ' ');
  for(int i = 0; i < desc.length(); i++)
  {
    desc[i] = tolower(desc[i]);
  }
  if(desc.find("exit") == string::npos) {
    fin >> procs;
    fin >> ticks;
    fin.ignore(1000, '\n');
    insertJob(totalJobs++, procs, ticks, desc);
    return false;
  }
  return true;
  
}



/*prints the job_ids of any jobs compleated during the tick*/
void Scheduler::deleteByTimer() {
  int syntactorator = 0;
    for (std::list<Job>::iterator iter = running.begin(); iter != running.end();iter++) {
      iter->decrementTimer();    
      if ((iter->getTimer() == 0)) {
        std::list<Job>::iterator deleteIter = iter; //don't erase loop guard
        std::cout << *iter <<", ";
        releaseProcs(iter->getProcs());
        iter--; //step off to be erased node
        running.erase(deleteIter); //erase node
        syntactorator++;
      }
    }
    std::cout << extraSyntax(syntactorator);
}

string Scheduler::extraSyntax(int syntactor) {
  return ((syntactor) ? ((syntactor - 1) ? ("were finished.\n")
                                                  : ("was finished.\n"))
                          : ("No jobs were finished\n"));
}
