#ifndef Symulacja_Cyfrowa_Symulacja_Cyfrowa_RNG_H_
#define Symulacja_Cyfrowa_Symulacja_Cyfrowa_RNG_H_

#pragma once
class RNG
{
public:
    RNG(int kernel);
    virtual ~RNG();

    // Draws number between <0,1>
    double Rand(double min, double max);
    double Rand();
    
    double RndExp(double lambda);
    bool RndZeroOne(double p);
    void Generate_Seeds(int kernel);
	
    int get_kernel() { return kernel_; };
private:
    int number_of_seeds_ = 200;
    int number_of_Rands_ = 10000;
    int kernel_;
    const double kM = 2147483647.0;
    static const int kA = 16807;
    static const int kQ = 127773;
    static const int kR = 2836;
};

#endif