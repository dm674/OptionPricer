#ifndef EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H

#include "Wrapper.h"
#include "Options&Payoffs/Parameters.h"
#include "Options&Payoffs/PathDependent.h"
#include "Statistics/MCStatistics.h"
#include "Statistics/MCTermination.h"
#include <vector>

class ExoticEngine
{
public:
    ExoticEngine(const Wrapper<PathDependent>& TheProduct_,
                const Parameters& r_);
    virtual void GetOnePath(MJArray& SpotValues)=0;
    void DoSimulation(StatisticsMC& TheGatherer,
                      TerminationMC& terminator);
    virtual ~ExoticEngine(){}
    double DoOnePath(const MJArray& SpotValues) const;

private:
    Wrapper<PathDependent> TheProduct;
    Parameters r;
    MJArray Discounts;
    mutable std::vector<CashFlow> TheseCashFlows;
};
#endif