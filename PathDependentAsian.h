#ifndef PATH_DEPENDENT_ASIAN_H
#define PATH_DEPENDENT_ASIAN_H
#include "PathDependent.h"
#include "Options&Payoffs/PayOffBridge.h"

class PathDependentAsian : public PathDependent
{
public:
    PathDependentAsian(const MJArray& LookAtTimes_,
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_);
    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const = 0;
    virtual ~PathDependentAsian(){}
    virtual PathDependent* clone() const = 0;
protected:
    double DeliveryTime;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};

class PathDependentArithmeticAsian : public PathDependentAsian
{
public:
    PathDependentArithmeticAsian(const MJArray& LookAtTimes_,
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_);
    virtual PathDependent* clone() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const;
};

class PathDependentGeometricAsian : public PathDependentAsian
{
public:
    PathDependentGeometricAsian(const MJArray& LookAtTimes_,
                                 double DeliveryTime_,
                                 const PayOffBridge& ThePayOff_);
    virtual PathDependent* clone() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const;
};

#endif