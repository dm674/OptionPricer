#ifndef MCTERMINATION_H
#define MCTERMINATION_H
#include<time.h>

class TerminationMC
{
public:
    TerminationMC(){}
    virtual void DumpOneResult()=0;
    virtual bool IsDone() const=0;
    virtual TerminationMC* clone() const=0;
    virtual ~TerminationMC(){}
private: };

class TerminationPaths : public TerminationMC
{
public:
    TerminationPaths(unsigned long maxpaths);
    virtual void DumpOneResult();
    virtual bool IsDone() const;
    virtual TerminationPaths* clone() const;
private:
    unsigned long PathsDone;
    unsigned long MaxPaths;
};

class TerminationTime : public TerminationMC
{
public:
    TerminationTime(double maxtime);
    virtual void DumpOneResult();
    virtual bool IsDone() const;
    virtual TerminationTime* clone() const;
private:
    time_t StartTime;
    double MaxTime;
};

class TerminationPathsNTime : public TerminationMC
{
public:
    TerminationPathsNTime(unsigned long maxpaths, double maxtime);
    virtual void DumpOneResult();
    virtual bool IsDone() const;
    virtual TerminationPathsNTime* clone() const;
private:
    TerminationPaths TermPaths;
    TerminationTime TermTime;
};

#endif