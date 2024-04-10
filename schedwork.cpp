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
    DailySchedule& sched,
    int r,
    int c);

bool schedOK(const vector<int>& numShifts,
    const size_t maxShifts,
    DailySchedule& sched);

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

    vector<int> numShifts; // keep track of total shifts worked by nurses
    for (int i=0; i<avail[0].size(); i++)
        numShifts.push_back(0);

    schedHelp(avail, dailyNeed, maxShifts, sched, numShifts, 0, 0);
}

bool schedHelp(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& numShifts,
    int r,
    int c)
{
    // base cases: row or col incremented out of range
    if (r==sched.size()) // we skipped past the last row; everything worked
        return true;
    if (c==sched[0].size()) // skipped past the last col; need new row
        return schedHelp(avail, dailyNeed, maxShifts, sched, r+1, 0);

    // iterate through possibilities
    for (int i=0; i<avail[0].size(); i++) {
        sched[r][c] = i; // try a worker
        // increment their number of shifts worked
        numShifts[i]++;
        // check if that worked
        if (schedOK(numShifts, maxShifts)) {
            // that did work
            if (schedHelp(avail, dailyNeed, maxShifts, sched, r, c+1))
                // and everything else down the line worked
                return true;
        }
        // else schedOK was false. let for loop try something else
        else
            numShifts[i]--;
    } 
    // reset this b/c it didn't work
    sched[r][c] = INVALID_ID;
    return false;

}

bool schedOK(const vector<int>& numShifts, const size_t maxShifts) {
    for (int i=0; i<numShifts.size(); i++) {
        if (numShifts[i] > maxShifts)
            return false;
    }

    return true;
}