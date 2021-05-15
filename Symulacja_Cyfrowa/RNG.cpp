#include "RNG.h"
#include <cmath>

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