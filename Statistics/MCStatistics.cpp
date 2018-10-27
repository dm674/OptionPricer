#include"MCStatistics.h"
#include<cmath>
#include<algorithm>
using namespace std;

/*
 * StatisticsMean
*/

StatisticsMean::StatisticsMean()
        :
        RunningSum(0.0), PathsDone(0UL) { }

void StatisticsMean::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum += result;
}

vector<vector<double> >
StatisticsMean::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);
    Results[0].resize(1);
    Results[0][0] = RunningSum / PathsDone;
    return Results;
}

StatisticsMC* StatisticsMean::clone() const
{
    return new StatisticsMean(*this);
}

/*
 * StatisticsVariance
*/

StatisticsVariance::StatisticsVariance()
        :
        RunningSum(0.0), RunningSumSquare(0.0), PathsDone(0UL) { }

void StatisticsVariance::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum += result;
    RunningSumSquare += pow(result,2);
}

vector<vector<double> >
StatisticsVariance::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);
    Results[0].resize(1);
    Results[0][0] = RunningSumSquare / PathsDone - pow(RunningSum / PathsDone,2);
    return Results;
}

StatisticsMC* StatisticsVariance::clone() const
{
    return new StatisticsVariance(*this);
}

/*
 * StatisticsMoments
*/

StatisticsMoments::StatisticsMoments()
        :
        RunningSum(0.0), RunningSumSquare(0.0), RunningSumCube(0.0), RunningSumQuartic(0.0), PathsDone(0UL) { }

void StatisticsMoments::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum += result;
    RunningSumSquare += pow(result,2);
    RunningSumCube += pow(result,3);
    RunningSumQuartic += pow(result,4);
}

vector<vector<double> >
StatisticsMoments::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);
    Results[0].resize(4);
    Results[0][0] = RunningSum / PathsDone;
    Results[0][1] = RunningSumSquare / PathsDone - pow(Results[0][0],2);
    Results[0][2] = RunningSumCube / PathsDone
            - 3*Results[0][0]*RunningSumSquare/PathsDone
            + 2*pow(Results[0][0],3);
    Results[0][3] = RunningSumQuartic / PathsDone
            - 4*Results[0][0]*RunningSumCube/PathsDone
            + 6*pow(Results[0][0],2)*RunningSumSquare/PathsDone
            - 3*pow(Results[0][0],4);
    return Results;
}

StatisticsMC* StatisticsMoments::clone() const
{
    return new StatisticsMoments(*this);
}

/*
 * StatisticsVaR
*/

StatisticsVaR::StatisticsVaR()
        :
        RunningLows(0UL), PathsDone(0UL) { }

void StatisticsVaR::DumpOneResult(double result)
{
    PathsDone++;
    RunningLows.push_back(result);
    std::sort(RunningLows.begin(),RunningLows.end());
    // Keep 10 first, and increase length by 1 every 20 paths
    // i.e. converge towards 5% - 5x more than required for 1%-VaR
    if(PathsDone > 10 && (PathsDone % 20) != 0 ) {
        RunningLows.pop_back();
    }
}

vector<vector<double> >
StatisticsVaR::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);
    Results[0].resize(1);
    // Return 1%-VaR
    Results[0][0] = RunningLows[(int)round(PathsDone/100)];
    return Results;
}

StatisticsMC* StatisticsVaR::clone() const
{
    return new StatisticsVaR(*this);
}

/*
 * StatisticsMulti
*/

StatisticsMulti::StatisticsMulti(vector<StatisticsMC*> stats)
{
    Stats = stats;

}

void StatisticsMulti::DumpOneResult(double result)
{
    for (int i = 0 ; i < Stats.size() ; i++){
        Stats[i]->DumpOneResult(result);
    }
}

vector<vector<double> >
StatisticsMulti::GetResultsSoFar() const
{
    // Assumes each StatisticsMC results are in first row of 2D array
    vector<vector<double> > Results(Stats.size());
    for (int i = 0 ; i < Stats.size() ; i++){
        Results[i] = Stats[i]->GetResultsSoFar()[0];
    }
    return Results;
}

StatisticsMC* StatisticsMulti::clone() const
{
    return new StatisticsMulti(*this);
}

StatisticsMulti::~StatisticsMulti()
{
    for (int i = 0 ; i < Stats.size() ; i++){
        delete Stats[i];
    }
}