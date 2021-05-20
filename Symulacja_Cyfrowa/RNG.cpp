#include "RNG.h"
#include <cmath>
#include <math.h> 

RNG::RNG(int kernel) : kernel_(kernel)
{
    // empty
}

RNG::~RNG()
{

}

double RNG::Rand()
{
    int h = kernel_ / kQ;
    kernel_ = kA * (kernel_ - kQ * h) - kR * h;
    if (kernel_ < 0)
        kernel_ = kernel_ + static_cast<int>(kM);
    return kernel_ / kM;
}

double RNG::Rand(double min, double max)
{
    return Rand() * (max - min) + min;
}

double RNG::RndExp(double lambda)
{
    double k = Rand();
    return -(1.0 / lambda) * log(k);
}

bool RNG::RndZeroOne(double p)
{
    double k;
    k = Rand();
    if (k < p)
        return 1;
    else
    return 0;
}
