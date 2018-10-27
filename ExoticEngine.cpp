#include "ExoticEngine.h"
#include <cmath>
#include<iostream>

ExoticEngine::ExoticEngine(const Wrapper<PathDependent>& TheProduct_,
                           const Parameters& r_)
        :
        TheProduct(TheProduct_),
        r(r_),
        Discounts(TheProduct_->PossibleCashFlowTimes())
{
    for (unsigned long i=0; i < Discounts.size(); i++)
        Discounts[i] = exp(-r.Integral(0.0, Discounts[i]));
    TheseCashFlows.resize(TheProduct->MaxNumberOfCashFlows());
}

void ExoticEngine::DoSimulation(StatisticsMC& TheGatherer,
                                TerminationMC& terminator)
{
    MJArray SpotValues(TheProduct->GetLookAtTimes().size());
    TheseCashFlows.resize(TheProduct->MaxNumberOfCashFlows());
    terminator.Reset(); // Use to reset all conditions, including timer
    double thisValue;
    do
    {
        GetOnePath(SpotValues);
        thisValue = DoOnePath(SpotValues);
        TheGatherer.DumpOneResult(thisValue);
        terminator.DumpOneResult(thisValue);
        //cout << terminator.IsDone();
    } while (!terminator.IsDone());
    return;
}

double ExoticEngine::DoOnePath(const MJArray& SpotValues) const
{
    unsigned long NumberFlows =
            TheProduct->CashFlows(SpotValues,
                                  TheseCashFlows);
    double Value=0.0;
    for (unsigned i =0; i < NumberFlows; ++i)
        Value += TheseCashFlows[i].Amount *
                 Discounts[TheseCashFlows[i].TimeIndex];
    return Value;
}
