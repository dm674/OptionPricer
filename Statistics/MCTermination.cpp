#include"MCTermination.h"
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;

/*
 * TerminationPaths
*/

TerminationPaths::TerminationPaths(unsigned long maxpaths)
        :
        MaxPaths(maxpaths), PathsDone(0UL) { }

void TerminationPaths::DumpOneResult(double current)
{
    PathsDone++;
}

bool TerminationPaths::IsDone() const
{
    return (PathsDone >= MaxPaths);
}

void TerminationPaths::Reset()
{
    PathsDone = 0UL;
}

TerminationPaths* TerminationPaths::clone() const
{
    return new TerminationPaths(*this);
}

/*
 * TerminationTime
*/

TerminationTime::TerminationTime(double maxtime)
        :
        MaxTime(maxtime)
{
    time_t timer;
    StartTime = time(&timer);
}

void TerminationTime::DumpOneResult(double current)
{
    // Empty
}

bool TerminationTime::IsDone() const
{
    time_t timer;
    return (difftime(time(&timer),StartTime) > MaxTime);
}

void TerminationTime::Reset()
{
    time_t timer;
    StartTime = time(&timer);
}

TerminationTime* TerminationTime::clone() const
{
    return new TerminationTime(*this);
}

/*
 * TerminationVariance
*/

TerminationVariance::TerminationVariance(double maxvariance)
        :
        MaxVariance(maxvariance), InnerVariance(StatisticsVariance()) { }

void TerminationVariance::DumpOneResult(double current)
{
    InnerVariance.DumpOneResult(current);
}

bool TerminationVariance::IsDone() const
{
    return (InnerVariance.GetResultsSoFar()[0][0] < MaxVariance);
}

void TerminationVariance::Reset()
{
    InnerVariance = StatisticsVariance();
}

TerminationVariance* TerminationVariance::clone() const
{
    return new TerminationVariance(*this);
}

/*
 * TerminationConv
*/

TerminationConv::TerminationConv(double epsilon)
        :
        Epsilon(epsilon), Prev(10000.0), InnerMean(StatisticsMean()) { }

void TerminationConv::DumpOneResult(double current)
{
    Prev = InnerMean.GetResultsSoFar()[0][0];
    InnerMean.DumpOneResult(current);
}

bool TerminationConv::IsDone() const
{
    return (abs(InnerMean.GetResultsSoFar()[0][0]-Prev)<Epsilon);
}

void TerminationConv::Reset()
{
    Prev= 10000.0;
}

TerminationConv* TerminationConv::clone() const
{
    return new TerminationConv(*this);
}

/*
 * TerminationPaths&Time
*/

TerminationPathsNTime::TerminationPathsNTime(unsigned long maxpaths, double maxtime)
    :
    TermPaths(TerminationPaths(maxpaths)) , TermTime(TerminationTime(maxtime)) { }

void TerminationPathsNTime::DumpOneResult(double current)
{
    TermPaths.DumpOneResult();
}

bool TerminationPathsNTime::IsDone() const
{
    return (TermPaths.IsDone() || TermTime.IsDone());
}

void TerminationPathsNTime::Reset()
{
    TermPaths.Reset();
    TermTime.Reset();
    return;
}

TerminationPathsNTime* TerminationPathsNTime::clone() const
{
    return new TerminationPathsNTime(*this);
}

/*
 * TerminationMulti
*/

TerminationMulti::TerminationMulti(vector<TerminationMC*> terms)
{
    Terms = terms;
}

void TerminationMulti::DumpOneResult(double current)
{
    for (int i = 0 ; i < Terms.size() ; i++){
        Terms[i]->DumpOneResult(current);
    }
}

bool TerminationMulti::IsDone() const
{
    bool done = false;
    for (int i = 0 ; i < Terms.size() ; i++){
        done = (done || Terms[i]->IsDone());
    }
    return done;
}

void TerminationMulti::Reset()
{
    for (int i = 0 ; i < Terms.size() ; i++){
        Terms[i]->Reset();
    }
    return;
}

TerminationMC* TerminationMulti::clone() const
{
    return new TerminationMulti(*this);
}

TerminationMulti::~TerminationMulti()
{
    for (int i = 0 ; i < Terms.size() ; i++){
        delete Terms[i];
    }
}