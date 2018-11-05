#ifndef STATISTICS_H
#define STATISTICS_H
#include <vector>

class StatisticsMC
{
public:
    StatisticsMC(){}
    virtual void DumpOneResult(double result)=0;
    virtual std::vector< std::vector<double> >
        GetResultsSoFar() const=0;
    virtual void PrintResults() const;
    virtual StatisticsMC* clone() const=0;
    virtual ~StatisticsMC(){}
private:
};

class StatisticsMean : public StatisticsMC
{
public:
    StatisticsMean();
    virtual void DumpOneResult(double result);
    virtual std::vector< std::vector<double> >
        GetResultsSoFar() const;
    virtual void PrintResults() const;
    virtual StatisticsMC* clone() const;
private:
    double RunningSum;
    unsigned long PathsDone;
};

class StatisticsVariance : public StatisticsMC
{
public:
    StatisticsVariance();
    virtual void DumpOneResult(double result);
    virtual std::vector< std::vector<double> >
    GetResultsSoFar() const;
    virtual void PrintResults() const;
    virtual StatisticsMC* clone() const;
private:
    double RunningSum;
    double RunningSumSquare;
    unsigned long PathsDone;
};

class StatisticsMoments : public StatisticsMC
{
public:
    StatisticsMoments();
    virtual void DumpOneResult(double result);
    virtual std::vector< std::vector<double> >
    GetResultsSoFar() const;
    virtual void PrintResults() const;
    virtual StatisticsMC* clone() const;
private:
    double RunningSum;
    double RunningSumSquare;
    double RunningSumCube;
    double RunningSumQuartic;
    unsigned long PathsDone;
};

class StatisticsVaR : public StatisticsMC
{
public:
    StatisticsVaR();
    virtual void DumpOneResult(double result);
    virtual std::vector< std::vector<double> >
    GetResultsSoFar() const;
    virtual void PrintResults() const;
    virtual StatisticsMC* clone() const;
private:
    std::vector<double> RunningLows;
    unsigned long PathsDone;
};

class StatisticsMulti : public StatisticsMC
{
public:
    StatisticsMulti(std::vector<StatisticsMC*> stats);
    virtual ~StatisticsMulti();
    virtual void DumpOneResult(double result);
    virtual std::vector< std::vector<double> >
    GetResultsSoFar() const;
    virtual void PrintResults() const;
    virtual StatisticsMC* clone() const;
private:
    std::vector<StatisticsMC*> Stats;
};

#endif