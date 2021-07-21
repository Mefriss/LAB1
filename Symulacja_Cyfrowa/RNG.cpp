#include "RNG.h"
#include <cmath>
#include <iterator>
#include <math.h> 
#include <vector>
#include <fstream>

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

void RNG::Generate_Seeds(int kernel)
{
    auto Seed_Gen = RNG(kernel);
    
    std::vector<int> seeds;
    for (int i = 0; i < number_of_Rands_; ++i)
    {
        for (int j = 0; j < number_of_Rands_; ++j)
        {
            Seed_Gen.Rand();
        }
        seeds.push_back(Seed_Gen.get_kernel());
    }

    std::ofstream output_file("./seeds.txt");
    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(seeds.begin(), seeds.end(), output_iterator);
}
