#include "European.h"

European::European(const MJArray& LookAtTimes_,
                    double DeliveryTime_,
                    const PayOffBridge& ThePayOff_)
        :
        PathDependent(LookAtTimes_),
        DeliveryTime(DeliveryTime_),
        ThePayOff(ThePayOff_)
{ }

unsigned long European::MaxNumberOfCashFlows() const
{
    return 1UL;
}

MJArray European::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

PathDependent* European::clone() const
{
    return new European(*this);
}

unsigned long European::CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const
{
//    double sum = SpotValues.sum();
//    double mean = sum/NumberOfTimes;
    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = ThePayOff(SpotValues[SpotValues.size()-1]);
//    GeneratedFlows[0].Amount = ThePayOff(mean);
    return 1UL;
}