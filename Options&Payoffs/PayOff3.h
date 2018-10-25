#ifndef PAYOFF3_H
#define PAYOFF3_H
class PayOff
{
public:
    PayOff(){};
    virtual double operator()(double Spot) const=0;
    virtual ~PayOff(){}
    virtual PayOff* clone() const=0;
private:
};

class PayOffCall : public PayOff
{
public:
    PayOffCall(double Strike_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffCall(){}
    virtual PayOff* clone() const;
private:
    double Strike;
};

class PayOffPut : public PayOff
{
public:
    PayOffPut(double Strike_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffPut(){}
    virtual PayOff* clone() const;
private:
    double Strike;
};

/*
 * Floating strike
 */

//class PayOffFloat : public PayOff
//{
//public:
//    PayOffFloat(){};
//    virtual double operator()(double Final, double Ref) const=0;
//    virtual ~PayOffFloat(){}
//    virtual PayOff* clone() const=0;
//};
//
//class PayOffCallFloat : public PayOffFloat
//{
//public:
//    PayOffCallFloat(double Coeff_);
//    virtual double operator()(double Spot) const;
//    virtual double operator()(double Final, double Ref) const;
//    virtual ~PayOffCallFloat(){}
//    virtual PayOff* clone() const;
//private:
//    double Coeff;
//};


#endif