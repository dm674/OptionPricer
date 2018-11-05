#include "Digital.h"

//PayOffDoubleDigital::PayOffDoubleDigital(double LowerLevel_,
//                                         double UpperLevel_)
//        :   LowerLevel(LowerLevel_),
//            UpperLevel(UpperLevel_)
//{
//}
//
//double PayOffDoubleDigital::operator()(double Spot) const
//{
//    if (Spot <= LowerLevel)
//        return 0;
//    if (Spot >= UpperLevel)
//        return 0;
//    return 1;
//}
//
//PayOff* PayOffDoubleDigital::clone() const
//{
//    return new PayOffDoubleDigital(*this);
//}

/*
 * Digital payoff
 */

PayOffDigital::PayOffDigital(double Strike_)
        :   Strike(Strike_)
{
}

double PayOffDigital::operator()(double Spot) const
{
    if (Spot <= Strike)
        return 0;
    return 1;
}

PayOff* PayOffDigital::clone() const
{
    return new PayOffDigital(*this);
}