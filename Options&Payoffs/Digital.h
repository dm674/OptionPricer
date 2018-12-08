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

class PayOffDigitalCall : public PayOff
{
public:
    PayOffDigitalCall(double Strike_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffDigitalCall(){}
    virtual PayOff* clone() const;
private:
    double Strike;
};

class PayOffDigitalPut : public PayOff
{
public:
    PayOffDigitalPut(double Strike_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffDigitalPut(){}
    virtual PayOff* clone() const;
private:
    double Strike;
};

#endif