#ifndef Symulacja_Cyfrowa_Symulacja_Cyfrowa_RNG_H_
#define Symulacja_Cyfrowa_Symulacja_Cyfrowa_RNG_H_

#pragma once
class RNG
{
public:
    RNG(int kernel);
    virtual ~RNG();

    // Draws number between <0,1>
    double Rand();

    int get_kernel() { return kernel_; };
private:
    int kernel_;
    const double kM = 2147483647.0;
    static const int kA = 16807;
    static const int kQ = 127773;
    static const int kR = 2836;
};

#endif