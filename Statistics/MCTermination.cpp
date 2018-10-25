#include"MCTermination.h"

/*
 * TerminationPaths
*/

TerminationPaths::TerminationPaths(unsigned long maxpaths)
        :
        MaxPaths(maxpaths), PathsDone(0UL) { }

void TerminationPaths::DumpOneResult()
{
    PathsDone++;
}

bool TerminationPaths::IsDone() const
{
    if (PathsDone == MaxPaths)
        return true;
    else
        return false;
}

TerminationPaths* TerminationPaths::clone() const
{
    return new TerminationPaths(*this);
}

/*
 * TerminationTime
*/

TerminationTime::TerminationTime(double maxtime)
{
    time_t timer;
    StartTime = time(&timer);
    MaxTime = maxtime;
}

void TerminationTime::DumpOneResult()
{
    // Empty
}

bool TerminationTime::IsDone() const
{
    time_t timer;
    return (difftime(time(&timer),StartTime) > MaxTime);
}

TerminationTime* TerminationTime::clone() const
{
    return new TerminationTime(*this);
}

/*
 * TerminationTime
*/

TerminationPathsNTime::TerminationPathsNTime(unsigned long maxpaths, double maxtime)
    :
    TermPaths(TerminationPaths(maxpaths)) , TermTime(TerminationTime(maxtime)) { }

void TerminationPathsNTime::DumpOneResult()
{
    TermPaths.DumpOneResult();
}

bool TerminationPathsNTime::IsDone() const
{
    return (TermPaths.IsDone() || TermTime.IsDone());
}

TerminationPathsNTime* TerminationPathsNTime::clone() const
{
    return new TerminationPathsNTime(*this);
}