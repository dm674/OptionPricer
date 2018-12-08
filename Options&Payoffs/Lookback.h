#ifndef LOOKBACK_H
#define LOOKBACK_H

#include "PayOffBridge.h"
#include "PathDependent.h"
#include "../Arrays.h"

class Lookback : public PathDependent
{
public:
    Lookback(const MJArray& LookAtTimes_,
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_);
    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~Lookback(){}
    virtual PathDependent* clone() const;
private:
    double DeliveryTime;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};

#endif //LOOKBACK_H
