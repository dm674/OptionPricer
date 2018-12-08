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
        Epsilon(epsilon), Prev(1000000.0), InnerMean(StatisticsMean()) { }

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

void TerminationMulti::Reset()
{
    for (int i = 0 ; i < Terms.size() ; i++){
        Terms[i]->Reset();
    }
    return;
}

//TerminationMC* TerminationMulti::clone() const
//{
//    return new TerminationMulti(*this);
//}

TerminationMulti::~TerminationMulti()
{
    for (int i = 0 ; i < Terms.size() ; i++){
        delete Terms[i];
    }
}

/*
 * TerminationMultiOR
 */

TerminationMultiOR::TerminationMultiOR(vector<TerminationMC*> terms)
        :
        TerminationMulti(terms)
{
}

bool TerminationMultiOR::IsDone() const
{
    bool done = false;
    for (int i = 0 ; i < Terms.size() ; i++){
        done = (done || Terms[i]->IsDone());
    }
    return done;
}

TerminationMC* TerminationMultiOR::clone() const
{
    return new TerminationMultiOR(*this);
}

/*
 * TerminationMultiAND
 */

TerminationMultiAND::TerminationMultiAND(vector<TerminationMC*> terms)
      :
      TerminationMulti(terms)
{
}

bool TerminationMultiAND::IsDone() const
{
    bool done = true;
    for (int i = 0 ; i < Terms.size() ; i++){
        done = (done && Terms[i]->IsDone());
    }
    return done;
}

TerminationMC* TerminationMultiAND::clone() const
{
    return new TerminationMultiAND(*this);
}
