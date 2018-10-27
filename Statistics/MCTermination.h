#ifndef MCTERMINATION_H
#define MCTERMINATION_H
#include<time.h>
#include<iostream>
#include<vector>
#include"MCStatistics.h" // For Variance

/*
 * Base class (abstract)
 */


class TerminationMC
{
public:
    TerminationMC(){}
    virtual void DumpOneResult(double result)=0;
    virtual bool IsDone() const=0;
    virtual void Reset()=0;
    virtual TerminationMC* clone() const=0;
    virtual ~TerminationMC(){}
private: };

/*
 * Single termination conditions
 */


class TerminationPaths : public TerminationMC
{
public:
    TerminationPaths(unsigned long maxpaths);
    virtual void DumpOneResult(double current = 0.0);
    virtual bool IsDone() const;
    virtual void Reset();
    virtual TerminationPaths* clone() const;
private:
    unsigned long PathsDone;
    unsigned long MaxPaths;
};

class TerminationTime : public TerminationMC
{
public:
    TerminationTime(double maxtime);
    virtual void DumpOneResult(double current = 0.0);
    virtual bool IsDone() const;
    virtual void Reset();
    virtual TerminationTime* clone() const;
private:
    time_t StartTime;
    double MaxTime;
};

class TerminationVariance : public TerminationMC
{
public:
    TerminationVariance(double maxvariance);
    virtual void DumpOneResult(double current = 0.0);
    virtual bool IsDone() const;
    virtual void Reset();
    virtual TerminationVariance* clone() const;
private:
    StatisticsVariance InnerVariance;
    double MaxVariance;
};

class TerminationConv : public TerminationMC
{
public:
    TerminationConv(double epsilon);
    virtual void DumpOneResult(double current);
    virtual bool IsDone() const;
    virtual void Reset();
    virtual TerminationConv* clone() const;
private:
    double Epsilon;
    double Prev;
    StatisticsMean InnerMean;
};

/*
 * Multiple terminations
 */

class TerminationPathsNTime : public TerminationMC
{
public:
    TerminationPathsNTime(unsigned long maxpaths, double maxtime);
    virtual void DumpOneResult(double current = 0.0);
    virtual bool IsDone() const;
    virtual void Reset();
    virtual TerminationPathsNTime* clone() const;
private:
    TerminationPaths TermPaths;
    TerminationTime TermTime;
};

class TerminationMulti : public TerminationMC
{
public:
    TerminationMulti(std::vector<TerminationMC*> terms);
    virtual ~TerminationMulti();
    virtual void DumpOneResult(double result);
    virtual bool IsDone() const;
    virtual void Reset();
    virtual TerminationMC* clone() const;
private:
    std::vector<TerminationMC*> Terms;
};

#endif