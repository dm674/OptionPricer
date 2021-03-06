#include"ConvergenceTable.h"
#include<iostream>
using namespace std;

// NB: Copy constructor, destructor or assignment operator not required:
// dynamic memory allocation handled by Wrapper template class

ConvergenceTable::ConvergenceTable(const Wrapper<StatisticsMC>& Inner_)
: Inner(Inner_)
        {
                StoppingPoint=1;
                PathsDone=0;
        }

StatisticsMC* ConvergenceTable::clone() const
{
    return new ConvergenceTable(*this);
}

void ConvergenceTable::DumpOneResult(double result)
{
    Inner->DumpOneResult(result);
    ++PathsDone;
    if (PathsDone == StoppingPoint)
    {
        StoppingPoint*=2;
        std::vector<std::vector<double> >
                thisResult(Inner->GetResultsSoFar());
        for (unsigned long i=0; i < thisResult.size(); i++)
        {
            thisResult[i].push_back(PathsDone);
            ResultsSoFar.push_back(thisResult[i]);
        }
    }
    return;
}

std::vector<std::vector<double> >
ConvergenceTable::GetResultsSoFar() const
{
    std::vector<std::vector<double> > tmp(ResultsSoFar);
    if (PathsDone*2 != StoppingPoint)
    {
        std::vector<std::vector<double> >
                thisResult(Inner->GetResultsSoFar());
        for (unsigned long i=0; i < thisResult.size(); i++)
        {
            thisResult[i].push_back(PathsDone);
            tmp.push_back(thisResult[i]);
        }
    }
    return tmp;
}

void ConvergenceTable::PrintResults() const
{
    Inner->PrintResults();
    cout << "and converges as \n";
    StatisticsMC::PrintResults();
}