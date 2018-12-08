#ifndef EUROPEAN_H
#define EUROPEAN_H
#include "PayOffBridge.h"
#include "PathDependent.h"
#include "../Arrays.h"


class European : public PathDependent
{
public:
    European(const MJArray& LookAtTimes_,
             double DeliveryTime,
             const PayOffBridge& ThePayOff_);
//    double OptionPayOff(double Spot) const;
//    double GetExpiry() const;
    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                std::vector<CashFlow>& GeneratedFlows) const;
    virtual PathDependent* clone() const;
    virtual ~European(){}
private:
    double DeliveryTime;
    PayOffBridge ThePayOff;
};
#endif

// PathDependent
//const MJArray& GetLookAtTimes() const;
//virtual unsigned long MaxNumberOfCashFlows() const=0;
//virtual MJArray PossibleCashFlowTimes() const=0;
//virtual unsigned long CashFlows(const MJArray& SpotValues,
//                                std::vector<CashFlow>&
//                                GeneratedFlows) const=0;
//virtual PathDependent* clone() const=0;
//virtual ~PathDependent(){}



//
//class PathDependentAsian : public PathDependent
//{
//public:
//    PathDependentAsian(const MJArray& LookAtTimes_,
//                       double DeliveryTime_,
//                       const PayOffBridge& ThePayOff_);
//    virtual unsigned long MaxNumberOfCashFlows() const;
//    virtual MJArray PossibleCashFlowTimes() const;
//    virtual unsigned long CashFlows(const MJArray& SpotValues,
//                                    std::vector<CashFlow>& GeneratedFlows) const = 0;
//    virtual ~PathDependentAsian(){}
//    virtual PathDependent* clone() const = 0;
//protected:
//    double DeliveryTime;
//    PayOffBridge ThePayOff;
//    unsigned long NumberOfTimes;
//};