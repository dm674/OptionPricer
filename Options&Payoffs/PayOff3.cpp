#include "PayOff3.h"
#include <algorithm>
using namespace std;

// Vanilla call
PayOffCall::PayOffCall(double Strike_) : Strike(Strike_)
{
}

double PayOffCall::operator() (double Spot) const
{
    return max(Spot-Strike,0.0);
}
PayOff* PayOffCall::clone() const
{
    return new PayOffCall(*this);
}

// Vanilla put
double PayOffPut::operator() (double Spot) const
{
    return max(Strike-Spot,0.0);
}

PayOffPut::PayOffPut(double Strike_) : Strike(Strike_)
{
}

PayOff* PayOffPut::clone() const
{
    return new PayOffPut(*this);
}

//// Vanilla call floating
//PayOffCallFloat::PayOffCallFloat(double Coeff_) : Coeff(Coeff_)
//{
//}
//
//double PayOffCallFloat::operator() (double Spot) const
//{
//    return 0.0;
//}
//double PayOffCallFloat::operator() (double Final, double Ref) const
//{
//    return max(Final - Coeff*Ref ,0.0);
//}
//PayOff* PayOffCallFloat::clone() const
//{
//    return new PayOffCallFloat(*this);
//}