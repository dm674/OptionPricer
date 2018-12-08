#include "Lookback.h"
#include<algorithm>

Lookback::Lookback(const MJArray& LookAtTimes_,
                   double DeliveryTime_,
                   const PayOffBridge& ThePayOff_)
        :
        PathDependent(LookAtTimes_),
        DeliveryTime(DeliveryTime_),
        ThePayOff(ThePayOff_),
        NumberOfTimes(LookAtTimes_.size())
{ }

unsigned long Lookback::MaxNumberOfCashFlows() const
{
    return 1UL;
}

MJArray Lookback::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

PathDependent* Lookback::clone() const
{
    return new Lookback(*this);
}

unsigned long Lookback::CashFlows(const MJArray& SpotValues,
                                  std::vector<CashFlow>& GeneratedFlows) const
{
    GeneratedFlows[0].TimeIndex = 0UL;
    // For a put/call payoff, the minimum/maximum (resp.) spot will be chosen
    GeneratedFlows[0].Amount = std::max(ThePayOff(SpotValues.min()),ThePayOff(SpotValues.max()));
    return 1UL;
}