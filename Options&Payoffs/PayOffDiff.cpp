#include"PayOffDiff.h"

/*
 * PayOffDiff : difference of two payoffs
 */

PayOffDiff::PayOffDiff(PayOff* PayOffPos_, PayOff* PayOffNeg_)
        :   PayOffPos(PayOffPos_),
            PayOffNeg(PayOffNeg_)
{
}

double PayOffDiff::operator()(double Spot) const
{
    return PayOffPos->operator()(Spot) - PayOffNeg->operator()(Spot);
}

PayOff* PayOffDiff::clone() const
{
    return new PayOffDiff(*this);
}

/*
 * Double-digital
 */

PayOffDoubleDigital::PayOffDoubleDigital(double LowerLevel_,
                                         double UpperLevel_)
         : PayOffDiff(new PayOffDigital(LowerLevel_),
                      new PayOffDigital(UpperLevel_))
{
}

PayOff* PayOffDoubleDigital::clone() const
{
    return new PayOffDoubleDigital(*this);
}
