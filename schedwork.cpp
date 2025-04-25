#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
static bool backTrack(size_t day, size_t slotIdx, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, vector<int> shifts, DailySchedule& sched){
  const size_t n_Days = avail.size();
  const size_t k = avail[0].size();
  if(day == n_Days){
    return true;
  }
  if(slotIdx == dailyNeed){
    return backTrack(day + 1, 0, avail, dailyNeed, maxShifts, shifts, sched);
  }
  for(Worker_T w = 0; w < k; ++w){
    if(!avail[day][w]){
      continue;
    }
    if(shifts[w] >= static_cast<int>(maxShifts)){
      continue;
    }
    sched[day][slotIdx] = w;
    ++shifts[w];
    if(backTrack(day, slotIdx + 1, avail, dailyNeed, maxShifts, shifts, sched)){
      return true;
    }
    --shifts[w];
    sched[day][slotIdx] = INVALID_ID;
  }
  return false;
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    const size_t n_Days = avail.size();
    const size_t k = avail[0].size();
    if(dailyNeed == 0 || dailyNeed > k){
      return false;
    }
    sched.assign(n_Days, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<int> shifts(k, 0);
    for(size_t d = 0; d < n_Days; d++){
      if(avail[d].size() != k){
        return false;
      }
    }
    return backTrack(0, 0, avail, dailyNeed, maxShifts, shifts, sched);
}

