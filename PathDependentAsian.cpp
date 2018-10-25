#include "PathDependentAsian.h"
#include<cmath>

/*
 * Generic Asian
 */

PathDependentAsian::PathDependentAsian(const MJArray& LookAtTimes_,
                                       double DeliveryTime_,
                                       const PayOffBridge& ThePayOff_)
        :
        PathDependent(LookAtTimes_),
        DeliveryTime(DeliveryTime_),
        ThePayOff(ThePayOff_),
        NumberOfTimes(LookAtTimes_.size())
{ }

unsigned long PathDependentAsian::MaxNumberOfCashFlows() const
{
    return 1UL;
}

MJArray PathDependentAsian::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

/*
 * Arithmetic Asian
 */

PathDependentArithmeticAsian::PathDependentArithmeticAsian(const MJArray& LookAtTimes_,
                                       double DeliveryTime_,
                                       const PayOffBridge& ThePayOff_)
        :
        PathDependentAsian(LookAtTimes_, DeliveryTime_, ThePayOff_)
{ }

PathDependent* PathDependentArithmeticAsian::clone() const
{
    return new PathDependentArithmeticAsian(*this);
}

unsigned long PathDependentArithmeticAsian::CashFlows(const MJArray& SpotValues,
                                            std::vector<CashFlow>& GeneratedFlows) const
{
    double sum = SpotValues.sum();
    double mean = sum/NumberOfTimes;
    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = ThePayOff(mean);
    return 1UL;
}

/*
 * Geometric Asian
 */

PathDependentGeometricAsian::PathDependentGeometricAsian(const MJArray& LookAtTimes_,
                                                           double DeliveryTime_,
                                                           const PayOffBridge& ThePayOff_)
        :
        PathDependentAsian(LookAtTimes_, DeliveryTime_, ThePayOff_)
{ }

PathDependent* PathDependentGeometricAsian::clone() const
{
    return new PathDependentGeometricAsian(*this);
}

unsigned long PathDependentGeometricAsian::CashFlows(const MJArray& SpotValues,
                                            std::vector<CashFlow>& GeneratedFlows) const
{
    double prod = SpotValues.product();
    double geomean = pow(prod,1.0/NumberOfTimes);
    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = ThePayOff(geomean);
    return 1UL;
}