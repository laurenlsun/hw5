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
bool schedHelp(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    vector<int>& numShifts,
    set<Worker_T>& onShift,
    DailySchedule& sched,
    unsigned int r,
    unsigned int c);

bool schedOK(const vector<int>& numShifts,
    const size_t maxShifts);

bool noRepeats(const vector<Worker_T>& day, Worker_T worker);

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

    sched = vector<vector<Worker_T>>(avail.size());
    for (int i=0; i<sched.size();i++) {
        vector<Worker_T> blankVect(dailyNeed, INVALID_ID);
        sched[i] = blankVect;
    }
    // create vector that keeps track of shifts worked
    vector<int> numShifts(avail[0].size(), 0);

    // create a set that keeps track of workers assigned per day
    set<Worker_T> onShift;

    return schedHelp(avail, dailyNeed, maxShifts, numShifts, onShift, sched, 0, 0);
}

bool schedHelp(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    vector<int>& numShifts,
    set<Worker_T>& onShift,
    DailySchedule& sched,
    unsigned int r,
    unsigned int c) // index in avail[0] of workers
{
    // cout << "row " << r << ", col " << c << endl;
    // base cases: row or col incremented out of range
    if (r==sched.size()) { // we skipped past the last row; everything worked
        // cout << "row out of range" << endl;
        // cout << "returning TRUE" << endl;
        return true;
    }
    if (c==dailyNeed) { // skipped past the last col; need new row
        // cout << "col out of range" << endl;
        onShift.clear(); // clear set of workers on shift for the new day
        return schedHelp(avail, dailyNeed, maxShifts, numShifts, onShift, sched, r+1, 0);
    }

    // iterate through possibilities
    // avail[0] is the number of workers
    for (Worker_T i=0; i<avail[r].size(); i++) {
        sched[r][c] = i;
        // cout << "scheduled worker " << i << " for (" << r << ", " << c << ")" << endl;
        // increment their number of shifts worked
        numShifts[i]++;
        
        // cout << "worker " << i << " now works " << numShifts[i] << " shifts" << endl;
        // check if that worked
        
        // cout << "avail[r][i]==1:  " << (avail[r][i]==1) << endl;
        // cout << "(numShifts [i] <= maxShifts):  " << (numShifts [i] <= maxShifts) << endl;

 
        if ((avail[r][i]==1) &&  // worker is available
            (numShifts [i] <= maxShifts) &&  // didn't work over max shifts
            (onShift.find(i)==onShift.end())) {  // didn't schedule same worker twice
              // that did work
              onShift.insert(i);
              if (schedHelp(avail, dailyNeed, maxShifts, numShifts, onShift, sched, r, c+1)) {
                  // and everything else down the line worked
                  return true;
              }
          }
        // else something didn't work. let for loop try something else
        // cout << "nevermind--backtracking ..." << endl;
        numShifts[i]--;
        onShift.erase(i);
    } 
    // reset this b/c it didn't work
    sched[r][c] = INVALID_ID;
    return false;
}

