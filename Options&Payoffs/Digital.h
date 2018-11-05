#ifndef DIGITAL_H
#define DIGITAL_H
#include "PayOff3.h"

//class PayOffDoubleDigital : public PayOff
//{
//public:
//    PayOffDoubleDigital(double LowerLevel_,
//                        double UpperLevel_);
//    virtual double operator()(double Spot) const;
//    virtual ~PayOffDoubleDigital(){}
//    virtual PayOff* clone() const;
//private:
//    double LowerLevel;
//    double UpperLevel;
//};

class PayOffDigital : public PayOff
{
public:
    PayOffDigital(double Strike_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffDigital(){}
    virtual PayOff* clone() const;
private:
    double Strike;
};
#endif