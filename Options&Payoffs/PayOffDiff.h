#include"PayOff3.h"
#include"Digital.h"

#ifndef PAYOFFDIFF_H
#define PAYOFFDIFF_H

class PayOffDiff : public PayOff
{
public:
    PayOffDiff(PayOff* PayOffPos_, PayOff* PayOffNeg_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffDiff(){}
    virtual PayOff* clone() const;
protected:
    PayOff* PayOffPos;
    PayOff* PayOffNeg;
};

class PayOffDoubleDigital : public PayOffDiff
{
public:
    PayOffDoubleDigital(double LowerLevel_,
                        double UpperLevel_);
//    virtual double operator()(double Spot) const;
    virtual ~PayOffDoubleDigital(){}
    virtual PayOff* clone() const;
};

#endif //OPTIONPRICER_PAYOFFDIFF_H
